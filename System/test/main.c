#define false 0
#define true 1
#define n 4
#define m 10
struct
{
char type[10];
int count;
int remain;
int address;
}equiptype[n];
struct
{
int number;
int status;
int remain;
char jobname[4];
int lnumber;
}equipment[m];
allocate(J,type,mm)
char *J,*type;
int mm;
{
int i,t,j;

i=0;
while(i<n&&strcmp(equiptype[i].type,type)!=0)
i++;
if(i>=n)
{
printf("该类设备,设备配失败");
return(false);
}
if(equiptype[i].remain<1)
{
printf("该类设备足配失败");
return(false);
}
t=equiptype[i].address;
while(!(equipment[t].status==1 && equipment[t].remain==0))
t++;

equiptype[i].remain--;
equipment[t].remain=1;
strcpy(equipment[t].jobname,J);
equipment[t].lnumber=mm;
}
reclaim (J,type)
char J,type;
{
int i,t,j,k,nn;
i=0;
while(i<n&&strcmp(equiptype[i].type,type)!=0)
i++;
if(i>=n)
{
printf("该类设备,设备收失败");
return(false);
}
t=equiptype[i].address;
j=equiptype[i].count;
k=0;
nn=t+j;
for(;t<nn;t++)
if(strcmp(equipment[t].jobname,J)==0&&equipment[t].remain==1)
{
equipment[t].remain=0;
k++;
}
equiptype[i].remain= equiptype[i].remain+k;
if(k==0)
printf("该作业没使用该类设备\n");
}
main( )
{
char J[4];
int i,mm,a;
char type[10];

strcpy(equiptype[0].type,"input");
equiptype[0].count=2;
equiptype[0].remain=2;
equiptype[0].address=0;
strcpy(equiptype[1].type,"printer");
equiptype[1].count=3;
equiptype[1].remain=3;
equiptype[1].address=2;
strcpy(equiptype[2].type,"disk");
equiptype[2].count=4;
equiptype[2].remain=4;
equiptype[2].address=5;
strcpy(equiptype[3].type,"tape");
equiptype[3].count=1;
equiptype[3].remain=1;
equiptype[3].address=9;

for(i=0;i<10;i++)
{
equipment[i].number=i;
equipment[i].status=1;
equipment[i].remain=0;
}
while(1)
{
printf("\n0－退1－配2－收3－显示");
printf("\n选择功能项（0~3）:");
scanf("%d",&a);
switch(a)
{
case 0 :
exit(0);
case 1 :
printf("输入作业名、作业所需设备类设备相号");
scanf("%s%s%d",J,type,&mm);
allocate(J,type,mm);
break;
case 2:
printf("输入作业名作业归设备类");
scanf("%s%s",J,type);
reclaim(J,type);
break;
case 3:
printf("\n输设备类表\n");
printf(" 设备类型 设备总量 空闲设备\n");
for(i=0;i<n;i++)
printf("%9s%8d%9d\n",equiptype[i].type,equiptype[i].count, equiptype[i].remain);
printf("输设备表:\n");
printf("绝号 /坏 已/未配 占用作业名 相号\n");
for(i=0;i<m;i++)
printf("%3d%8d%9d%12s%8d\n",equipment[i].number, equipment[i].status,equipment[i].remain,equipment[i].jobname,
equipment[i].lnumber);
}
}
}
