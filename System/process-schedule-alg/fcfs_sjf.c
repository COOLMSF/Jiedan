#include<stdio.h>
#include<stdlib.h>
#include <string.h>

// 交换整形变量 a，b
void swap(int *a,int *b){

    // 使用临时变量temp交换时间
    int temp;

    temp=*a;
    *a=*b;
    *b=temp;
}

// 先来先服务器
int fcfs()
{
    int n,i,j,w,t,s;

    // 平均周转时间
    // 平均等待时间
    float avt=0,avw=0;
    
    int *p=NULL,*a=NULL,*b=NULL;

    printf("请输入进程数量:\n");
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
        printf("请输入进程id，到达时间，突发时间\n");
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

    printf("进程\t到达时间\t突发时间\t等待时间\t周转时间\t结束时间\n");
    printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",p[0],a[0],b[0],w,t,a[0]+b[0]+w);
    for(i=1;i<n;i++){
        // 如果到达时间大于周转时间
        if(a[i]>t){
            w=0;
            t=t+b[i]-a[i];
            // printf("%d\t%d\t%d\t%d\t%d\n",p[i],a[i],b[i],w,t);
            printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",p[i],a[i],b[i],w,t,a[i]+b[i]+w);
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
        // printf("%d\t%d\t%d\t%d\t%d\n",p[i],a[i],b[i],w,t);
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",p[i],a[i],b[i],w,t,a[i]+b[i]+w);
        avw+=w;
        avt+=t;
    }
    // 计算平均值
    avt/=n;
    avw/=n;
    printf("\n平均等待时间 = %f\n",avw);
    printf("\n平均周转时间 = %f\n",avt);
}

// 短作业优先
int sjf()
{
	int burst_t[10],process[10],n,temp,i,j,w_time[10],sum=0;
	float average;

    // 输入进程数量
	printf("输入进程数量:");
	scanf("%d",&n);

    // 输入突发时间，CPU运行时间
	printf("\n 输入每个进程的突发时间:");
    
    // 对于n个进程
	for(i=0;i<n;i++)
	{
		printf("\nP%d 的突发时间:",i);
		scanf("%d",&burst_t[i]);
		process[i]=i;
	}

    // 根据突发时间进行排序
	for(i=0;i<n-1;i++)
	{
		for(j=i+1;j<n;j++)
		{
            // 交换条件
			if(burst_t[i]>burst_t[j])
			{
                // 交换突发时间
				temp=burst_t[i];
				burst_t[i]=burst_t[j];
				burst_t[j]=temp;

                // 交换进程
				temp=process[i];
				process[i]=process[j];
				process[j]=temp;
			}
		}
	}
    // 初始化等待时间
	w_time[0]=0;
	for(i=1;i<n;i++)
	{
		w_time[i]=w_time[i-1]+burst_t[i-1];
	}
	for(i=0;i<n;i++)
	{
		sum+=w_time[i];
	}
	average=(float)sum/n;
	printf("\n 每个进程的等待时间:-");
	for(i=0;i<n;i++)
	{
		printf("\n 进车P%d 的等待时间是 %d 秒.",process[i],w_time[i]);
		
	}
	printf("\n 平均等待时间是%f 秒.",average);
	return 0;
}


int main(int argc, char *argv[])
{
    char alg_name[100] = { 0 };
    puts("请输入要运行的算法(fcfs, sjf):");

    scanf("%s", alg_name);

    if (strcmp(alg_name, "fcfs") == 0) {
        fcfs();
        return 1;
    } else if (strcmp(alg_name, "sjf") == 0) {
        sjf();
        return 1;
    } else {
        puts("找不到该算法");
        return -1;
    }
}
