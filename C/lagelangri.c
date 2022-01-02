#include <stdio.h>
#define MAX 20
//输入点的结构
typedef struct stPoint
{
    double x;
    double y;
} Point;

int main()
{
    int n;
    int i,j;
    int k, found = 0;
    Point points[MAX];

    double x,tmp,lagrange=0;//这个x是你将要计算的f(x)插值点，tmp是拉格朗日基函数，larange是根据拉格朗日函数得出f(x)的值
    printf("请输入被插值点的个数:");
    scanf("%d",&n);
    if(n>MAX || n <=0)
    {
        return 1;
    }
   //输入插值点的x值和y值
  printf("请输入插值点的x值和y值：\n");
   for(i=0;i<=n;i++)
      scanf("%lf%lf",&points[i].x,&points[i].y);
    printf("\n多项式的x值:");
    scanf("%lf",&x);
    for(i=0;i<=n;i++)
    {
        for(j=0,tmp=1;j<=n;j++)
        {
            if(j==i)   
            continue; 
            tmp=tmp*(x-points[j].x)/(points[i].x-points[j].x);//套公式
        }
        lagrange=lagrange+tmp*points[i].y; 
    }  
    printf("\nf(%lf)=%lf\n",x,lagrange);
    return 0;
}
