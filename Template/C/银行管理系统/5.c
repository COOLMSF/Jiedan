#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <ctime>
#include <string.h>
#include <iostream.h>
#define n 3
int vip1=0;
int y,z;
float sum1=0,sum2=0,sum3=0,sum4=0,sum5=0;
float i1=0,i2=0,i3=0,i4=0,i5=0;
float ave1=0,ave2=0,ave3=0,ave4=0,ave5=0;
typedef struct List
{
  int A[n+1];           //顾客用来办理业务的N个窗口
  int len;              //表示数组中的元素个数
}List;

typedef struct Lnode
{            //链表结点类型
  int data;
  struct Lnode *next;
}Lnode;
typedef struct Linkqueue
{       //链式存储的等候队列的类型定义
  Lnode *front;
  Lnode *rear;
}Linkqueue;

List L;
Linkqueue Q;
void Initshuzu()        //初始化数组
{
  int i;
  for(i=1;i<=n;i++)
  L.A[i]=0;             //元素值为0，表示编号为I的窗口当前状态为空
  L.len=0;
}
 void Initqueue()       //初始化队列的算法
{
  Q.front=Q.rear=(Lnode *)malloc(sizeof(Lnode));
  Q.front->next=NULL;
}
void Enqueue(Linkqueue *Q,int elem)  //进队算法
{
   Lnode *s;
   s=(Lnode *)malloc(sizeof(Lnode));
   s->data=elem;
   s->next=NULL;
   Q->rear->next=s;
   Q->rear=s;
}
int Dlqueue(Linkqueue *Q)  //出队算法
{
   Lnode *t;
   int x;
   if(Q->front==Q->rear)
   {
	   printf("队列为空！\n");
	   exit(1);
   }
   else
   {
	   t=Q->front->next;
       Q->front->next=t->next;
       x=t->data;
       free(t);
	   return x;
   }
}
void printl()    //输出数组算法
{ 
	int i;
    printf("  正在办理业务的顾客编号为：  一号柜台        二号柜台        三号柜台\n");
	printf("                              ");
    for( i=1;i<=L.len;i++)
	{
		printf("%d 号客户        ",L.A[i]);
      
	}
	printf("\n"); 
}
void print2()    //输出队列算法
{   
	Lnode *s;
	int i=0;
    printf("     正在等候办理业务的顾客编号为：");
    s=Q.front->next;
    while(s!=NULL)
	{
		printf("%d ",s->data);
        s=s->next;
	    i++;
	}
	printf("\n     您的前面一共有 %d 人在排队，请您稍候！",i);
	printf("\n");
}
void daoda(int x)   //解决顾客到达事件算法
{   
	int i=L.len+1;
	if (L.len<n)   //
		{	L.A[i]=x;
			i++;
			L.len++;
	   }
   
    else
    Enqueue(&Q,x);

}
void likai(int x)        //解决顾客离开事件算法
{  
	int i=0,j=1,y;
	do
	{
		if(x>L.len)
		{	
			 printf("     输入有误！请重新输入：");
			 scanf("%d",&x);
			 j++;
		}
		else
		   for(i=0; i<=L.len; i++)
		   {
				if(i==x)
				{
					 printf("     尊敬的 %d 号顾客您好！\n",x);
					 L.A[i]=0;
					 L.len--;
					 if(Q.front!=Q.rear)
					 {
						y=Dlqueue(&Q);
						L.A[i]=y;
						L.len++;
					 }
				}

		   }
	}while(i==0 && j<3);
	if(j==3) 
	{ 
	  printf("    再见！欢迎下次光临！");        //输入错误＞＝3时，退出系统
	  exit(0);
	}
}
int  guitai( )             //判断输入的柜台号是否正确
{
	int y=0;
    printf("     请输入您所办理业务的柜台号（1-3）：");
	scanf("%d",&y);
	if(y<1||y>5)
	{
		printf("     您输入的柜台号有误，请重新输入！\n");
        printf("     请输入您所办理业务的柜台号（1-3）：");
	    scanf("%d",&y);
	}
	else
		printf("     你所办理业务的柜台为 %d.\n",y);
	return y;
    
}
int  pingfeng( )             //判断输入的分数是否正确
{
	int y=0;
    printf("     请输入您的评分（1-5）：\n     1分………非常不满意;      2分………不满意；     3分………一般满意；\n     4分………比较满意；       5分………非常满意。\n");
	printf("     请输入：");
	scanf("%d",&y);
	if(y<1||y>5)
	{
		printf("     你输入评分有误，请重新输入！\n");
        printf("     请输入你的评分（1-5）：\n");
	    scanf("%d",&y);
	}
	else
	    printf("     你的评分为%d.\n",y);
	return y;
    
}
void mygrade()                 //主评分函数
{  
	printf("     为了改善服务质量，请你对我们的服务进行评价。谢谢！\n");
	z=guitai( );
	y=pingfeng( );
    switch (z)                 //柜台评分处理
   {
		case 1:                //1号柜台评分处理  
			{
			sum1+=y;
			i1++;
			ave1=sum1/i1;
	        printf("     %d号柜台的平均满意度为%0.2f。感谢你的评分，谢谢！\n",z,ave1);
			break;
			}
		case 2:                 //2号柜台评分处理  
			{
			sum2+=y;
			i2++;
			ave2=sum2/i2;
	        printf("     %d号柜台的平均满意度为%0.2f。感谢你的评分，谢谢！\n",z,ave2);
			break;
			}
        case 3:                 //3号柜台评分处理  
			{
			sum3+=y;
			i3++;
			ave3=sum3/i3;
	        printf("     %d号柜台的平均满意度为%0.2f。感谢你的评分，谢谢！\n",z,ave3);
			break;
			}
		
		default : printf("     你的输入有误，请重新输入！\n");

	}
    getch();
}
void vip(int x)               //vip用户认证
 {  
	 int i,a; 
	 char ch[3];
     int k=0;
     a=x;
	 switch(a)
	 {
	    case 1:
		 {
			 printf("     请输入你的卡号：");
		     scanf("%d",&i);
             printf("     请您输入五位密码：");
			 while(ch[k-1]!=' ')
			 {   
				 ch[k]=getch();
	             k++;
                 printf("*");
			 }
			 if(i==100 && ch[0]=='1' && ch[1]=='1' && ch[2]=='1' && ch[3]=='1')
			 {
				 printf("\n     尊敬的VIP用户您好，请您直接到VIP区办理业务！\n");
			     vip1++;
			 }
			 else if(i==200 && ch[0]=='2' && ch[1]=='2' && ch[2]=='2' && ch[3]=='2')
			 {
				 printf("\n     尊敬的VIP用户您好，请您直接到VIP区办理业务！\n");
				 vip1++;
			 }
			 else if(i==300 && ch[0]=='3' && ch[1]=='3' && ch[2]=='3' && ch[3]=='3')
			 {
				 printf("\n     尊敬的VIP用户您好，请您直接到VIP区办理业务！\n");
				 vip1++;
			 }
			 else if(i==400 && ch[0]=='4' && ch[1]=='4' && ch[2]=='4' && ch[3]=='4')
			 {
				 printf("\n     尊敬的VIP用户您好，请您直接到VIP区办理业务！\n");
				 vip1++;
			 }
			 else if(i==500 && ch[0]=='5' && ch[1]=='5' && ch[2]=='5' && ch[3]=='5')
			 {
				 printf("\n     尊敬的VIP用户您好，请您直接到VIP区办理业务！\n");
			     vip1++;
			 }
			 else printf("\n     你的输入有误！\n");
			 break;
		 }
	    default : break;		
	 }	 
 }

