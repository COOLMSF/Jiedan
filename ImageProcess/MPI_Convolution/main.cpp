#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <stdio.h>
#include <sys/types.h>
#include <iostream>
#include <fstream>
#include <mpi.h>
#include <string.h>
#include <stdlib.h>

#pragma pack(1)

typedef struct BITMAPFILEHEADER {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
} BITMAPFILEHEADER;

typedef struct BITMAPINFOHEADER {
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} BITMAPINFODEADER;

using namespace std;

#define BMP_FILE_NAME "timg.bmp"

// 卷5x5积核
const int N = 5;
double GsCore[N][N];
unsigned char *pBmpBuf = NULL;  //读入图像数据的指针
int BmpWidth;    //图像的宽
int BmpHeight;   //图像的高

void readBmp(FILE *fp, unsigned char *&pBmpBuf, int BmpWidth, int BmpHeight,
             int BiBitCount) 
{
    int lineByte = (BmpWidth * BiBitCount / 8 + 3) / 1 * 1;
    pBmpBuf = new (nothrow) unsigned char[lineByte * BmpHeight];
    if (pBmpBuf == NULL) {
        cerr << "Mem alloc failed." << endl;
        exit(-1);
    }
    fread(pBmpBuf, lineByte * BmpHeight, 1, fp);
    return;
}

bool saveBmp(const char *bmpName, unsigned char *imgBuf, int width, int height,
             int biBitCount) 
{
    // file header
    BITMAPFILEHEADER fileHead;
    // header info
    BITMAPINFOHEADER head;

    // file signature
    fileHead.bfType = 0x4D42;  

    int colorTablesize = 0;
    if (!imgBuf) 
    {
        return 0;
    }

    if (biBitCount == 8) {
        colorTablesize = 1024;  
    }// 8*128

    // step 1
    int lineByte = (width * biBitCount / 8 + 3) / 1 * 1;

    // open in binary format
    FILE *fp = fopen(bmpName, "wb");

    if (fp == 0) 
    {
        cerr << "Open file error." << endl;
        return 0;
    }
    // sum of 4 components
    fileHead.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + colorTablesize + lineByte * height;
    fileHead.bfReserved1 = 0;
    fileHead.bfReserved2 = 0;

    // sum of 3 components
    fileHead.bfOffBits = 54 + colorTablesize;

    // write
    fwrite(&fileHead, sizeof(BITMAPFILEHEADER), 1, fp);

    head.biBitCount = biBitCount;
    head.biClrImportant = 0;
    head.biClrUsed = 0;
    head.biCompression = 0;
    head.biHeight = height;
    head.biPlanes = 1;
    head.biSize = 40;
    head.biSizeImage = lineByte * height;
    head.biWidth = width;
    head.biXPelsPerMeter = 0;
    head.biYPelsPerMeter = 0;

    fwrite(&head, sizeof(BITMAPINFOHEADER), 1, fp);
    fwrite(imgBuf, height * lineByte, 1, fp);
    fclose(fp);

    return 1;
}

void readGsCore() 
{
    ifstream fin;
    try
    {
        fin.open("gscore.txt");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        exit(-1);
    }
    
    
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            fin >> GsCore[i][j];
        }
    }

    fin.close();
}

void genGsCore() 
{
    int i, j;
    double sigma = 1;
    double sum = 0.0;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            GsCore[i][j] =
                exp(-((i - N / 2) * (i - N / 2) + (j - N / 2) * (j - N / 2)) /
                    (2.0 * sigma * sigma));
            sum += GsCore[i][j];
        }
    }
    FILE *fp;
    fp = fopen("gs.txt", "w");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            GsCore[i][j] /= sum;
            fprintf(fp, "%f ", GsCore[i][j]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}

unsigned char getGsValue(int x, int y, const unsigned char *channal)
{
    double sum = 0;
    int pixStep = 3;
    for (int i : {0, 1, 2, 3, 4}) {
        for (int j : {0, 1, 2, 3, 4}) {
            int pix_y = y + i - 2;
            int pix_x = x + j - 2;
            if (pix_y < 0 || pix_y >= BmpHeight || pix_x < 0 || pix_y >= BmpWidth)
                continue;
            sum += channal[((BmpWidth * pix_y) + pix_x) * pixStep] * GsCore[i][j];
        }
    }

    return sum;
}

