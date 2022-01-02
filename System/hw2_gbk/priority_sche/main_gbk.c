#include<stdio.h>
#include<string.h>

// 进程结构体
struct process{
char name[10];
int at,bt,pr,wt,tt,sta;
}p[20];

struct done{
char name[10];
int st,ct;
}d[20];

void read(int n)
{
    int i;
    printf("\n输入进程信息\n");
    for(i=0;i<n;i++)
    {
     printf("\nname:");
     scanf("%s",p[i].name);
     printf("\nat:");
     scanf("%d",&p[i].at);
     printf("\nbt:");
     scanf("%d",&p[i].bt);
     printf("\npriority:");
     scanf("%d",&p[i].pr);
     p[i].sta=0;
    }
}
// 
int ps(int n)
{
	int ls,i,j,k,num,idle,found;
	idle=0;
	for(ls=0,i=0,num=0;ls<n;)
	{
        // 更新状态
		found=0;
		for(j=0;j<n;j++)
		{
		if(found==0 && p[j].sta==0 && p[j].at<=i)
			{
				found++;
				k=j;
			}
		if(found>0 && p[j].sta==0 && p[j].at<=i)
			{
				if(p[j].pr<p[k].pr)
					{
					k=j;
					}
			}
		}
        // 如果没找到
		if(found==0 && idle==0)
		{
			idle=1;
			strcpy(d[num].name,"idle");
			d[num].st=i;
			i++;
		}
		else if(found==0 && idle==1)
		{
			i++;
		}
		else if(found>0)
		{
			if(idle==1)
				{
				d[num].ct=i;
				num++;
				idle=0;
				}
            // 复制字符串
			strcpy(d[num].name,p[k].name);
			d[num].st=i;
			d[num].ct=i+p[k].bt;
			num++;
			p[k].wt=i-p[k].at;
			p[k].tt=p[k].wt+p[k].bt;
			i=i+p[k].bt;
            // 更新状态
			p[k].sta=1;
			ls++;
		}
	}
        return(num);
}

void display(int n,int num)
{
  int i,j;
  printf("\nname\tat\tbt\twt\ttt\n");
  for(j=0;j<n;j++)
  {
  printf("%s\t%d\t%d\t%d\t%d\n",p[j].name,p[j].at,p[j].bt,p[j].wt,p[j].tt);
  }
	for(i=0;i<num;i++)
	{
		printf("--------");
	}
	printf("\n");
	for(i=0;i<num;i++)
	{
		printf("|%s\t",d[i].name);
	}
	printf("|\n");
	for(i=0;i<num;i++)
	{
		printf("--------");
	}
	printf("\n");
	for(i=0;i<num;i++)
	{
		printf("%d\t",d[i].st);
	}
	printf("%d\n",d[i-1].ct);
  printf("\n");
}

void main()
{
int n,i,j,k,p;
printf("\n输入进程数:");
scanf("%d",&n);
read(n);
p=ps(n);
display(n,p);
}

