#include<stdio.h>

#include<stdlib.h>

#include<string.h>

typedef struct{

double number;//订单编号

char name[20];//姓名

char id[20];//身份证号

int count;//数量

char p[20];//航班号

}GUEST;

typedef struct{

char num[20];//航班号

char depart[30];//出发城市

char arrive[30];//到达城市

char start[20];//起飞时间

char end[20];//到达时间

int price;//价格

int discount;//折扣率（%）

int total;//总票数

int rest;//剩余票数

int t;//订单数

GUEST guest[20];//乘客

}PLANE;

PLANE plane[20];

int n;//n为航班数

void inputplane(){//输入航班

int i;

printf("输入总航班数：");

scanf("%d",&n);

printf("输入航班信息：\n");

printf("航班号  出发城市  到达城市  起飞时间  到达时间  价格  折扣率  总票数  剩余票数\n");

for(i=0;i<n;i++)

scanf("%s   %s     %s     %s     %s     %d     %d    %d    %d",plane[i].num,plane[i].depart,plane[i].arrive,plane[i].start,plane[i].end,&plane[i].price,&plane[i].discount,&plane[i].total,&plane[i].rest);

}

void list(){//显示

int i;

printf("航班号  出发城市  到达城市  起飞时间  到达时间  价格  折扣率  总票数  剩余票数\n");

for(i=0;i<n;i++)

printf("%s     %s     %s     %s    \t%s\t%d      %d\t%d \t%d\n",plane[i].num,plane[i].depart,plane[i].arrive,plane[i].start,plane[i].end,plane[i].price,plane[i].discount,plane[i].total,plane[i].rest);

}

void search1(){//按航班号查询

int i;

char num[20];

printf("输入你查询的航班号：");

scanf("%s",num);

for(i=0;i<n;i++)

{

if(strcmp(num,plane[i].num)==0)

{

printf("航班号  出发城市  到达城市  起飞时间  到达时间  价格  折扣率  总票数  剩余票数\n");

printf("%s     %s     %s     %s    \t%s\t%d     %d\t%d \t%d\n",plane[i].num,plane[i].depart,plane[i].arrive,plane[i].start,plane[i].end,plane[i].price,plane[i].discount,plane[i].total,plane[i].rest);

break;

}

}

if(i==n)

printf("没有此航班！\n");

}

void search2(){//按起飞抵达城市查询

int i;

char a[50],b[50];

printf("输入起飞城市和到达城市：");

scanf("%s %s",a,b);

printf("航班号  出发城市  到达城市  起飞时间  到达时间  价格  折扣率  总票数  剩余票数\n");

for(i=0;i<n;i++)

{

if((strcmp(a,plane[i].depart)==0)&&(strcmp(b,plane[i].arrive)==0))

printf("%s     %s     %s     %s   \t%s\t%d    %d\t%d \t%d\n",plane[i].num,plane[i].depart,plane[i].arrive,plane[i].start,plane[i].end,plane[i].price,plane[i].discount,plane[i].total,plane[i].rest);

}

printf("\n");

for(i=0;i<n;i++)

{

if((strcmp(a,plane[i].depart)==0)&&(strcmp(b,plane[i].arrive)==0))

break;

}

if(i==n)

printf("没有此航班！\n");

}

void book(){//订票

char name[20],p[20],id[20];

double number;

int i,j,k,y,count;

for(i=0;i<n;i++)

plane[i].t=0;

do

{

printf("输入订单信息：\n");

printf("订单编号  姓名  身份证号  订票数  航班号\n");

scanf("%d %s %s %d %s",&number,name,id,&count,p);

for(i=0;i<n;i++)

{

if(strcmp(p,plane[i].num)==0)

break;

}

if(i==n)

printf("没有此航班\n");

else

{

if(plane[i].rest>=count)

{

j=plane[i].t;

plane[i].guest[j].number=number;

strcpy(plane[i].guest[j].name,name);

strcpy(plane[i].guest[j].id,id);

plane[i].guest[j].count=count;

strcpy(plane[i].guest[j].p,p);

plane[i].rest-=count;

plane[i].t++;

}

else

{

printf("很抱歉，该航班剩余票数为 %d 张\n",plane[i].rest);

for(k=0;k<n;k++)

{

if((strcmp(plane[i].depart,plane[k].depart)==0)&&(strcmp(plane[i].depart,plane[k].depart)==0))

break;

}

if(k==n)

printf("没有其他从%s到%s的航班\n",plane[i].depart,plane[i].arrive);

else

{

printf("从%s到%s还有 %s 航班\n\n",plane[k].depart,plane[k].arrive,plane[k].num);

printf("航班号  出发城市  到达城市  起飞时间  到达时间  价格  折扣率  总票数  剩余票数\n");

printf("%s     %s     %s     %s   \t%s\t%d     %d\t%d \t%d\n",plane[k].num,plane[k].depart,plane[k].arrive,plane[k].start,plane[k].end,plane[k].price,plane[k].discount,plane[k].total,plane[k].rest);

}

}

}

printf("是否继续订票，“是”输入1，“否”输入0\n");

scanf("%d",&y);

}while(y);

}

