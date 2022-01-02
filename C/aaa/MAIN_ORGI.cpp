#include<string.h>
#include<stdio.h>
#include <math.h>
float map[2][10][10] = { {
    0,1,2,3,4,5,6,7,8,9,
    9,8,7,6,5,4,3,2,1,0,
    0,1,2,3,4,5,6,7,8,9,
    9,8,7,6,5,4,3,2,1,0,
    0,1,2,3,4,5,6,7,8,9,
    9,8,7,6,5,4,3,2,1,0,
    0,1,2,3,4,5,6,7,8,9,
    9,8,7,6,5,4,3,2,1,0,
    0,1,2,3,4,5,6,7,8,9,
    9,8,7,6,5,4,3,2,1,0
} ,
{
    0,1,2,3,4,5,6,7,8,9,
    9,8,7,6,5,4,3,2,1,0,
    0,1,2,3,4,5,6,7,8,9,
    9,8,7,6,5,4,3,2,1,0,
    0,1,2,3,4,5,6,7,8,9,
    9,8,7,6,5,4,3,2,1,0,
    0,1,2,3,4,5,6,7,8,9,
    9,8,7,6,5,4,3,2,1,0,
    0,1,2,3,4,5,6,7,8,9,
    9,8,7,6,5,4,3,2,1,0
} };
#define K1 2
#define M1 10    //输入图像的行号
#define N1 10 //输入图像的列号 
#define M2 3    //卷积核的行号
#define N2 3 //卷积核的列号
#define S1 200

float w[K1][M2][N2] = { {{ 2, 2, 2 }, { 1, 1, 1 }, { 3, 3, 3 }}, {{ 2, 2, 2 }, { 1, 1, 1 }, { 3, 3, 3 }} };
float g[K1][M1 + M2 - 1][N1 + N2 - 1] = { 0 };
float g2[K1][M1][N1];

void conv(float f[K1][M1][N1], float con[K1][M2][N2], float g[K1][M1 + M2 - 1][N1 + N2 - 1])
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
                            temp += f[k][m][n] * con[k][i - m][j - n];
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
    for (int k = 0; k < K1; k++)
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                printf("%f ", map[k][i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
    conv(map, w, g);
    //BN(g2);
    //Relu(g2);

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
