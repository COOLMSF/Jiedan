#include<stdio.h>

int main()
{
	int burst_t[10],process[10],n,temp,i,j,w_time[10],sum=0;
	float average;

    // 输入进程数量
	printf("Enter number  of process:");
	scanf("%d",&n);

    // 输入突发时间，CPU运行时间
	printf("\n Enter burst time for each process:");
    
    // 对于n个进程
	for(i=0;i<n;i++)
	{
		printf("\nBurst time of process P%d:",i);
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
	printf("\n Waiting time for each process:-");
	for(i=0;i<n;i++)
	{
		printf("\n Waiting time for process P%d is %d sec.",process[i],w_time[i]);
		
	}
	printf("\n Average waiting time is %f sec.",average);
	return 0;
}