void quit(){ //退票

double number;

char id[20];

int i,j,temp,k,y;

temp=0;

printf("请输入您的订单编号:\n");

scanf("%d",&number);

printf("请输入您的身份证：\n");

scanf("%s",id);

for(i=0;i<n;i++)

{

for(j=0;j<plane[i].t;j++)

{

if(number==plane[i].guest[j].number&&(strcmp(id,plane[i].guest[j].id)==0))

{

temp=1;

break;

}

}

if(temp==1)

break;

}

if(i==n)

printf("没有此订单！\n");

else

{

printf("订单编号  姓名  身份证号  订票数  航班号\n");

printf("    %d",plane[i].guest[j].number);

printf("     %s",plane[i].guest[j].name);

printf("     %s",plane[i].guest[j].id);

printf("     %d",plane[i].guest[j].count);

printf("     %s\n",plane[i].guest[j].p);

printf("您是否确认删除(1/0)\n");

scanf("%d",&y);

if(y==1)

{

plane[i].rest+=plane[i].guest[j].count;

for(k=j+1;k<plane[i].t;k++)

{

plane[i].guest[k-1].number=plane[i].guest[k].number;

strcpy(plane[i].guest[k-1].name,plane[i].guest[k].name);

strcpy(plane[i].guest[k-1].id,plane[i].guest[k].id);

plane[i].guest[k-1].count=plane[i].guest[k].count;

strcpy(plane[i].guest[k-1].p,plane[i].guest[k].p);

}

plane[i].t--;

printf("退票成功!!\n");

}

}

}


void change()//修改

{

char a[20];

int i;

printf("请输入你要修改的航班号:");

scanf("%s",a);

for(i=0;i<n;i++)

{

if(strcmp(a,plane[i].num)==0)

break;

}

if(i==n)

printf("没有此航班！\n");

else

{

printf("原信息:\n");

printf("航班号  出发城市  到达城市  起飞时间  到达时间  价格  折扣率  总票数  剩余票数\n");

printf("%s    %s     %s     %s    \t%s\t%d    %d\t%d \t%d\n",plane[i].num,plane[i].depart,plane[i].arrive,plane[i].start,plane[i].end,plane[i].price,plane[i].discount,plane[i].total,plane[i].rest);

printf("请输入修改后的信息:\n");

printf("航班号  出发城市  到达城市  起飞时间  到达时间  价格  折扣率  总票数  剩余票数\n");

scanf(" %s    %s    %s    %s    %s   %d    %d    %d    %d",plane[i].num,plane[i].depart,plane[i].arrive,plane[i].start,plane[i].end,&plane[i].price,&plane[i].discount,&plane[i].total,&plane[i].rest);

}

}

int main()

{

int a,b;

do

{

system("cls");

for(a=0;a<50;a++)

printf("*");

printf("\n");

printf("\t\t1： 输入航班信息\n");

printf("\t\t2： 列出航班信息\n");

printf("\t\t3： 按航班号查询航班信息\n");

printf("\t\t4： 按出发到达城市查询航班信息\n");

printf("\t\t5： 订票\n");

printf("\t\t6： 退票\n");

printf("\t\t7： 修改航班信息\n");

printf("\t\t8： 退出程序\n");

for(a=0;a<50;a++)

printf("*");

printf("\n");

printf("请输入功能选项1-8)：\n");

scanf("%d",&b);

switch(b)

{

case 1:

inputplane();

system("pause");

break;

case 2:

list();

system("pause");

break;

case 3:

search1();

system("pause");

break;

case 4:

search2();

system("pause");

break;

case 5:

book();

system("pause");

break;

case 6:

quit();

system("pause");

break;

case 7:

change();

system("pause");

break;

case 8:
	
return 0;

}

}while(1);

}
