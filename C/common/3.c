#include<stdio.h>
int main()
{
    int i,j;
    int n;
    printf("Input n:");
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=i;j++)
        {
            printf("%4d",i*j);
        }
        printf("\n");
    }
    return 0;
}