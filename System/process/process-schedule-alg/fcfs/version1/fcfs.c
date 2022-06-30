#include<stdio.h>
#include<stdlib.h>

// 交换整形变量 a，b
void swap(int *a,int *b){

    // 使用临时变量temp交换时间
    int temp;

    temp=*a;
    *a=*b;
    *b=temp;
}

// main函数
int main()
{
    int n,i,j,w,t,s;

    // 平均周转时间
    // 平均等待时间
    float avt=0,avw=0;
    
    int *p=NULL,*a=NULL,*b=NULL;

    printf("Enter the number of processes:\n");
    // 输入n个进程
    scanf("%d",&n);

    // 分配内存
    a=(int *)malloc(n*sizeof(int));
    // 内存分配出错
    // 下面也是一样的
    if (a == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    b=(int *)malloc(n*sizeof(int));
    if (b == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    p=(int *)malloc(n*sizeof(int));
    if (p == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    // 输入进程，id，到达时间，运行时间
    for(i=0;i<n;i++){
        printf("Enter process id, arrival time, burst time\n");
        scanf("%d%d%d",&p[i],&a[i],&b[i]);
    }

    // 按照到达时间进行排序
    for(i=1;i<n;i++){
        // sort according to arrive time
        for(j=i-1;j>=0&&a[j]>a[i];j--){
            swap(&a[i],&a[j]);
            swap(&b[i],&b[j]);
            swap(&p[i],&p[j]);
            i--;
        }
    }
    s=a[0];
    
    // 计算等待时间
    w=s-a[0];

    // 计算周转时间
    t=b[0]+s-a[0];

    // 周转时间
    avt+=t;

    // 等待时间
    avw+=w;

    printf("Process\tAT\tBT\tWT\tTT\n");
    printf("%d\t%d\t%d\t%d\t%d\n",p[0],a[0],b[0],w,t);
    for(i=1;i<n;i++){
        // 如果到达时间大于周转时间
        if(a[i]>t){
            w=0;
            t=t+b[i]-a[i];
            printf("%d\t%d\t%d\t%d\t%d\n",p[i],a[i],b[i],w,t);
            // 对于每一个进行都进行相加
            // 相加等待时间
            avw+=w;

            // 相加周转时间
            avt+=t;
        }
        // 前一个进程的到达时间 
        s=t+a[i-1];
        // 等待时间
        w=s-a[i];
        // 周转时间
        t=s+b[i]-a[i];
        printf("%d\t%d\t%d\t%d\t%d\n",p[i],a[i],b[i],w,t);
        avw+=w;
        avt+=t;
    }
    // 计算平均值
    avt/=n;
    avw/=n;
    printf("\nAverage waiting time = %f\n",avw);
    printf("\nAverage turnaround time = %f\n",avt);
    return 0;
}
