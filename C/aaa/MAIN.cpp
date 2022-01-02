#include<string.h>
#include<stdio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _dim {
    int dim1;
    int dim2;
    int dim3;
};

struct _dim dim_map, dim_w;

#define MAX_BUF 255
#define MAP(i,j,k) (map[dim_map.dim2*dim_map.dim3*i + dim_map.dim3*j + k])
#define W(i,j,k) (w[dim_w.dim2*dim_w.dim3*i + dim_w.dim3*j + k])

float *maxtrix_from_file_to_array(FILE *fp, struct _dim dim)
{
	float *array;
    char *buf;
    char line[MAX_BUF] = { 0 };

    array = (float *)malloc(dim.dim1 * dim.dim2 * dim.dim3 * sizeof(float));

    if (array == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    // handle every line
    while (fgets(line, MAX_BUF, fp)) {
        if (strcmp(line, "\r\n") == 0)
          continue;
        // 分割
        buf = strtok(line, ",");
        while (buf) {
            // 转化为整数
            array[i] = atoi(buf);
            buf = strtok(NULL, ",");
            i++;
        }
    }

    return array;
}

int read_data_dim1(FILE *fp, struct _dim *dim)
{
    char line[MAX_BUF] = { 0 };
    char dim1 = 1;

    while (fgets(line, MAX_BUF, fp)) {
        if (strcmp(line, "\r\n") == 0)
            dim1++;
    }
    dim->dim1 = dim1;
}

int read_data_dim2(FILE *fp, struct _dim *dim)
{
    char line[MAX_BUF] = { 0 };
    char dim2 = 0;

    while (fgets(line, MAX_BUF, fp)) {
        if (strcmp(line, "\r\n") == 0)
            break;
        dim2++;
    }
    dim->dim2 = dim2;
}

int read_data_dim3(FILE *fp, struct _dim *dim)
{
    char line[MAX_BUF] = { 0 };
    char dim3 = 1;

    fgets(line, MAX_BUF, fp);

    for (int i = 0; i < strlen(line); i++) {
        if (line[i] == ',')
            dim3++;
    }
    dim->dim3 = dim3;
}

// float map[2][10][10] = { {
//     0,1,2,3,4,5,6,7,8,9,
//     9,8,7,6,5,4,3,2,1,0,
//     0,1,2,3,4,5,6,7,8,9,
//     9,8,7,6,5,4,3,2,1,0,
//     0,1,2,3,4,5,6,7,8,9,
//     9,8,7,6,5,4,3,2,1,0,
//     0,1,2,3,4,5,6,7,8,9,
//     9,8,7,6,5,4,3,2,1,0,
//     0,1,2,3,4,5,6,7,8,9,
//     9,8,7,6,5,4,3,2,1,0
// } ,
// {
//     0,1,2,3,4,5,6,7,8,9,
//     9,8,7,6,5,4,3,2,1,0,
//     0,1,2,3,4,5,6,7,8,9,
//     9,8,7,6,5,4,3,2,1,0,
//     0,1,2,3,4,5,6,7,8,9,
//     9,8,7,6,5,4,3,2,1,0,
//     0,1,2,3,4,5,6,7,8,9,
//     9,8,7,6,5,4,3,2,1,0,
//     0,1,2,3,4,5,6,7,8,9,
//     9,8,7,6,5,4,3,2,1,0
// } };
//
#define K1 2
#define M1 10    //输入图像的行号
#define N1 10 //输入图像的列号 
#define M2 3    //卷积核的行号
#define N2 3 //卷积核的列号
#define S1 200

// float w[K1][M2][N2] = { {{ 2, 2, 2 }, { 1, 1, 1 }, { 3, 3, 3 }}, {{ 2, 2, 2 }, { 1, 1, 1 }, { 3, 3, 3 }} };
float g[K1][M1 + M2 - 1][N1 + N2 - 1] = { 0 };
float g2[K1][M1][N1];

void conv(float *map, float *w, float g[K1][M1 + M2 - 1][N1 + N2 - 1])
{
    int i, j, m, n,k;
    for (k = 0; k < K1; k++) 
    {
        for (i = 0; i < M1 + M2 - 1; i++)
        {
            for (j = 0; j < N1 + N2 - 1; j++)
            {
                float temp = 0;
                for (m = 0; m < M1; m++)
                {
                    for (n = 0; n < N1; n++)
                    {
                        if ((i - m) >= 0 && (i - m) < M2 && (j - n) >= 0 && (j - n) < N2)
                            temp += MAP(k, m, n) * W(k, i - m, j - n);
                        g[k][j][i] = temp;
                        
                    }
                }
            }
        }
    }
    for (k = 0; k < K1; k++)
    {
        for (i = 0; i < M1; i++)
        {
            for (j = 0; j < N1; j++)
            {
                g2[k][i][j] = g[k][i + (M2 - 1) / 2][j + (N2 - 1) / 2];
            }
        }
    }
}
void BN(float f[K1][M1][N1])
{
    int i, j, k;
    float nor = 0;
    float mean_k = 0;
    float var = 0;
    float var_k = 0;
    for (int k = 0; k < K1; k++)
    {
        for (int i = 0; i < M1; i++)
        {
            for (int j = 0; j < N1; j++)
            {
                nor += f[k][i][j];
            }

        }

    }
    
    mean_k = nor / S1;
    for (int k = 0; k < K1; k++)
    {
        for (int i = 0; i < M1; i++)
        {
            for (int j = 0; j < N1; j++)
            {
                var+= (f[k][i][j]-mean_k)* (f[k][i][j] - mean_k);
            }

        }

    }
    
    var_k=var/ S1;
    for (int k = 0; k < K1; k++)
    {
        for (int i = 0; i < M1; i++)
        {
            for (int j = 0; j < N1; j++)
            {
                f[k][i][j] = (f[k][i][j] - mean_k)/sqrt(var_k);
            }

        }

    }
}
void  Relu(float f[K1][M1][N1])
{
    int i, j, k;
    for (int k = 0; k < K1; k++)
    {
        for (int i = 0; i < M1; i++)
        {
            for (int j = 0; j < N1; j++)
            {
                if (f[k][i][j]<0)
                f[k][i][j]=0;
            }
           
        }
      
    }

}


int main()
{
//
    
    // 从conv.txt里面读取数据到fp_map
    FILE *fp_map = NULL;
    /// 从mat.txt读取数据到fp_w
    // float w[K1][M2][N2] = { {{ 2, 2, 2 }, { 1, 1, 1 }, { 3, 3, 3 }}, {{ 2, 2, 2 }, { 1, 1, 1 }, { 3, 3, 3 }} };
    FILE *fp_w = NULL;
    float *map;
    float *w;

    fp_map = fopen("conv.txt", "r");
    if (fp_map == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    fp_w = fopen("mat.txt", "r");
    if (fp_w == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    // 计算map矩阵维度
    read_data_dim1(fp_map, &dim_map);
    // 刷新文件指针
    rewind(fp_map);
    read_data_dim2(fp_map, &dim_map);
    rewind(fp_map);
    read_data_dim3(fp_map, &dim_map);
    rewind(fp_map);

    // 计算w矩阵维度
    read_data_dim1(fp_w, &dim_w);
    // 刷新文件指针
    rewind(fp_w);
    read_data_dim2(fp_w, &dim_w);
    rewind(fp_w);
    read_data_dim3(fp_w, &dim_w);
    rewind(fp_w);

    map = maxtrix_from_file_to_array(fp_map, dim_map);
    w = maxtrix_from_file_to_array(fp_w, dim_w);

    // puts("");
    // puts("Map data");
    // for (int i = 0; i < dim_map.dim1 * dim_map.dim2 * dim_map.dim3; i++)
    //     printf("%d ", map[i]);
    // puts("");

    // puts("");
    // puts("W data");
    // for (int i = 0; i < dim_w.dim1 * dim_w.dim2 * dim_w.dim3; i++)
    //     printf("%d ", w[i]);
    // puts("");

    for (int k = 0; k < K1; k++)
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                printf("%f ", MAP(k, i, j));
            }
            printf("\n");
        }
        printf("\n");
    }
    conv(map, w, g);
    // BN(g2);
    // Relu(g2);

    for (int k = 0; k < K1; k++)
    { 
        for (int i = 0; i < M1; i++)
        {
            for (int j = 0; j < N1; j++)
            {
                printf("%f  ", g2[k][i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
    //getchar();

	
	return 0;
}