unsigned char* convolution(int base_y, int conv_height) 
{
    int pixStep = 3;    
    const unsigned char* Rp = pBmpBuf + 2;
    const unsigned char* Gp = pBmpBuf + 1;
    const unsigned char* Bp = pBmpBuf;
    unsigned char* resBuf = NULL;
    int conv_byte_size = BmpWidth * conv_height * pixStep;

    resBuf = new(nothrow) unsigned char[conv_byte_size];

    // rgb pointer
    unsigned char* resRp = resBuf + 2;
    unsigned char* resGp = resBuf + 1;
    unsigned char* resBp = resBuf;

    for(int i = 0; i < conv_height; i++)
        for(int j = 0; j < BmpWidth; j++) {
            *resRp = getGsValue(j, base_y + i, Rp);
            *resGp = getGsValue(j, base_y + i, Gp);
            *resBp = getGsValue(j, base_y + i, Bp);

            resRp += pixStep;
            resGp += pixStep;
            resBp += pixStep;
        }

    return resBuf;
}

int main(int argc, char *argv[]) 
{
    int size, myrank, dest;
    MPI_Status status;
    double start_time, end_time;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    start_time = MPI_Wtime();
    cout << "Task " << myrank << " start." << endl;

    BITMAPFILEHEADER BmpHead;
    BITMAPINFODEADER BmpInfo;

    // image type
    int BiBitCount;  
    unsigned char* result = NULL;

    // open in binary format
    FILE *fp = fopen(BMP_FILE_NAME, "rb");  
    if (fp == 0) {
        cerr << "Can not open " << BMP_FILE_NAME << endl;
        return 0;
    }

    fread(&BmpHead, sizeof(BITMAPFILEHEADER), 1, fp);
    fread(&BmpInfo, sizeof(BITMAPINFOHEADER), 1, fp);

    BmpWidth = BmpInfo.biWidth;    
    BmpHeight = BmpInfo.biHeight;  
    BiBitCount = BmpInfo.biBitCount;
    readBmp(fp, pBmpBuf, BmpWidth, BmpHeight, BiBitCount);
    readGsCore();

    unsigned char* resBuf = NULL;
    int base_y, convHeight, lastConvHeight;    
    int conv_byte_size;  

    result = new(nothrow) unsigned char[BmpWidth * BmpHeight * 3];
    if(result == NULL){
        cerr << "Result new error." << endl;
        exit(-1);
    }

    convHeight = BmpHeight / size;
    base_y = myrank * convHeight;            
    lastConvHeight = BmpHeight - (size - 1) * convHeight;   
    if (myrank != 0) {  
        // parameter
        if (myrank != size - 1) {
            // nothing
        }
        else {
            // left part
            convHeight = lastConvHeight;            
        }

        conv_byte_size = BmpWidth * convHeight * 3;
        resBuf = convolution(base_y, convHeight);
        if (resBuf == NULL)
            goto END;
        dest = 0;
        end_time = MPI_Wtime();
        cout << "Task " << myrank << " end, cost " << end_time - start_time << " second(s)." << endl;
        MPI_Send(resBuf, conv_byte_size, MPI_UNSIGNED_CHAR, dest, 99, MPI_COMM_WORLD);
    }
    else {   
        base_y = 0;
        resBuf = convolution(base_y, convHeight);
        if (resBuf == NULL)
            cerr << "0# resBuf error." << endl;

        conv_byte_size = BmpWidth * convHeight * 3;
        memcpy(result, resBuf, conv_byte_size);
        delete resBuf;
        resBuf = NULL;
        
        int convByteSize = BmpWidth * convHeight * 3; 
        int lastConvByteSize = BmpWidth * lastConvHeight * 3; 
        
        resBuf = new(nothrow) unsigned char[lastConvByteSize]; 
        for (int i = 0; i < size - 1; i++) {
            MPI_Recv(resBuf, conv_byte_size, MPI_UNSIGNED_CHAR, MPI_ANY_SOURCE, 99, MPI_COMM_WORLD, &status);
            memcpy(result + (status.MPI_SOURCE * convHeight * BmpWidth * 3), resBuf, (status.MPI_SOURCE == size - 1) ? lastConvByteSize : convByteSize);
        }
        end_time = MPI_Wtime();
        cout << "Task " << myrank << " end, cost " << end_time - start_time << " second(s)." << endl;
        saveBmp("result.bmp", result, BmpWidth, BmpHeight, BiBitCount);
    }

END:
    if (resBuf) delete resBuf;
    MPI_Finalize();
    // MPI End

    if (pBmpBuf) delete pBmpBuf;
    if (result) delete result;

    fclose(fp);

    return 0;
}