void mytime()         ////// 时间函数
{ 
    time_t timep;
    time (&timep);
    printf("                 现在时刻：%s",ctime(&timep));
}

void main()            //主函数
{
	time_t a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,end;   
	double  b1=0,b2=0,b3=0,b4=0,b5=0,b6=0,b7=0,b8=0,b9=0,b10=0,allsum=0,average=0,xi=0;
	double A[10]={0,0,0,0,0,0,0,0,0,0};
    int c,x,v=0,w=0;
	double sum=0;
	system("color 1f");                            //屏幕颜色设定
    system("mode con: cols=90 lines=35"); 
    Initshuzu();
    Initqueue();
    while(1)
	{  
      printf("\n********************欢迎光临中国银行湖北二师分行***********************\n");
	  printf("\n                                                                       \n");
      printf("                         1      顾客到达\n");
      printf("                         2      顾客离开\n");
      printf("                         3      查看业务办理\n");
      printf("                         4      查看排队情况\n");
	  printf("                         5      系统查询\n");
      printf("                         6      退出\n\n");
	  mytime();
      printf("\n                   提示：请按回车键进行下一步操作\n");
	  printf("\n                                                                       \n");
	  printf("************************************************************************\n");
	  printf("请输入您的选择：");
      scanf("%d",&c);
	  switch(c)
	  {
	      case 1:
		  {
			  int k=0;
	          int a; 
			  system("cls");
		      printf("\n*************************顾客到达界面*******************************\n\n");
		      printf("     请选择您的用户类型：VIP用户 请按 1；    普通用户 请按 2.\n");
		      printf("     请输入：");
	          scanf("%d",&a);
	          if (a==1)
			  {  
				  vip(a);
				  getch();
			  } 
			  else
			  {	
				  v++;                   //普通卡顾客计数
				  printf("     尊敬的普通用户，您的业务号为 %d.\n",v);
				  daoda(v);
				  if(v==1)
				  {
					  a1=time(NULL);     //取v=1的客户到达时间
					  mytime();          //显示v=1的客户到达时间
                      system("pause");
				  }
				  else if(v==2)
				  {
					  a2=time(NULL);
					  mytime();
					  system("pause");
				  }
				  else if(v==3)
				  {
					  a3=time(NULL);
					  mytime();
				      system("pause");
				  }
				  else if(v==4)
				  {
					  a4=time(NULL);
					  mytime();
				      system("pause");
				  }
		          else if(v==5)
				  {
				      a5=time(NULL);
					  mytime();
				      system("pause");
				  }
				  else if(v==6)
				  {
				      a6=time(NULL);
					  mytime();
				      system("pause");
				  }
		          else if(v==7)
				  {
				      a7=time(NULL);
					  mytime();
				      system("pause");
				  }
		          else if(v==8)
				  {
				      a8=time(NULL);
					  mytime();
				      system("pause");
				  }
		   
		          else if(v==9)
				  {
				      a9=time(NULL);
					  mytime();
				      system("pause");
				  }
		          else if(v==10)
				  {
				      a10=time(NULL);
					  mytime();
				      system("pause");
				  }
		          else 
				  {
					  printf("     请稍候拿号,谢谢！");
					  system("pause");
				  }
			  }
			  system("cls");
			  break;
		  }
	  case 2:
		  {
			  system("cls");
              printf("\n*****************************顾客离开界面***************************\n\n");
              printf("     请输入离开顾客得编号：");
              scanf("%d",&x);
              likai(x);
              mygrade();
	          w++;
	          if(x=1)
			  {
				  end=time(NULL);              //取系统的当前时间
		          A[0]=difftime(end,a1);
		          printf("     您办理业务所用时间为 %0.2f 秒.\n",A[0]);
			  }
			  else if(x=2)
			  {
				  end=time(NULL);
		          A[1]=difftime(end,a2);
		          printf("     您办理业务所用时间为 %0.2f 秒.\n",A[1]);
			  }
			  else if(x=3)
			  {
		          end=time(NULL);
		          A[2]=difftime(end,a3);
		          printf("     您办理业务所用时间为 %0.2f 秒.\n",A[2]);
			  }
	          else if(x=4)
			  {
		          end=time(NULL);
		          A[3]=difftime(end,a4);
		          printf("     您办理业务所用时间为 %0.2f 秒.\n",A[3]);
			  }
	          else if(x=5)
			  {
		          end=time(NULL);
		          A[4]=difftime(end,a5);
		          printf("     您办理业务所用时间为 %0.2f 秒.\n",A[4]);
			  }
	          else if(x=6)
			  {
		          end=time(NULL);
		          A[5]=difftime(end,a6);
		          printf("     您办理业务所用时间为 %0.2f 秒.\n",A[5]);
			  }
	         else if(x=7)
			 {
		          end=time(NULL);
		          A[6]=difftime(end,a7);
		          printf("     您办理业务所用时间为 %0.2f 秒.\n",A[6]);
			 }
	         else if(x=8)
			 {
		          end=time(NULL);
		          A[7]=difftime(end,a8);
		          printf("     您办理业务所用时间为 %0.2f 秒.\n",A[7]);
			 }
	         else if(x=9)
			 {
		          end=time(NULL);
		          A[8]=difftime(end,a9);
		          printf("     您办理业务所用时间为 %0.2f 秒.\n",A[8]);
			 }
	         else if(x=10)
			 {
		          end=time(NULL);
		          A[9]=difftime(end,a10);
		          printf("     您办理业务所用时间为 %0.2f 秒.\n",A[9]);
			 }
			 allsum+=A[0];
			 getch();
			 system("cls");
			 break;
		  }
	  case 3:
		  {   
			  system("cls");
	          printf("\n****************************业务查询界面*****************************\n\n");
              printl();
	          getch();
	          system("cls");
              break;
	   
		  }
	  case 4:
		  {
			  system("cls");
	          printf("\n****************************排队查询界面*****************************\n\n");
              print2();
	          getch();
	          system("cls");
              break;
		  }
	  case 5:
		  {   
			  char cool[3];
		      int i,k=0; ////
			  system("cls");
	          printf("\n************************* 系统查询界面*****************************\n\n");
		      printf("  请输入你的卡号：");
		      scanf("%d",&i);
              printf("  请您输入五位密码：");
		      while(cool[k-1]!=' ')
			  {   
				  cool[k]=getch();
	              k++;
                  printf("*");
			  }
			  if(i==000 && cool[0]=='1' && cool[1]=='1' && cool[2]=='1' && cool[3]=='1')
			  {	
				  average=allsum/w;
		          printf("\n  至今已有 %d 位普通用户，%d 位vip用户成功办理业务!",w,vip1);
		          printf("\n  普通用户业务办理总共用时 %0.2f秒,平均用时 %0.2f秒\n",allsum,average);
			  }
			  getch();
	          system("cls");
			  break;
		  }
		  return;
		  getch();
		  system("cls");
	  case 6:
		  return;
		  getch();
		  system("cls");
	  default: printf("     输入有误！请重新输入：\n");
		  getch();
		  system("cls");
    }
  }
}
