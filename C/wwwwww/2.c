#include<stdio.h>

int main()

{

int i, j; // i, j控制行或列

printf("\n输出9*9乘法表三角形形状1：\n");

printf("-------------------------------------------------------------------------\n");

for (i = 1; i <= 9; i++)

{

for (j = 1; j <= 9; j++)

// %2d 控制宽度为两个字符，且右对齐；如果改为 %-2d 则为左对齐

// \t为tab缩进

printf("%d*%d=%2d\t", i, j, i*j);

printf("\n");

}


puts("");

    for(i=1;i<=9;i++){
        for(j=1;j<=9;j++){
            if(j<i)
                //打印八个空格，去掉空格就是左上三角形 
                printf("        ");
            else
                printf("%d*%d=%2d  ",i,j,i*j);
        }

        printf("\n");  
    }

    return 0;
}

