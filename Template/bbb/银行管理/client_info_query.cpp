

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
//宏定义
#define MaxSpace 100
#define keylen 6
#define RADIX_n 10
#define RADIX_c 26
#define SHOW_MSG_ERROR "\n输入数据错误，程序终止执行！\n" 
#define true 1
#define false 0
typedef char KeyType;
typedef struct 
{//结构描述
	char number[6];								//序号 
	char name[6];								//姓名
	char sche[6];								//存款日期 
	char time[6];								//到期时间
}InfoType;
typedef struct
{//关键字-静态链表结点类型
	KeyType keys[keylen];						//关键字（排队号）
	InfoType others;
	int next;
}SLNode;
typedef struct 
{//关键字序列-静态链表类型
	SLNode sl[MaxSpace];						//静态链表
	int keynum;									//关键字字符数
	int length;									//表长
}SLList;

typedef int ArrType_n[RADIX_n];  				//数字字符
typedef int ArrType_c[RADIX_c];  				//字母字符

KeyType key[keylen],kl[4];

//功能函数声明 系统子程序及功能设计
void Distribute(SLNode *sl, int i, int *f, int *e);////
void Collect(SLNode *sl, ArrType_n f, ArrType_n e);////
void Distribute_c(SLNode *sl, int i,int *f, int *e);////
void Collect_c(SLNode *sl, ArrType_c f, ArrType_c e);
void RadixSort(SLList *L);
void Arrange(SLList *L);
int  BinSearch(SLList L, KeyType key[]);
void SeqSearch(SLList L, KeyType key[],int i);
void DisplayStyle(int i, char *s);
void Display(SLList L, int i);
void searchcon(SLList L);
void Prompt();
bool InputData(SLList *L);
bool Check_HangBanHao(char *HangBanHao);

// 1. 数字字符分配函数 
void Distribute(SLNode *sl, int i, int *f, int *e)///////
{
    int j,p;
    for ( j=0;j<RADIX_n;j++)	
		f[j]=0;
	for ( p=sl[0].next; p; p=sl[p].next)
	{
		j=sl[p].keys[i]%48;				//将数字字符映射为十进制数字
		if ( !f[j])	f[j]=p;			
		else		sl[e[j]].next=p;	//将p指向的结点插入到第j个子表中
		e[j]=p;			
	}
}

// 2. 字母字符分配函数 
void Distribute_c(SLNode *sl, int i, int *f, int *e)///////
{  
	int j,p;
	for ( j=0;j<RADIX_c;j++)
		f[j]=0;
	for ( p=sl[0].next; p!=0; p=sl[p].next)
	{
		j=sl[p].keys[i]%65;				//将字母字符映射为字母集中的相应序号
		if ( !f[j])	f[j]=p;		
		else	sl[e[j]].next=p;		//将p指向的结点插入到第j个子表中
		e[j]=p;			
	}
}


// 3. 按指针链整理线性表 
void Arrange(SLList *L)
{   
	int p,q,i;
    SLNode temp;
	p=L->sl[0].next;							//p指向第一个结点
	for ( i=1;i<L->length;i++)
	{
		while ( p<i)							//查找第i个结点，并用p指向此结点
			p=L->sl[p].next;
		q=L->sl[p].next;
		if ( p!=i)					//若第i个结点不在当前位置，交换结点数据
		{
			temp=L->sl[p];
            L->sl[p]=L->sl[i];
            L->sl[i]=temp;
			L->sl[i].next=p;
		}
		p=q;					 	//p指向下一个未调整结点
	}
}

// 4. 折半查找函数 
int BinSearch(SLList L, KeyType key[])
{   	//折半查找函数。在有序表L中查找关键字为key[]的记录
    int high, low, mid;						    //上下界和中值
    	low=1; 								//下界初始化为1
    high=L.length;							    //上界初始化为表长
	while (low<=high)						//判别查找区间
	{
		mid=(low+high)/2;					//计算中值
		if ( strcmp(key,L.sl[mid].keys)==0)	//若正好等于中值
			return mid;						//查找成功, 返回中值
		else if ( strcmp(key,L.sl[mid].keys)<0)		//在中值左边
			high=mid-1;						//调整上界, 调整查找区间
		else 								//在中值右边
            low=mid+1;						//调整下界, 调整查找区间
	}
	return 0;								//查找失败, 返回0
}

