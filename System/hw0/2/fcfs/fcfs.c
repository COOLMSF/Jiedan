#include<stdio.h>
#include<stdlib.h>

void swap(int *a,int *b){
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
}

int main()
{
    int n,i,j,w,t,s;

    float avt=0,avw=0;
    int *p=NULL,*a=NULL,*b=NULL;

    printf("Enter the number of processes:\n");
    scanf("%d",&n);

    allocmem();

    for(i=0;i<n;i++){
        printf("Enter process id, arrival time, burst time\n");
        scanf("%d%d%d",&p[i],&a[i],&b[i]);
    }

    for(i=1;i<n;i++){
        for(j=i-1;j>=0&&a[j]>a[i];j--){
            swap(&a[i],&a[j]);
            i--;
        }
    }

    printf("Process\tAT\tBT\tWT\tTT\n");
    printf("%d\t%d\t%d\t%d\t%d\n",p[0],a[0],b[0],w,t);
    for(i=1;i<n;i++){

        s=t+a[i-1];
        w=s-a[i];
        t=s+b[i]-a[i];
        printf("%d\t%d\t%d\t%d\t%d\n",p[i],a[i],b[i],w,t);
        avw+=w;
        avt+=t;
    }
    avt/=n;
    avw/=n;
    printf("\nAverage waiting time = %f\n",avw);
    printf("\nAverage turnaround time = %f\n",avt);
    return 0;
}