// 5.顺序查找函数 
void SeqSearch(SLList L, KeyType key[],int i)
{  	//顺序查找函数。在有序表L中查找关键字为key[]的记录
    int j, k, m=0;
   	for (j=1; j<=L.length; j++)
   	{
		switch(i)						//按不同关键字查找
		{
           case 2:  k=strcmp(key,L.sl[j].others.number);	 break;  
                    //按顺序依次调用strcmp函数进行比较
           case 3:  k=strcmp(key,L.sl[j].others.name);  break;  
                    //按顺序依次调用strcmp函数进行比较
           case 4:  k=strcmp(key,L.sl[j].others.time); break;  
                    //按顺序依次调用strcmp函数进行比较
          
		}
	 	if ( k==0) 						//查找成功
	   	{
			m=1;						//查找标识置为1
			Display(L,j);				//显示查找结果
	   	}
  	}//namefor
   	if (m==0)							//查找失败
	   printf ( "很抱歉，无此客户信息。\n");	//输出提示信息
}

// 6. 打印客户信息函数 
void Display(SLList L, int i)
{
	printf ( "序号 姓名 存款日期 存款日期\n");
	DisplayStyle(6, L.sl[i].keys);
DisplayStyle(7, L.sl[i].others.number);	        //控制对齐输出
 	DisplayStyle(7, L.sl[i].others.name);
DisplayStyle(7, L.sl[i].others.sche);       //控制对齐输出
   
	printf ( "\n");
}

// 7. 调整对齐格式函数 
void DisplayStyle(int i, char *s)
{	//调整格式函数。调整表列对齐
	int j;
	i -= strlen(s);
	for ( j=0; j<i; ++j)  printf ( " ");		//输出占位空格, 以便对齐
	printf ( "%s,", s);
}

// 8. 查找交互界面函数 
void searchcon(SLList L)
{
	int i=1,k;
	while (i>=1 && i<=6)
	{
		printf(" \n请选择命令代号(0---6), 0 为退出系统:  ");
		scanf("%d", &i);
		switch(i)
		{
			case 1:
  				   printf("输入要查询的序号:  ");
			   	   scanf(" %s", key);k=BinSearch(L, key);
				   if (k)  Display(L,k);
				   else printf("很抱歉，无此客户信息。\n");
				   break;
			case 2: 
                   printf("输入要查询的客户姓名: ");
			       scanf("%s", key); SeqSearch(L, key, i);
			       break;
			case 3: 
                   printf("输入要查询的存款日期: ");
			       scanf( "%s", key); SeqSearch(L, key, i);
				   break;
			case 4: 
                   printf("输入要查询的到期时间: ");
			       scanf( "%s", kl); SeqSearch(L, kl, i);
			       break;
			case 5: 
                   printf("请依次录入客户信息数据:\n");
			       InputData(&L);
			       break;
			case 0:  
				   exit(0);
		}
		Prompt();                          	//循环显示主菜单
	}
}

// 9. 显示主菜单函数 
void Prompt()
{
	printf ( "***************************************************\n");
	printf ( "     	*          客户信息查询与检索系统         	*\n");	
	printf ( "      	*          1. 按序号查询               	*\n");
	printf ( "      	*          2. 按姓名查询               	*\n");
	printf ( "      	*          3. 按存款日期查询               	*\n");
	printf ( "      	*          4. 按到期时间查询             	*\n");
	printf ( "      	*          5. 依次录入客户信息             	*\n");
	printf ( "      	*          0. 退出系统                   	*\n");
	printf ( "***************************************************\n");
}

// 10. 输入客户记录函数 
bool InputData(SLList *L)
{
	int i=++L->length;
	char yn='y';
	printf ( "\n请依次录入客户信息数据:");
	do
	{
		printf("\n序号 姓名 存款日期 到期时间 \n");
		scanf ("%s %s %s %s",  &L->sl[i].others.number, &L->sl[i].others.name,&L->sl[i].others.sche,
			&L->sl[i].others.time);
		fflush(stdin);   					//清空输入缓冲区
		++i;
		printf ( "继续输入吗? y/n:");
	}while((yn=getche())=='y' || yn=='Y');
	printf("\n");
	L->length=i-1;
	//RadixSort(L);
	//Arrange(L);
	return true;
}


// 11. 主函数 
int main()
{
	SLList L;
	L.keynum=6; L.length=0;				//初始化
	Prompt();	  						//显示主菜单
	if (!InputData(&L))					//信息录入，并作输入效验
	{
		printf ( SHOW_MSG_ERROR);
		return 1;
	}
	searchcon(L);						//执行相关查询
	return 0;
}


