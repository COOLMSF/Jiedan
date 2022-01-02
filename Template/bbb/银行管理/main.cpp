#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
#define MAXSIZE 1000
#define MAX 20 
#define N 100

#define MAXINT 55555//表示极大值
int i,j;
int visited[20];
int d[20];


#define OK 1
#define LIST_ADD_SIZE 1000
#define ERROR -1
#define OVERFLOW -1
#define MaxSpace 100
#define keylen 6
#define RADIX_n 10
#define RADIX_c 26
#define SHOW_MSG_ERROR "\n输入数据错误，程序终止执行！\n" 
#define true 1
#define false 0
#define keylen 6
#define RADIX_n 10
#define RADIX_c 26
#define SHOW_MSG_ERROR "\n输入数据错误，程序终止执行！\n" 
#define TRUE 1
#define FALSE 0
#define true 1
#define false 0
#define MaxSpace 1000
typedef char KeyType;

#define LIST_INIT_SIZE 1000

using namespace std;

typedef int Status;
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
typedef struct
{
	char id[10];    /* 职工号 */
	char name[20];    /* 职工姓名 */
	char department[20];    /* 所在部门 */
	float salary;    /* 职工工资 */
	char postion[20];    /* 职位 */
}ElemType;

typedef struct
{
	ElemType *elem;    //存储空间基址
	int length;        //当前表长度（当前表中元素个数）
	int listsize;      //当前分配的存储容量（以sizeof(ElemType)为单位）
}SqList;

Status SqList_Init(SqList &L)   //初始化，构造一个新的线性表L
{
	L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!L.elem)  exit(OVERFLOW);  //存储内存分配失败
	L.length = 0;                  //空表长度为0
	L.listsize = LIST_INIT_SIZE;   //初始化存储容量
	return OK;
}

int ListLength(SqList L)  //返回L中数据元素个数
{
	return L.length;
}

//返回表中第i个元素的值
ElemType GetElem(SqList L, int i)
{
	if (i<1 || i>L.length)   exit(ERROR);   //i值不合法
	return L.elem[i - 1];
}

typedef struct LNode {
	long long int account;//账号
	char name[20];//姓名
	long long int telephone;//联系方式
	long long int ID;//身份证号
	double money;//余额
	SqList branch;//分帐号表
	int VIP;//1表示是VIP，0表示不是VIP 
	struct LNode* next;//指向下一结点的指针
}LNode, * LinkList;//用户信息链表

//在表尾插入新的元素 
Status SqList_Insert(SqList &L, ElemType e)
{
	ElemType *p, *q, *newbase = NULL;
	if (L.length >= L.listsize)  //当前内存已满，增加内存，重新分配
	{
		newbase = (ElemType *)realloc(L.elem, (L.listsize + LIST_ADD_SIZE) * sizeof(ElemType));
		if (!newbase)  exit(OVERFLOW);  //存储内存分配失败
		L.elem = newbase;               //新基址
		L.listsize += LIST_ADD_SIZE;    //存储容量增加
	}
	int i = L.length + 1;
	q = &(L.elem[i - 1]);     //q为插入位置
	for (p = &(L.elem[L.length - 1]); p >= q; --p)    *(p + 1) = *p;
	//插入位置及之后的元素右移
	*q = e;      //插入e到第i个元素的位置
	++L.length;  //表长加一
	return OK;
}

//在顺序线性表中删除第i个元素
Status SqList_Delete(SqList &L, int i)
{
	
	//i的合法值为 1<= i <=L.length
	ElemType *p, *q;
	if (i<1||i>L.length)  return ERROR;  //i值不合法         
	p = &L.elem[i-1];                        //p为被删除元素的位置
	
	q=L.elem+L.length-1;                 //表尾元素的位置
	for(++p;p<=q;++p)  *(p-1)=*p;        //被删除元素之后的元素左移
	--L.length;
	return OK;
}

// 比较是否是同一人(id号是否相等)
Status Equal(ElemType a, ElemType b)
{
	if (!strcmp(a.id,b.id))  return TRUE;
	else return FALSE;
}

//在L中查找第一个值与e满足compare关系的元素,返回它在表中的下标 
int SqList_LocateElem(SqList L, ElemType e,
	Status(*compare)(ElemType, ElemType))  //形参compare()是函数型指针
	
{
	int i = 1;    //i的初值为第一个元素的位序
	ElemType *p;  //p的初值为第一个元素的存储位置
	p = L.elem;
	while (i <= L.length && !(*compare)(*p++, e))  ++i;
	if (i <= L.length)   return i;  //若找到，则返回其在L中的位序，否则返回0
	else  return 0;
}

// 获取输入的员工信息 
ElemType GetEmpInfomation()
{
	ElemType e; 
	printf("请输入职工号:");
	scanf("%s",&(e.id));
	printf("请输入职工姓名:");
	scanf("%s", &(e.name));
	printf("请输入职位:");
	scanf("%s", &(e.postion));
	printf("请输入部门:");
	scanf("%s", &(e.department));
	printf("请输入薪资:");
	scanf("%f", &(e.salary));
	printf("\n"); 
	return e;
} 

// 插入新的员工信息
void AddEmpToList(SqList &L)
{
	ElemType e = GetEmpInfomation();
	int res = SqList_LocateElem(L, e, Equal);
	if(res == 0)//此员工信息未存在 
	{
		SqList_Insert(L, e);
		printf("添加成功！是否继续添加？1:是;0:否\n");
		int c = -1;
		scanf("%d",&c);
		if(c == 1){
			AddEmpToList(L);
		}else if(c == 0){
			printf("\n");
			return;
		}else{
			printf("非法输入，请重新操作！\n\n");
			return;
		}
	}else{//此员工信息已存在 
		printf("此编号员工信息已存在，请勿重复操作！\n\n"); 
		return;
	} 
	
} 

// 显示某员工信息
void showEmpInfo(SqList L)
{
	printf("\n请输入要查看的员工编号：");
	char id[10];
	scanf("%s",id);
	ElemType e;
	strcpy(e.id,id);
	int res = SqList_LocateElem(L, e, Equal);
	if(res != 0){
		e = GetElem(L, res);
		printf("职工号\t姓名\t部门\t职位\t薪资\n");
		printf("%s\t%s\t%s\t%s\t%.2f\n\n", e.id, e.name, e.department, e.postion, e.salary);
	}else{
		printf("此员工不存在！\n\n");
	}
} 

// 删除某员工信息
void DeleteEmp(SqList &L)
{
	if(L.length == 0){
		printf("当前无员工信息，请先选择添加员工信息操作！\n");
		return;
	} 
	printf("请输入要删除的员工编号：");
	char id[10];
	scanf("%s",id);
	ElemType e;
	strcpy(e.id,id);
	int res = SqList_LocateElem(L, e, Equal);
	if(res != 0){
		printf("确定要删除吗？确定:1; 放弃:0\n");
		int c;
		scanf("%d",&c); 
		if(c == 1){
			SqList_Delete(L, res + 1);//第i+1各=个元素的下表是i 
			printf("删除成功！\n\n");
		}else{
			printf("此操作已取消！\n\n");
		}		
	}else{
		printf("此员工不存在！\n\n");
	}
} 
 
//打印员工信息表 
void Print(SqList L)
{
	printf("\n职工号\t姓名\t部门\t职位\t薪资\n");
	ElemType p;
	for (int i = 0; i < L.length; i++)
	{
		p = L.elem[i];
		printf("%s\t%s\t%s\t%s\t%.2f\n", p.id, p.name, p.department, p.postion, p.salary);
	}
	printf("\n\n");
}

// 主菜单 
void menu(SqList &L)
{
	bool flag = true;
	while(flag)
	{
	    flag = true;
	 printf("======================================================\n"); 
		printf("\t\t欢迎进入公司职工信息管理系统\n"); 
	 printf("======================================================\n"); 
	    printf("\t\t1.增加职工信息\n"); 
	    printf("\t\t2.查找职工信息\n"); 
	    printf("\t\t3.显示所有职工信息\n"); 
	    printf("\t\t4.删除职工信息\n"); 
	    printf("\t\t5.退出\n"); 
	    printf("======================================================\n"); 
	    printf("请选择1-5："); 
	    int c;
	    scanf("%d",&c);
	    switch(c)
		{
	    	case 1: AddEmpToList(L);break;
	    	case 2: showEmpInfo(L);break;
	    	case 3: Print(L);break;
	    	case 4: DeleteEmp(L);break;
	    	case 5: flag = false; printf("\n您已退出！\n");break;
	    	default: printf("输入不合法！\n\n");break;
		}
	} 
}


using namespace std;

//bool manbermark=0;//标记是否有注册成员   
string loginmarknumber ;//记录登录时还没有一个注册的，注册时的账号   

class information  
{  
public :  
    string num ;//账号  
    string name;//用户名  
    string key;//密码  
    string ID;//身份证号  
    string tel;//电话号码  
    double money;//余额  
    information *next;//记录下一空间地址  
};  
int cheak_num(string str,information *head)//检查账号是否存在  
{  
 int t=0;//记录该账号是否存在  
 information * p=head;  
 if(head==NULL)  
  t=0;  
 else  
 {  
  while(p->next!=NULL)//对已有账号进行遍历  
  {  
   if(p->num!=str)  
    p=p->next;  
   else  
   {t=1;  
   break;  
   }  
  }  
  if(t==0)  
   if(p->num==str)  
    t=1;  
 }  
 return t;//若账号已经存在则返回1，否则返回0  
}  
information * get_information (information *head)//管理员录入信息  
{  
 information *s,*p;  
 s=new information;  
 cout<<"请录入信息："<<endl;  
 cout<<"账号：";  
 cin>>s->num;  
 cout<<"用户名：";  
 cin>>s->name;  
 cout<<"密码：";  
 cin>>s->key;  
 cout<<"身份证号：";  
 cin>>s->ID;  
 cout<<"电话号码：";  
 cin>>s->tel;  
 cout<<"余额：";  
 cin>>s->money;  
 cout<<endl<<"====================================信息录入成功==============================="<<endl;  
 while ( 1 )                                           
 {  
  char ch;  
  if( head==NULL )  
  {  
   head = s ;  
   //head->next=NULL;//头指针赋值  
  }  
  else  
   p->next = s ;                                             //将新结点插入已有链表的最后  
  cout<<"是否继续录入信息   是（1），（2）否"<<endl;  
  cin>>ch;  
  while(ch!='1' && ch!='2'){  
   cout<<"请重新输入是否继续录入 是（1）  否（2）";  
   cin>>ch;  
  }  
  if(ch=='1'){  
  //选择“是?  
   p = s ;// p指向链表中最后的结点  
   p->next=NULL;  
   s=new information;  
   s->next=NULL;  
   cout<<"请输入注册信息:"<<endl;  
   cout<<"账号：";  
   string str111;  
   cin>>str111;  
   int t;  
   t=cheak_num(str111,head);  
   while(t==1)            //对已有账号进行判断 ，直到新注册账号不存在为止  
   {  
    cout<<"账号已存在，请重新注册：";  
    cin>>str111;  
    t=cheak_num(str111,head);  
   }  
   s->num=str111;  
   cout<<"用户名：";  
   cin>>s->name;  
   cout<<"密码：";  
   cin>>s->key;  
   cout<<"身份证号:";  
   cin>>s->ID;  
   cout<<"电话号码:";  
   cin>>s->tel;  
   cout<<"余额:";  
   cin>>s->money;  
   cout<<endl;  
  }  
  else//选择“否”  
  {  
   s->next=NULL;  
   break;  
  }  
  cout<<endl<<"====================================信息录入成功==============================="<<endl;  
 }  
 return head;  
}  
void output_information (information *head)//显示所有账号信息  
{    
if(head==NULL){  
    cout<<"暂无注册信息";  
    return ;   
}   
int i=1;  
 information *s;  
 s=head;  
 while(s->next!=NULL)  
 {  
  cout<<"用户注册编码："<<i<<endl;   
  cout<<"账号："<<s->num<<endl;  
  cout<<"用户名: "<<s->name<<endl;  
  cout<<"密码："<<s->key<<endl;  
  cout<<"身份证号："<<s->ID<<endl;  
  cout<<"电话："<<s->tel<<endl;  
  cout<<"金额："<<s->money<<endl<<endl;  
  s=s->next;  
  i++;  
 }  
 cout<<"用户注册编码："<<i<<endl;   
 cout<<"账号："<<s->num<<endl;  
 cout<<"用户名: "<<s->name<<endl;  
 cout<<"密码："<<s->key<<endl;  
 cout<<"身份证号："<<s->ID<<endl;  
 cout<<"电话："<<s->tel<<endl;  
 cout<<"金额："<<s->money<<endl;  
}  
int check_keys(string number,string keys,information *head)//检查账号是否存在且密码是否正确  
{  
 int t=0;  
 information *p=head;  
 while(p->next!=NULL)  
 {  
  if(p->num!=number)  
   p=p->next;  
  else  
  {  
   if(p->key==keys)  
   {t=3;//账号存在且密码正确  
   break;  
   }  
   else  
   {t=2;//账号存在但是密码不正确  
   break;  
   }  
  }  
 }  
 if(t==0)  
  if(p->num==number)  
   if(p->key==keys)  
    t=3;//账号存在且密码正确  
   else  
    t=2;//账号存在但是密码不正确  
   return t;  
}  
void take_money(information * p)//取钱函数  
{  
 double m;  
 cout<<"请输入提款金额：";  
 cin>>m;  
 if(m<=p->money)//判断是否超过账号余额  
 {   p->money=p->money-m;  
 cout<<"取款成功"<<endl;  
 }  
 else  
 {  
  while(m>p->money)//若取钱金额超过账户余额  
  {cout<<"余额不足，请重新操作"<<endl;  
  cout<<"请输入提款金额：";  
  cin>>m;  
  }  
  p->money=p->money-m;//对取现后的余额进行修改  
  cout<<endl<<"======================================取款成功=================================="<<endl;  
 }  
}  
void save_money(information *p)//存钱函数  
{  
 double m;  
 cout<<"请输入存款金额:";  
 cin>>m;  
 p->money=p->money+m;//对所存入的账户余额修改  
 cout<<endl<<"======================================存款成功=================================="<<endl;  
}  
information*cheak_number(string number,information *head)//在管理员模式下或者是客户在正确输入密码后查找客户信息  
{  
 int a=0 ;//标记账户是否存在  
 information *p=head;  
 while(p->next!=NULL)  
 {  
  if(p->num==number)  
  { a=1;  
  break;  
  }  
  else  
   p=p->next;  
 }  
 if(p->num==number)  
  a=1;  
 if(a==0)  
  p=NULL;  
 return p;//返回所查找的客户地址信息  
}  
void move_money(information *p,information *head)// 转账函数                  p是正在登陆的账号地址  
{  
 information *x;//记录所转账号地址  
 x=NULL ;  
 double m;//转账金额  
 string str;//转账账号  
 char ch ;//记录用户输入的是否继续转账决定  
 cout<<"请输入要转账的账号:";  
 cin>>str;  
 x=cheak_number(str,head);//记录下了所转账好的地址  
 while(x==NULL)//如果账户不存在  
 {  
  x=cheak_number(str,head);//记录下了所转账好的地址  
  cout<<"账号不存在，是否重新操作：(1)是  (2)否"<<endl;  
  cin>>ch;  
        if(ch=='1')  
  {  
   cout<<"请重新输入要转账的账户：";  
   cin>>str;  
   x=cheak_number(str,head);//记录下了所转账好的地址  
  }  
  else  
   break;  
 }  
 if(x!=NULL)//如果账户存在  
 {  
  cout<<"请输入转账金额：";  
        cin>>m;  
  while(p->money<m)  
  {cout<<"余额不足，请重新输入转账金额："<<endl;  
  cin>>m;  
  }  
  x->money=x->money+m ;  
  p->money=p->money-m;  
  cout<<endl<<"=====================================转账成功================================"<<endl;  
 }  
}  
void revise_information(information *p)//"修改信息"  
{  
 string str,str1;//记录用户账号信息  
 char ch;//记录用户决定  
 while(1)  
 {  
  cout<<"请选择要修改的信息  (1)账号  (2)用户名  (3)密码  (4)身份证号  (5)电话 (6)退出修改当前账户信息   ";  
  cin>>ch;  
  while(ch!='1'&&ch!='2'&&ch!='3'&&ch!='4'&&ch!='5'&&ch!='6')//用户若输入业务已有误  
  {  
   cout<<"请重新输入有效的业务：";  
   cin>>ch;  
  }  
  if( ch=='1')//修改账号  
  {  
   cout<<"请输入新账号：";  
   cin>>str;  
   p->num=str;  
   cout<<endl<<"====================================修改账号成功================================"<<endl;  
  }  
  else  
   if( ch=='2')//修改用户名  
   {  
    cout<<"请输入新的用户名：";  
    cin>>str;  
    p->name=str;  
    cout<<endl<<"===================================修改用户名成功=============================="<<endl;  
   }  
   else  
    if( ch=='3')//修改密码  
    {  
     cout<<"请输入原密码：";  
     cin>>str;  
     while(p->key!=str)  
     {  
      cout<<"与原密码不一致，请重新输入原密码：";  
      cin>>str;  
     }  
     cout<<"请输入新密码：";  
     cin>>str;  
     cout<<"请确认密码：";  
     cin>>str1;  
     while(str!=str1)  
     {  
      cout<<"与第一次输入不同，请重新设定：";  
      cout<<"请输入新密码：";  
      cin>>str;  
      cout<<"请确认密码：";  
      cin>>str1;  
     }  
     cout<<endl<<"===============================设定成功，请记好新密码=========================="<<endl;  
    }  
    else  
     if( ch=='4')//修改身份证号  
     {  
      cout<<"请输入新身份证号：";  
      cin>>str;  
      p->ID=str;  
      cout<<endl<<"==================================修改身份证成功==============================="<<endl;  
     }  
     else  
      if( ch=='5')//修改电话号码  
      {  
       cout<<"请输入新电话号码：";  
       cin>>str;  
       p->tel=str;  
       cout<<endl<<"==================================电话号码修改成功============================="<<endl;  
      }  
      else  
       break;//退出修改账户信息  
 }  
}  
void show_information(information*p)//显示当前账户信息  
{  
 cout<<"账号："<<p->num<<endl;  
 cout<<"用户名:"<<p->name<<endl;  
 cout<<"密码："<<p->key<<endl;  
 cout<<"身份证号："<<p->ID<<endl;  
 cout<<"电话："<<p->tel<<endl;  
 cout<<"金额："<<p->money<<endl;  
}  


void query_money(information *p)//显示当前账户余额  
{  
 cout<<"您的余额为：";  
 cout<<p->money<<endl;  
}  
information* logon(information *head)//用户注册账号  
{  
 information *s;  
 string str;//记录账号信息  
 cout<<"请输入注册账号：";  
 cin>>str;  
 int t;  
 if(head==NULL)//如果链表不存在信息，默认为新注册的账号不存在  
  t=0;  
 else  
  t=cheak_num(str,head);//判断账号是否已经存在  
 while(t==1)//账号已经存在 重新输入  
 {  
  cout<<"账号已存在，请重新注册：";  
  cin>>str;  
  t=cheak_num(str,head);  
 }  
 s=new information ;//为链表开辟新空间  
 s->num=str;  
 if(head==NULL)  
   loginmarknumber=str;  
 cout<<"用户名：";  
 cin>>s->name;  
 cout<<"密码：";  
 cin>>s->key;  
 cout<<"身份证号：";  
 cin>>s->ID;  
 cout<<"电话号码：";  
 cin>>s->tel;  
 cout<<"余额：";  
 cin>>s->money;  
 if(head==NULL)//如果当前链表没有任何信息    
 {  
  head=s;  
  head->next=NULL;  
 }  
 else//将新注册的插入当前链表  
 {  
  s->next=head->next;  
  head->next=s;  
 }  
 cout<<endl<<"=====================================注册成功==================================="<<endl;  
 return head;  
}  


information * choose(information *head)//普通用户登陆账号以及选择需要的业务  
{  
 int t,loginmark=0;  
 if(head==NULL){//还没有注册账号   
    cout<<endl<<"未有账户注册，无法完成登陆功能，请先注册账户信息"<<endl<<"是否现在注册：（1）是，（2）稍后注册"<<endl;  
    int x;  
    cin>>x;  
    while(x!=1&&x!=2){  
        cout<<"请重新选择：";  
         cin>>x;   
    }  
   if(x==1){  
   head=logon(head);  
   loginmark=1;  
   }  
   else  
    return head ;     
 }  

 information *p;//p是用来记录所查找到的账号的地址的  
 string number,keys;//number 记录登陆账号 keys记录账密码  
  if(loginmark==0){  
  cout<<"请输入账号：";  
 cin>>number;  
 cout<<"请输入账号密码:";  
 cin>>keys;  
 t=check_keys(number,keys,head);       //t是用来记录是否存在账号以及密码是否正确的，若账号不存在则返回0，若账号密码错误返回2，账号存在且密码正确时返回3  
 while(t==0||t==2)//如果账号不存在或者是密码输入错误  
 {  
  if(t==2)//用户输入密码有误  
  {cout<<"密码输入错误，请重新输入账号及密码";  
  cout<<"账号:";  
  }  
  else//账号不存在  
   cout<<"账号不存在，请重新输入账号及密码,账号:";  
  cin>>number;  
  cout<<"密码:";  
  cin>>keys;  
  t=check_keys(number,keys,head);//调用判断密码 账号是否正确  
 }   
 }  
 else  
 number=loginmarknumber;  

 cout<<endl<<"==================================普通用户登陆成功=============================="<<endl<<endl;  
 cout<<"请选择业务：(1)取钱 (2)存钱  (3)转账  (4)修改信息  (5)余额查询 (6)显示账号信息  (7)退出账号"<<endl;  
 p=cheak_number(number,head);       //记录所登陆的账号地址  
 char ch;      //记录用户所做的选择  
 cin>>ch;  
 while(1)  
 {  
  while(ch!='1'&&ch!='2'&&ch!='3'&&ch!='4'&&ch!='5'&&ch!='6'&&ch!='7')//用户若出入业务有误  
  {cout<<"请重新输入所需业务：(1)取钱 (2)存钱  (3)转账  (4)修改信息  (5)余额查询 (6)显示账号信息  (7)退出账号"<<endl;  
  cin>>ch;   //重新输入业务  
  }  
  if(ch=='7')    //退出当前账户   
   break;  
  else  
  {  
   switch(ch)  
   {  
   case '1':take_money(p);break;          //取钱  
   case '2':save_money(p);break;          //存钱  
   case '3':move_money(p,head);break;     //转账  
   case '4':revise_information(p);break;  //修改信息  
   case '5':query_money(p);break;         //查询余额  
   case '6':show_information(p);break;    //查看信息  
   }  
   cout<<"请选择业务：(1)取钱 (2)存钱  (3)转账  (4)修改信息  (5)余额查询 (6)显示账号信息  (7)退出账号"<<endl;  
   cin>>ch;  
  }  
 }  
 return head;  
}  

string change_monitor_keys(string monitor)  
{  
 string string1,string2;//记录用户两次输入密码  
 cout<<"请输入原密码：";  
 cin>>string1;  
 while(string1!=monitor)//如果管理员密码输入不正确  
 {  
  cout<<"与原密码不符，是否重新输入  (1)是   (2) 否  "<<endl;  
  char chra;  
  cin>>chra;//记录用户是否继续登陆  
  while(chra!='1'&&chra!='2')//判断用户是否存在误操作  
  {  
   cout<<"选择有误，请重新选择：(1)是   (2) 否 "<<endl;  
   cin>>chra;  
  }  
  if(chra=='1')//继续登陆输入账号  
  {  
   cout<<"请再次输入原密码：";  
   cin>>string1;  
  }  
  else{//停止登陆  
  cout<<endl<<"==================================密码未修改===================================="<<endl;  
   break;  
   }  
 }  
 if(string1!=monitor)//退出修改管理员密码  
  return monitor;  
 cout<<"请输入新密码：";  
 cin>>string1;  
 cout<<"请再次输入确认修改密码：";  
 cin>>string2;  
 while(string1!=string2)//判断两次输入的新密码是否一致  
 {  
  cout<<"两次输入密码不相同，请选择是否继续修改：(1)是 (2)否"<<endl;  
  char jilu;//记录用户选择是否继续修改  
  cin>>jilu;  
  while(jilu!='1'&&jilu!='2')//判断用户是否存在误操作，是则提示  
  {  
   cout<<"请重修选择是否修改：(1)是 (2)否"<<endl;  
   cin>>jilu;  
  }  
  if(jilu=='1')//继续修改密码  
  {  
   cout<<"请输入新密码：";  
   cin>>string1;     
   cout<<"请再次输入确认修改密码：";  
   cin>>string2;  
  }  
  else{//退出修改密码  
   break;  
  }  
 }  
 if(string2==string1)//如果在两次输入修改密码一致，成功修改  
 {  
  monitor=string1;  
  cout<<endl<<"====================================密码修改成功==============================="<<endl;  
 }  
 else  
  cout<<endl<<"==================================密码未修改=============================="<<endl;  
 return monitor;  
}  
void choose_model(information *head,string monitor)//选择开始界面业务  
{  
 information *p;  
 char ch,mon_cho;//记录用户选择  
 string str;//后面用到的是管理员密码  客户账号  
 cout<<"==============================欢迎进入银行管理系统=============================="<<endl;  
 while(1)  
 {  
  cout<<"请选择进入模式："<<endl;  
  cout<<"(1)管理员模式  (2)普通用户模式 (3)退出系统 "<<endl;  
  cin>>ch;  
  while(ch!='1'&&ch!='2'&&ch!='3')//如果用户输入有误，提示  
  {   cout<<"请选择进入模式："<<endl;  
  cout<<"(1)管理员模式  (2)普通用户模式 (3)退出系统 "<<endl;  
  cin>>ch;  
  }  
  if(ch=='1')//管理员模式  
  {  
   cout<<"您已进入管理员模式"<<endl<<"请输入管理员密码：";  
   cin>>str;  
   if(monitor!=str)  
   {  
    char judge;//用来记录选择  
    while(monitor!=str)//判断管理员密码是否正确  
    {  
     cout<<"管理员密码输入错误，是否重新输入   (1)是   (2)否"<<endl;//此处考虑到可能是客户不小心进入可以选择退出管理员模式  
     cin>>judge;  
     while(judge!='1'&&judge!='2')//如果用户输入有误,提示  
     {  
      cout<<"请重新选择是否重新输入密码  (1)是   (2)否"<<endl;  
     }  
     if(judge=='1')//继续输入密码  
     {  
      cout<<"请重新输入管理员密码:";  
      cin>>str;//重新输入管理员密码  
     }  
     else  
     {break;//结束本输入密码循环  
     }  
    }  
   }  
   if(monitor==str)//成功登陆管理员  
   {  
    cout<<endl<<"==================================管理员登陆成功==============================="<<endl;  
    while(1)  
    {  

     cout<<endl<<endl<<"请输入要执行的操作"<<endl;  
     cout<<"(1)客户信息录入  (2)管理客户信息  (3)修改管理员密码 (4)显示所有账户信息  (5)退出管理员模式"<<endl;  

     cin>>mon_cho;//记录用户选择  
     while(mon_cho!='1'&&mon_cho!='2'&&mon_cho!='3'&&mon_cho!='4'&&mon_cho!='5')//如果用户输入有误，提示  
     {  
      cout<<endl<<endl<<"请重新选择模式"<<endl;  
      cout<<"(1)客户信息录入  (2)管理客户信息  (3)修改管理员密码  (4)显示所有账户信息  (5)退出管理员模式"<<endl;  
      cin>>mon_cho;  
     }  
     if(mon_cho=='1')//客户信息录入  
      head=get_information(head);  
     else  
      if(mon_cho=='2')//管理账户信息  
      {  
       if(head==NULL){  
        cout<<"对不起，由于暂无账户注册信息，该操作无法执行"<<endl;  
        continue;   
       }  
       cout<<"请输入要修改的客户账号：";  
       cin>>str;  
       p=cheak_number(str,head);//判断账户是否存在  
       while(p==NULL)//账户不存在，提示重新输入  
       {  
        cout<<"该账号不存在，请重新输入：";  
        cin>>str;  
        p=cheak_number(str,head);  
       }  
       revise_information(p);//修改已存在的账户信息  
      }  
      else  
       if(mon_cho=='5')//结束管理员模式  
        break;  
       else  

        if(mon_cho=='4')//输出所有账户信息  
         output_information (head);  
        else//修改管理员密码  
         monitor=change_monitor_keys(monitor);  

    }  
   }  
  }  
  else  
   if(ch=='2')//选择普通客户模式  
   {  
    char jilu;//记录用户所选业务  
    cout<<"==============================欢迎进入银行管理系统=============================="<<endl;  
    while(1)  
    {  
     cout<<"请选择需要业务：(1) 注册  (2) 登录 (3)退出普通用户模式 "<<endl;  
     cin>>jilu;  
     while(jilu!='1'&&jilu!='2'&&jilu!='3')//判断用户误操作,提示  
     {  
      cout<<"输入错误，请重新选择业务：：(1) 注册  (2) 登录 (3)退出普通用户模式 "<<endl;  
      cin>>jilu;  
     }  
     if(jilu=='1')//注册  
      head=logon(head);  
     else  
      if(jilu=='2')//登陆  
       head=choose(head);  
      else  
       break;//退出普通用户模式  
    }  
   }  
   else //退出该系统  
    break;  
  }  

}  










typedef  int Status;
typedef struct{
char name[20];
char type[1];
}QElemType;
typedef struct {
   QElemType *base;
   int front;
   int viprear;
   int namerear;
   int rear;
}SqQueue;
Status InitQueue(SqQueue &Q)
 {
	Q.base=(QElemType*)malloc(sizeof(QElemType)*MAXSIZE);
	if (!Q.base)
		exit(1); 
	Q.viprear=Q.front=0;
	Q.rear=0; 
	return OK;
}
Status QueueLength(SqQueue Q)
{
	if(Q.rear==Q.front) return 0;
return (Q.rear-Q.front+MAXSIZE)%MAXSIZE;}
Status EnQueue(SqQueue &Q,QElemType e)
{
	int j;
	if((Q.rear+1)%MAXSIZE==Q.front)
		return ERROR;
	if(*e.type-'0')
	{
for(j=(Q.rear-Q.viprear);j>=1;j--)
Q.base[Q.viprear+j]=Q.base[Q.viprear+j-1];
Q.rear++;
Q.base[Q.viprear]=e;
Q.viprear++;	
printf("尊敬的VIP客户：你已经排号成功！\n");

	}
	else
	{ Q.base[Q.rear]=e;
Q.rear=(Q.rear+1)%MAXSIZE;
	printf("尊敬的普通客户：你已经排号成功！\n");
	}
return OK;
}
Status DeQueue(SqQueue &Q,QElemType &e)
{
if(Q.front==Q.rear)
return ERROR;
if(Q.front==Q.viprear) 
++Q.front;
printf("\n离开的客户为:%s",Q.base[Q.front].name);
if(*Q.base[Q.front].type-'0')
printf("   vip客户\n");
else printf("   普通客户\n");
Q.front=(Q.front+1)%MAXSIZE;
return OK;
}    
Status Locatetion(SqQueue &Q,QElemType &e)
{
	int j;
	Q.base[Q.namerear]=e;
	//k=Q.namerear-Q.front;
	for (j=Q.front;j<Q.namerear;j++)
			printf("%s  ",Q.base[j].name);
	//printf("您前面还有:%d人",k);
	return OK;
}







int bank_queue()  
{  

	SqList L;  //定义SqList型结构L
	SqList_Init(L);  //初始化L

	menu(L);
	
	system("pause");

 information *head=NULL;  
string monitor="123";//monitor为管理员初始密码  
choose_model(head,monitor);  



	int choose;
	 int j;
     SqQueue Q;
    QElemType *E;
    InitQueue(Q) ;
        printf("****************************\n");
        printf("欢迎使用银行自助排队系统\n");
        printf("请选择你要使用的功能：\n");
        printf("1.新客户排队等待服务\n");
        printf("2.客户离开排队服务\n");
        printf("3.查询当前客户前面还有几人\n");
        printf("4.查询截止目前总共办理多少客户\n");
        printf("0.退出银行排队系统\n");
		printf("****************************\n");
			do
{	
	printf("请选择输入你要使用的服务：\n");
	scanf("%d",&choose);
	switch(choose)
	{
case 1:
    E=(QElemType*)malloc(1*sizeof(QElemType));
		printf("请选择客户类别\n1、VIP客户  0、普通客户\n");
	scanf("%s",E->type);
	printf("请输入你的姓名：\n");
	scanf("%s",E->name);
	if(EnQueue(Q,*E))
	       printf("当前排队情况：");
	         for (j=Q.front;j<Q.rear;j++)
			printf("%s  ",Q.base[j].name);
            printf("\n");
			 break;
case 2:
    	if(DeQueue(Q,*E))
		printf("\n出队成功\n");
        	else printf("\n*******出队失败******\n");
           printf("当前排队情况：");
	         for (j=Q.front;j<Q.rear;j++)
			printf("%s  ",Q.base[j].name);
            printf("\n");
           break;
case 3:
	printf("\n当前排队人数%d\n",QueueLength(Q));
    printf("\n请输入你要查找的人的姓名：");
	scanf("%s",E->name);
	for(j=Q.front;j<Q.rear;j++)
		if(strcmp(E->name,Q.base[j].name))
			break;
		printf("%s  ",Q.base[j].name);
	printf("当前排队情况：");
	         for (j=Q.front;j<Q.rear;j++)
			printf("%s  ",Q.base[j].name);
            printf("\n");
	break;
case 4:
	if(Q.front>Q.viprear)
	printf("\n已办理用户人数%d\n",Q.front-1);
	else 
			printf("\n已办理用户人数%d\n",Q.front);
	printf("当前排队情况：");
	for (j=Q.front;j<Q.rear;j++)
	printf("%s  ",Q.base[j].name);
     printf("\n");
	break;
case 0:
		{
			  printf("\n\n谢谢您的使用，请按任意键退出\n\n\n");
                        break;
                }
	}
	}while(choose!=0);		





return 0;  
}  


int jin;
char a;
void chuangjian();

int denglu();   //登录账户
int huyan();   //账户验证
int miyan();  //密码验证
void cunkuan(int);   //存款
void qukuan(int);     //取款
void daikuan(int);    //贷款
void lixi(int);       //利息计算
void display(int);//查询
//
void date();      //显示日期
void flag(int);    //主界面
void flag1();     //初始界面
//
struct users {
	char idnum[9];   //账户
	char password[7];    //密码
	char name[10]; //姓名
	char idnumber[20];  //身份证号码
	double YuE;     //余额
} user[N];
char id[11], password[7];

void chuangjian();

int denglu();   //登录账户
int huyan();   //账户验证
int miyan();  //密码验证
void cunkuan(int);   //存款
void qukuan(int);     //取款
void daikuan(int);    //贷款
void lixi(int);       //利息计算
void display(int);//查询
//
void date();      //显示日期
void flag(int);    //主界面
void flag1();     //初始界面
//
// struct users {
// 	char idnum[9];   //账户
// 	char password[7];    //密码
// 	char name[10]; //姓名
// 	char idnumber[20];  //身份证号码
// 	double YuE;     //余额
// } user[N];
// char id[11], password[7];


int  daikuan() {
	fflush(stdin);
	chuangjian();
	flag1();
	int m = denglu();
	while (m != -1) {
		flag(m);
	}
}

void flag1() {
	fflush(stdin);
	printf("\n#################################################################################\n");
	printf("\n▓                               * 欢迎使用**银行  *                               ▓\n");
	printf("\n#################################################################################\n");
	printf("\n          ◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆       \n");
	printf("          ◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆         \n");
	printf("\n#################################################################################\n");
	printf("\n▓                          ************请先登录*******************                ▓\n");
	printf("\n#################################################################################\n");
}

void flag(int m) {
	int a;//选择功能的变量
	do {
		date();
		printf("\n#################################################################################\n");
		printf("\n▓                               * 欢迎使用  *                                 ▓\n");
		printf("\n#################################################################################\n");
		printf("\n          ◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆\n");
		printf("          |◆|******|◆|        ☆ 存款业务       请按 1        |◆|******|◆|\n");
		printf("          |◆|******|◆|        ☆ 取款业务       请按 2        |◆|******|◆|\n");
		printf("          |◆|******|◆|        ☆ 查询余额       请按 3        |◆|******|◆|\n");
		printf("          |◆|******|◆|        ☆ 贷款业务       请按 4        |◆|******|◆|\n");
		printf("          |◆|******|◆|        ☆ 利息计算       请按 5        |◆|******|◆|\n");
		printf("          |◆|******|◆|        ☆ 退出系统       请按 6        |◆|******|◆|\n");
		printf("          |◆|******|◆|                                        |◆|******|◆|\n");
		printf("          ◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆\n");
		printf("\n#################################################################################\n");
		printf("\n▓                          *******************************                    ▓\n");
		printf("\n#################################################################################\n");
		printf("\n\n\t\t##请输入你的选择：");
		fflush(stdin);
		scanf("%d", &a);
		switch (a) {
			case 1: {
				fflush(stdin);
				cunkuan(m);
				break;//存款

			}
			case 2:  {

				fflush(stdin);
				qukuan(m);
				break;//取款

			}
			case 3: {

				fflush(stdin);
				display(m);
				break;//查询业务
			}
			case 4: {

				fflush(stdin);
				daikuan(m);
				break;//贷款

			}
			case 5: {

				fflush(stdin);
				lixi(m);
				break;//利息

			}
			case 6:
				exit(0);
			default:
				printf("您输入的选择有误，请输入正确的选项：");

		}
	} while (1);
}
//********************************************************************************************************************
//用户功能选择界面

//***************************************************************************
void chuangjian() { //创建用户实验
	fflush(stdin);
	date();
	printf("请输入创建用户数量：");
	int n;
	scanf("%d", &n);
	for (i = 1; i <= n; i++) {
		printf("请输入您的名字\n");
		scanf("%s", user[i].name);
		printf("请输入您的身份证号\n");
		scanf("%s", user[i].idnumber);
		printf("请输入您的账户\n");
		scanf("%s", user[i].idnum);
		printf("请输入您六位数密码\n");
		scanf("%s", user[i].password);
		user[i].YuE = 0;
	}
}
int huyan(char *s) {
	fflush(stdin);
	for (i = 0; i < N; i++)
		if (strcmp(s, user[i].idnum ) == 0 )
			break;
	if (i < N)
		return i;
	else
		return 0;
}

int miyan(char *s, int i) {
	fflush(stdin);
	if (strcmp(s, user[i].password ) == 0)
		return 1;
	else
		return 0;
}
int denglu() {
	fflush(stdin);
	date();
	printf("请输入您的账户登录：\n");
	scanf("%s", id);
	while (huyan(id) == 0) {
		printf("请输入正确已在本行开户的的账户：\n");
		scanf("%s", id);
	}
	int k = huyan(id);
	printf("请输入您的六位密码：\n");
	for (i = 0; i < 6; i++) {
		password[i] = getchar();
		printf("*");
	}
	while (miyan(password, k) != 1) {
		printf("您密码输入错误\n");
		printf("请输入正确六位密码：\n");
		for (i = 0; i < 6; i++) {
			password[i] = getchar();
			printf("*");
		}
	}
	if (miyan(password, k) == 1) {
		printf("您已成功登录\n");
		return k;
	} else
		return -1;
}
void cunkuan(int m) { //存款
	fflush(stdin);
	int k;
	printf("\n\n");
	printf("\t\t||================================================================||\n");
	printf("\t\t||                           *存款金额*                           ||\n");
	printf("\t\t||================================================================||\n");
	printf("\t\t||                                                                ||\n");
	printf("\t\t||                                                                ||\n");
	printf("\t\t||         1、200        2、400        3、600        4、800       ||\n");
	printf("\t\t||                                                                ||\n");
	printf("\t\t||                                                                ||\n");
	printf("\t\t||         5、1000        6、2000        7、4000        8、6000   ||\n");
	printf("\t\t||                                                                ||\n");
	printf("\t\t||         9、其他金额           0、退出存款                      ||\n");
	printf("\t\t||================================================================||\n");
	printf("\t\t||================================================================||\n");
	printf("\n\n\t\t\t请输入你的选择：");
	scanf("%d", &k);
	while (k != 0) {
		switch (k) {
			case 1: {
				jin = 200;
				printf("您存款前余额为：%lf\n", user[m].YuE);
				user[m].YuE += jin;
				printf("您存后的余额为：%lf,您已存款成功！\n", user[m].YuE);
				break;
			}
			case 2: {
				jin = 400;
				printf("您存款前余额为：%lf\n", user[m].YuE);
				user[m].YuE += jin;
				printf("您存后的余额为：%lf,您已存款成功！\n", user[m].YuE);
				break;
			}
			case 3: {
				jin = 600;
				printf("您存款前余额为：%lf\n", user[m].YuE);
				user[m].YuE += jin;
				printf("您存后的余额为：%lf,您已存款成功！\n", user[m].YuE);
				break;
			}
			case 4: {
				jin = 800;
				printf("您存款前余额为：%lf\n", user[m].YuE);
				user[m].YuE += jin;
				printf("您存后的余额为：%lf,您已存款成功！\n", user[m].YuE);
				break;
			}
			case 5: {
				jin = 1000;
				printf("您存款前余额为：%lf\n", user[m].YuE);
				user[m].YuE += jin;
				printf("您存后的余额为：%lf,您已存款成功！\n", user[m].YuE);
				break;
			}
			case 6: {
				jin = 2000;
				printf("您存款前余额为：%lf\n", user[m].YuE);
				user[m].YuE += jin;
				printf("您存后的余额为：%lf,您已存款成功！\n", user[m].YuE);
				break;

			}
			case 7: {
				jin = 4000;
				printf("您存款前余额为：%lf\n", user[m].YuE);
				user[m].YuE += jin;
				printf("您存后的余额为：%lf,您已存款成功！\n", user[m].YuE);
				break;
			}
			case 8: {
				jin = 8000;
				printf("您存款前余额为：%lf\n", user[m].YuE);
				user[m].YuE += jin;
				printf("您存后的余额为：%lf,您已存款成功！\n", user[m].YuE);
				break;
			}
			case 9: {
				printf("请输入您的存款余额：%d\n", &jin);
				printf("您存款前余额为：%lf\n", user[m].YuE);
				user[m].YuE += jin;
				printf("您存后的余额为：%lf,您已存款成功！\n", user[m].YuE);

				break;
			}
		}
		printf("输入0返回主页面，或者输入其他选择金额继续存款.\n");
		scanf("%d", &k);
	}
}
void qukuan(int m) { //取款
	fflush(stdin);
	date();
	int k;
	printf("\n\n");
	printf("\t\t||================================================================||\n");
	printf("\t\t||                           *取款金额*                           ||\n");
	printf("\t\t||================================================================||\n");
	printf("\t\t||                                                                ||\n");
	printf("\t\t||                                                                ||\n");
	printf("\t\t||         1、200        2、400        3、600        4、800       ||\n");
	printf("\t\t||                                                                ||\n");
	printf("\t\t||                                                                ||\n");
	printf("\t\t||         5、1000        6、2000        7、4000        8、6000   ||\n");
	printf("\t\t||                                                                ||\n");
	printf("\t\t||         9、其他金额           0、退出存款                      ||\n");
	printf("\t\t||================================================================||\n");
	printf("\t\t||================================================================||\n");
	printf("\n\n\t\t\t请输入你的选择：");
	scanf("%d", &k);
	while (k != 0) {
		switch (k) {
			case 1: {
				jin = 200;
				if (jin <= user[m].YuE) {
					printf("您取款前余额为：%lf\n", user[m].YuE);
					user[m].YuE -= jin;
					printf("您取后的余额为：%lf,您已取款成功！\n", user[m].YuE);
				} else {
					printf("您的账户余额不足，无法取款！\n");

				}
				break;
			}
case2: {
				jin = 400;
				if (jin <= user[m].YuE) {
					printf("您取款前余额为：%lf\n", user[m].YuE);
					user[m].YuE -= jin;
					printf("您取后的余额为：%lf,您已取款成功！\n", user[m].YuE);
				} else {
					printf("您的账户余额不足，无法取款！\n");

				}
				break;
			}

			case 3: {
				jin = 600;
				if (jin <= user[m].YuE) {
					printf("您取款前余额为：%lf\n", user[m].YuE);
					user[m].YuE -= jin;
					printf("您取后的余额为：%lf,您已取款成功！\n", user[m].YuE);
				} else {
					printf("您的账户余额不足，无法取款！\n");

				}
				break;
			}
			case 4: {
				jin = 800;
				if (jin <= user[m].YuE) {
					printf("您取款前余额为：%lf\n", user[m].YuE);
					user[m].YuE -= jin;
					printf("您取后的余额为：%lf,您已取款成功！\n", user[m].YuE);
				} else {
					printf("您的账户余额不足，无法取款！\n");

				}
				break;
			}
			case 5: {
				jin = 1000;
				if (jin <= user[m].YuE) {
					printf("您取款前余额为：%lf\n", user[m].YuE);
					user[m].YuE -= jin;
					printf("您取后的余额为：%lf,您已取款成功！\n", user[m].YuE);
				} else {
					printf("您的账户余额不足，无法取款！\n");

				}
				break;
			}
			case 6: {
				jin = 2000;
				if (jin <= user[m].YuE) {
					printf("您取款前余额为：%lf\n", user[m].YuE);
					user[m].YuE -= jin;
					printf("您取后的余额为：%lf,您已取款成功！\n", user[m].YuE);
				} else {
					printf("您的账户余额不足，无法取款！\n");

				}
				break;
			}
			case 7: {
				jin = 4000;
				if (jin <= user[m].YuE) {
					printf("您取款前余额为：%lf\n", user[m].YuE);
					user[m].YuE -= jin;
					printf("您取后的余额为：%lf,您已取款成功！\n", user[m].YuE);
				} else {
					printf("您的账户余额不足，无法取款！\n");

				}
				break;

			}
			case 8: {
				jin = 6000;
				if (jin <= user[m].YuE) {
					printf("您取款前余额为：%lf\n", user[m].YuE);
					user[m].YuE -= jin;
					printf("您取后的余额为：%lf,您已取款成功！\n", user[m].YuE);
				} else {
					printf("您的账户余额不足，无法取款！\n");

				}
				break;
			}
			case 9: {
				printf("请输入您的qu款金额：\n");
				scanf("%d", &jin);
				if (jin <= user[m].YuE) {
					printf("您取款前余额为：%lf\n", user[m].YuE);
					user[m].YuE -= jin;
					printf("您取后的余额为：%lf,您已取款成功！\n", user[m].YuE);
				} else {
					printf("您的账户余额不足，无法取款！\n");

				}
				break;
			}

		}
		printf("输入0，返回主页面，或者您可以选择金额继续取款。\n");
		scanf("%d", &k);
	}
}
void display(int m) { //查询
	fflush(stdin);
	date();
	printf("您的账户为:%s\n", user[m].idnum);
	printf("您的身份证号为:%s\n", user[m].idnumber);
	printf("您的账户余额为:%lf\n", user[m].YuE);
	printf("您的xingming为:%s\n", user[m].name);
	printf("按#返回主页面！");
	scanf("%c", &a);
}
void lixi(int m) { //利息计算
	date();
	printf("按#返回主页面！");
	scanf("%c", &a);
}
void daikuan(int m) { //贷款
	date();
	int k;
	printf("\n\n");
	printf("\t\t||================================================================||\n");
	printf("\t\t||                           *贷款金额*                           ||\n");
	printf("\t\t||================================================================||\n");
	printf("\t\t||                                                                ||\n");
	printf("\t\t||                                                                ||\n");
	printf("\t\t||         1、200        2、400        3、600        4、800       ||\n");
	printf("\t\t||                                                                ||\n");
	printf("\t\t||                                                                ||\n");
	printf("\t\t||         5、1000        6、2000        7、4000        8、6000   ||\n");
	printf("\t\t||               (以上贷款金额利率为0.1/每年                      ||\n");
	printf("\t\t||             您也可选择超过6000元的贷款利率为0.12/每年)         ||\n");
	printf("\t\t||================================================================||\n");
	printf("\t\t||================================================================||\n");
	printf("\n\n\t\t\t请输入你的贷款金额：");
	scanf("%d", &k);
	printf("请确定您的贷款金额为%d", k);
	printf("<1>确认 <2>取消");
	int g;
	scanf("%d", &g);
	if (g == 1) {
		printf("您已贷款成功！");
		printf("您款前余额为：%lf", user[m].YuE);
		user[m].YuE += k;
		printf("您取后的余额为：%lf", user[m].YuE);
	} else {
		printf("请您输入新的贷款金额");
		scanf("%d", &g);
		printf("您已贷款成功！");
		printf("您款前余额为：%lf", user[m].YuE);
		user[m].YuE += k;
		printf("您取后的余额为：%lf", user[m].YuE);
	}
	printf("按#返回主页面！");
	scanf("%c", &a);
}
void date() { //显示当前日期
	printf("当前日期：");
	system("date/t");
	printf("当前时间：");
	system("time/t");
}




typedef char KeyType;
// typedef struct 
// {//结构描述
// 	char number[6];								//序号 
// 	char name[6];								//姓名
// 	char sche[6];								//存款日期 
// 	char time[6];								//到期时间
// }InfoType;
// typedef struct
// {//关键字-静态链表结点类型
// 	KeyType keys[keylen];						//关键字（排队号）
// 	InfoType others;
// 	int next;
// }SLNode;
// typedef struct 
// {//关键字序列-静态链表类型
// 	SLNode sl[MaxSpace];						//静态链表
// 	int keynum;									//关键字字符数
// 	int length;									//表长
// }SLList;

typedef int ArrType_n[RADIX_n];  				//数字字符
typedef int ArrType_c[RADIX_c];  				//字母字符

// KeyType key[keylen],kl[4];

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
		// printf("\n序号 姓名 存款日期 到期时间 \n");
		// scanf ("%s %s %s %s",  &L->sl[i].others.number, &L->sl[i].others.name,&L->sl[i].others.sche,
		// 	&L->sl[i].others.time);
		// fflush(stdin);   					//清空输入缓冲区
		// ++i;
		// printf ( "继续输入吗? y/n:");
	}while((yn=getchar())=='y' || yn=='Y');
	printf("\n");
	L->length=i-1;
	//RadixSort(L);
	//Arrange(L);
	return true;
}


int info_query()
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


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#define OK 1
#define ERROR 0
#define OVERFLOW -2
using namespace std;
typedef int Status;
#define MAXSIZE 50000
//#define _CRT_SECURE_NO_WARNINGS
static int number;
typedef struct branch_account {
	long long int account;
	double money;
}branch_account;//分帐号表的结点，包括账号和余额，余额在函数3中进行修改
// typedef struct {
// 	branch_account* a;
// 	int length;
// }SqList;//分帐号表，包括一个分帐号结点类型的数组和数组长度
// typedef struct LNode {
// 	long long int account;//账号
// 	char name[20];//姓名
// 	long long int telephone;//联系方式
// 	long long int ID;//身份证号
// 	double money;//余额
// 	SqList branch;//分帐号表
// 	int VIP;//1表示是VIP，0表示不是VIP 
// 	struct LNode* next;//指向下一结点的指针
// }LNode, * LinkList;//用户信息链表
//

void InitList(LinkList& L) {
	L = (LinkList)malloc(sizeof(LNode));
	if (!L)
		exit(OVERFLOW);
	L->next = NULL;
}//链表初始化
void Create(LinkList& L) {
	LinkList p;
	int flag = 1;
	cout << "请输入客户账号、姓名、联系方式、身份证号等信息。" << endl;
	p = (LinkList)malloc(sizeof(LNode));
	if (!p)
		exit(OVERFLOW);
	p->branch.length = 0;
	cout << "请输入16位或19位账号" << endl;
	cin >> p->account;
	cout << "请输入姓名" << endl;
	cin >> p->name;
	cout << "请输入联系方式（11位号码）" << endl;
	cin >> p->telephone;
	cout << "请输入18位身份证号" << endl;
	cin >> p->ID;
	cout<<"请选择用户是否是VIP，是请输入1,否则请输入0";
	cin >> p->VIP;
	//cin >> p->account >> p->name >> p->telephone >> p->ID >> flag;
	cout << "若客户开设分帐户，请输入1，否则输入0" << endl;
	cin >> flag;
	if (flag) {
		cout << "请输入分帐户数目" << endl;
		cin >> p->branch.length;
		// p->branch.a = (branch_account*)malloc(sizeof(branch_account)*MAXSIZE);
		// for (int i = 0; i < p->branch.length; i++) {
		// 	cout << "请输入分帐户" << i+1 << "的账号";
		// 	cin >> p->branch.a[i].account;
		// 	p->branch.a[i].money = 0;
		// }
	}//根据flag判断是否有分帐户，建立分帐户
	p->money = 0;
	p->next = L->next;
	L->next = p;
}//建立一个客户信息系统
void insert(LinkList& L) {
	LinkList s = L->next;
	int flag;
	s = (LinkList)malloc(sizeof(LNode));
	if (!s)
		exit(OVERFLOW);
	s->branch.length = 0;
	cout << "请输入客户账号、姓名、联系方式、身份证号等信息。" << endl;
	cout << "请输入16位或19位账号" << endl;
	cin >> s->account;
	cout << "请输入姓名" << endl;
	cin >> s->name;
	cout << "请输入联系方式（11位号码）" << endl;
	cin >> s->telephone;
	cout << "请输入18位身份证号" << endl;
	cin >> s->ID;
	cout<<"请选择用户是否是VIP，是请输入1,否则请输入0";
	cin >> s->VIP;
	cout << "若客户开设分帐户，请输入1，否则输入0" << endl;
	cin >> flag;
	if (flag) {
		// cout << "请输入分帐户数目" << endl;
		// cin >> s->branch.length;
		// s->branch.a = (branch_account*)malloc(sizeof(branch_account) * MAXSIZE);
		// for (int i = 0; i < s->branch.length; i++) {
		// 	cout << "请输入分帐户" << i+1 << "的账号";
		// 	cin >> s->branch.a[i].account;
		// 	s->branch.a[i].money = 0;
		// }
	}
	s->money = 0;
	s->next = L->next;
	L->next = s;
}//依次插入客户信息，与创建基本类似
void DestroyList (LinkList& L) {
	LinkList p;
	while (L) {
		p = L;
		L = L->next;
		free(p);
	}
}//销毁链表，用于文件操作中信息存盘后内存的清空
void DeleteElem(LinkList& L, int i) {
	LinkList p = L;
	LinkList q;
	int j;
	for (j = 0; p->next && j < i - 1; j++)
		p = p->next;
	if (!(p->next) || j > i - 1)
		cout << "删除失败" << endl;
	q = p->next;
	p->next = q->next;
	free(q);
}//按序号对客户信息进行删除
void DeleteName(LinkList& L) {
	LinkList p = L->next;
	LinkList q;
	string name;
	int count=1,flag=0;
	cout << "请输入你想删除的客户的姓名" << endl;
	cin >> name;
	if (!p)
		cout << "系统中没有任何客户信息，查找失败" << endl;
	else {
		while (p!= NULL) {
			if (name == p->name) {
				flag = 1;
				DeleteElem(L, count);
				cout << name << "客户删除成功" << endl;
				break;
				//p = p->next;
				
			}
			else {
				p = p->next;
				count++;
			}	
		}
	}
	//if (!flag)
		//cout << "删除失败" << endl;
}//按姓名对客户信息进行删除
void DeleteAccount(LinkList& L) {
	LinkList p = L->next;
	LinkList q;
	int account;
	int count = 1, flag = 0;
	cout << "请输入你想删除的客户的账号" << endl;
	cin >> account;
	if (!p)
		cout << "系统中没有任何客户信息，查找失败" << endl;
	else {
		while (p != NULL) {
			if (account == p->account) {
				flag = 1;
				DeleteElem(L, count);
				cout << "删除成功" << endl;
				break;
			}
			else {
				p = p->next;
				count++;
			}
		}
	}
	//if (!flag)
		//cout << "删除失败" << endl;
}//按账号对客户信息进行删除
void sort(LinkList& L) {
	LinkList p;
	LinkList q;
	LinkList tail = NULL;
	while (L->next->next!= tail) {
		p = L;
		q = L->next;
		while (q->next != tail) {
			if (q->account > q->next->account) {
				p->next = q->next;
				q->next = q->next->next;
				p->next->next = q;
				q = p->next;
			}
			p = p->next;
			q = q->next;
		}
		tail = q;
	}
}//对客户信息按照账号顺序进行排序
void printList(LinkList L) {
	LinkList p = L->next;
	int n = 1;
	cout << endl << "    --------------------------------------------------------------------------------------------------------"<< endl;
	cout << "            账户                 姓名         联系方式           身份证号               分账号" << endl;
	cout << "    --------------------------------------------------------------------------------------------------------" << endl;
	if (p==NULL)
		cout << "系统中没有任何信息" << endl;
	else {
		while (p) {
			// cout << n << "   " << p->account << "        " << p->name << "        " << p->telephone << "        " << p->ID;
			// if (p->branch.length != 0) {
			// 	cout << "        " << p->branch.a[0].account << endl;
			// 	for (int i = 1; i < p->branch.length; i++) {
			// 		cout<<"                                                                                       "<< p->branch.a[i].account << endl;
			// 	}
			// }
			// else
			// 	cout << "                无" << endl;
			// p = p->next;
			// n++;	
		}
	}
	cout<< "    --------------------------------------------------------------------------------------------------------" << endl;
}//输出所有用户的信息
void SearchName(LinkList L) {
	int flag = 0;
	LinkList p = L->next;
	int count = 1;
	string name;
	cout << "请输入你想查找的客户的姓名" << endl;
	cin >> name;
	if (p == NULL)
		cout << "系统中没有任何客户信息，查找失败" << endl;
	else {
		while (p) {
			if (name == p->name) {
				flag = 1;
				cout << "要查找的是第" << count << "位客户" << endl;
				cout<< "账号  "<<p->account << "  姓名  " << p->name << "  联系方式  " << p->telephone << "  身份证号  " << p->ID << endl;
			}
			p = p->next;
			count++;
		}
	}
	if (!flag)
		cout << "查找失败" << endl;
}//按照姓名进行查找
void Revise(LinkList &L){
	LinkList p=L->next;
	int flag = 0;
	string name;
	char name1[20];
	long long int telephone,telephone1;
	long long int account,account1;
	cout<<"请输入你要修改的项目"<<endl;
	cout<<"1.修改姓名"<<endl;
	cout<<"2.修改联系方式"<<endl;
	cout<<"3.修改账号"<<endl;
	int way;
	cin>>way;
	switch(way){
		case 1:
			cout<<"请输入原始姓名" <<endl;
			cin>>name;
			if(p==NULL)
				cout<< "系统中没有任何客户信息" << endl;
			else{
				while(p){
					if(name==p->name){
						flag=1;
						cout<<"请输入你要修改的姓名"<<endl;
						cin>>name1;
						strcpy(p->name,name1);
						break;
					}
					p=p->next;
				}
			}
			if(!flag)
				cout<<"系统中没有该客户"<<endl;
			break;
		case 2:
			p=L->next;
			cout<<"请输入原始联系方式"<<endl;
			cin>>telephone;
			if(p==NULL)
				cout<< "系统中没有任何客户信息" << endl;
			else{
				while(p){
					if(telephone==p->telephone){
						flag=1;
						cout<<"请输入你要修改的联系方式"<<endl;
						cin>>telephone1;
						p->telephone=telephone1;
						break;
					}
					p=p->next;
				}
			}
			if(!flag)
				cout<<"系统中没有该客户"<<endl;
			break;
		case 3:
			p=L->next;
			cout<<"请输入原始账号"<<endl;
			cin>>account;
			if(p==NULL)
				cout<< "系统中没有任何客户信息" << endl;
			else{
				while(p){
					for(int i=0;i<p->branch.length;i++){
						if(account==p->account){
							flag=1;
							cout<<"请输入你要修改的账号"<<endl;
							cin>>account1;
							p->account=account1;
							break;
						}
						else
							// if(account==p->branch.a[i].account){
							// 	flag=1;
							// 	cout<<"请输入你要修改的账号"<<endl;
							// 	cin>>account1;
							// 	p->branch.a[i].account=account1;
							// 	break;
							// }
					} 
					p=p->next;	
				}
			}
			if(!flag)
				cout<<"系统中没有该客户"<<endl;
			break;
		default:
			cout<<"没有该功能"<<endl;			
	}
}
void SearchAccount(LinkList L) {
	int flag = 0;
	LinkList p = L->next;
	int count = 1;
	int account;
	cout << "请输入你想查找的客户的账号" << endl;
	cin >> account;
	if (p == NULL)
		cout << "系统中没有任何客户信息，查找失败" << endl;
	else {
		while (p) {
			if (account == p->account) {
				flag = 1;
				cout << "要查找的是第" << count << "位客户" << endl;
				cout << "账号 " << p->account << "姓名 " << p->name << "联系方式 " << p->telephone << "身份证号 " << p->ID << endl;
			}
			p = p->next;
			count++;
		}
	}
	if (!flag)
		cout << "查找失败" << endl;
}//按照账号进行查找
void mainwork_7(LinkList& L);
void shixian(LinkList&L);
void mainwork_2(LinkList &L) {
	int flag = 0;
	int menu;
	char temp;
	//system("color lf");
	cout << "                ***************欢迎使用客户信息系统***************" << endl;
	cout << "           **                  " << "1.客户信息系统的建立" << "                **                  " << endl;
	cout << "           **                  " << "2.插入客户信息" << "                      **                  " << endl;
	cout << "           **                  " << "3.查询客户信息" << "                      **                  " << endl;
	cout << "           **                  " << "4.删除客户信息" << "                      **                  " << endl;
	cout << "           **                  " << "5.显示客户信息系统记录" << "              **                  " << endl;
	cout << "           **                  " << "6.修改客户信息"<< "                       **                  " << endl;
	cout << "           **                  " << "7.进行文件存取操作" << "                  **                  " << endl;
	cout << "           **                  " << "0.退出信息系统" << "                      **                  " << endl;
	cout << "                **************************************************" << endl;
	cout << "请选择0-7" << endl;
	cin >> menu;
	while (menu != 0) {
		switch (menu)
		{
			case 1:
				if (flag == 0) {
					Create(L);
					cout << "建立系统" << endl;
					printList(L);
					flag = 1;
				}
				else
					cout << "已建立系统，请选择其他功能" << endl;
				break;
			case 2:
				if (flag == 1||L->next) {
				insert(L);
				cout << "插入后" << endl;
				sort(L);
				printList(L);
				}
				else
					cout << "还未建立系统，请先建立"<<endl;
				break;
			case 3:
				int way;
				if (L!= NULL) {
					if (flag||L->next) {
						cout << "选择查找方式" << endl;
						cout << "按姓名请输入1，按账号请输入2" << endl;
						cin >> way;
						if (way == 1)
							SearchName(L);
						else
							SearchAccount(L);

					}
				}
				else
					cout << "系统中没有任何信息" << endl;
				break;
			case 4:
				if (L!= NULL) {
					if (flag||L->next) {
						cout << "选择删除方式" << endl;
						cout << "按姓名请输入1，按账号请输入2" << endl;
						cin >> way;
						if (way == 1)
							DeleteName(L);
						else
							DeleteAccount(L);

					}
				}
				else
					cout << "系统中没有任何信息" << endl;
				break;
			case 5:
				cout << "当前系统信息如下" << endl;
				printList(L);
				break;
			case 6:
				Revise(L); 
				break;
			case 7:
				mainwork_7(L);
				break;
			case 8:
				shixian(L);
				break;
			case 0:
				exit(0);
			default:
				cout << "没有此功能,请重新输入" << endl;
		}
		cout << "选择功能：";
		cin >> menu;
	}
}
static void write(FILE* fp, LinkList L) {
	LinkList p = L->next;
	while (p != NULL) {
		//fwrite(&p, sizeof(struct LNode), 1, fp);
		fprintf(fp, "%lld %s %lld %lld %lf %d %d ", p->account, p->name, p->telephone, p->ID, p->money, p->VIP, p->branch.length);
		for (int i = 0; i < p->branch.length; i++) {
			fprintf(fp, "%lld %lf ", p->branch.a[i].account,p->branch.a[i].money);
		}
		fprintf(fp, "\n");
		p = p->next;
	}
}//写入文件
void WriteFile(char* fname, LinkList L) {
	FILE* fp;
	fp = fopen(fname, "wb");
	if (fp == NULL) {
		cout << "文件产生失败" << endl;
	}
	write(fp, L);
	fclose(fp);
}//写入文件
static void read(FILE* fp, LinkList &L, int b) {
	/*while (L->next != NULL) {
		LinkList p = (LinkList)malloc(b);
		//fread(&p, b, 1, fp);
		fscanf(fp, "%lld %s %lld %lld %lf ", &p->account, &p->name, &p->telephone, &p->ID, &p->money);
		for (int i = 0; i < p->branch.length; i++) {
			fscanf(fp, "%lld %lf", &p->branch.a[i].account, &p->branch.a[i].money);
		}
		p = p->next;
	}*/
	LinkList tail=L;
	while(!feof(fp)) {
		LinkList p = (LinkList)malloc(b);
		//fread(&p, b, 1, fp);
		fscanf(fp, "%lld%s%lld%lld%lf%d%d", &p->account, &p->name, &p->telephone, &p->ID, &p->money, &p->VIP, &p->branch.length);
		if (p->branch.length != 0) {
			p->branch.a = (branch_account*)malloc(sizeof(branch_account) * MAXSIZE);
			for (int i = 0; i < p->branch.length; i++) {
				fscanf(fp, "%lld%lf", &p->branch.a[i].account, &p->branch.a[i].money);
			}
		}
		fscanf(fp, " ");
		/*if (L == NULL) {
			L = p;
			p->next = NULL;
		}
		else {
			q = L;
			while (q->next != NULL)
				q = q->next;
		}
		q->next = p;
		p->next = NULL;*/
		tail->next = p;
		tail = p;
		tail->next = NULL;
	}
}//读出文件
void ReadFile(char* fname, LinkList &L) {
	FILE* fp;
	int b;
	fp = fopen(fname, "rb");
	if (fp == NULL) {
		cout << "文件打开失败" << endl;
	}
	b = sizeof(struct LNode);
	L = (LinkList)malloc(b);
	if (!L)
		exit(OVERFLOW);
	L->next = NULL;
	//fread(L, b, 1, fp);
	read(fp, L, b);
	fclose(fp);
}//读出文件
void mainwork_7(LinkList &L) {
	int menu;
	cout << "****************文件操作******************" << endl;
	cout << "             1.客户信息存盘                           " << endl;
	cout << "             2.从文件恢复内存的客户信息               " << endl;
	cout << "             0.退出                                   " << endl;
	cout << "******************************************" << endl;
	cout << "选择功能" << endl;
	cin >> menu;
	char* fname = new char[20];
	//fname = "customer.txt";
	strcpy(fname, "customer.dat");
	while (menu != 0) {
		switch (menu)
		{
		case 1:
			cout << "存储信息到文件customer.dat中" << endl;
			WriteFile(fname, L);
			DestroyList(L);
			cout << "数据文件customer.dat建立成功";
			cout << "内存已清空" << endl;
			break;
		case 2:
			cout << "准备将数据文件customer.dat恢复到内存中" << endl;
			LinkList L;
			ReadFile(fname, L);
			cout << "数据文件customer.dat已经读入内存" << endl;
			cout << "是否继续对客户信息进行操作？继续操作请按3,否则请选择（0-2）中的操作" << endl;
			int way;
			cin >> way;
			if (way == 3)
				mainwork_2(L);
			break;
		case 0:
			exit(0);
		default:
			cout << "没有此功能,请重新输入" << endl;
		}
		cout << "选择功能：";
		cin >> menu;
	}
}
void ZClassify(LinkList &L,LinkList &H,LinkList &M,LinkList &LOW){
	while(L){
		if(L->money>=1000000)
		H->next=L;
		if(L->money>=100000&&L->money<1000000)
		M->next=L;
		if(L->money<100000)
		LOW->next=L;
		L=L->next;
	}
}//按资产划分
void VClassify(LinkList &L,LinkList &Y,LinkList &N){
	while(L){
		if(L->VIP)
		Y->next=L;
		else
		N->next=L;
		L=L->next;
	}
} 
void shixian(LinkList &L){
	LinkList H=(LinkList)malloc(sizeof(LNode));
	LinkList M=(LinkList)malloc(sizeof(LNode));
	LinkList LOW=(LinkList)malloc(sizeof(LNode));
	char *filename= new char[20];
	ZClassify(L,H,M,LOW);
	char *filename1= new char[20];
	cout<<"请输入文件名"<<endl;
	cin>>filename1;
	strcpy(filename, filename1);
	WriteFile(filename,LOW);
	cout<<"资产低于十万的客户信息为"<<endl;
	ReadFile(filename,LOW);
	WriteFile(filename,M);
	cout<<"资产高于十万低于一百万的客户资料为"<<endl;
	ReadFile(filename,M);
	WriteFile(filename,H);
	cout<<"资产高于一百万的客户信息为"<<endl;
	ReadFile(filename,H);
	LinkList Y=(LinkList)malloc(sizeof(LNode));
	LinkList N=(LinkList)malloc(sizeof(LNode));
	VClassify(L,Y,N);
	WriteFile(filename,Y);
	cout<<"VIP客户信息为"<<endl;
	ReadFile(filename,Y);
	WriteFile(filename,N);
	cout<<"不是VIP客户信息为"<<endl;
	ReadFile(filename,N);
}

int vip_system() {
	LinkList L;
	InitList(L);
	mainwork_2(L);  //363行 
	//mainwork_7(L);
}


//6.银行网点查询：网点导航，网点增删改 参考校园导游
// 0正门测温区；1自助服务区（ATM机）；2产品展示区；3客户等候区；4综合业务柜 ；5理财服务区； 
typedef struct ArcCell{
	int assign;//权值 
}ArcCell,adjmatrix[MAX][MAX];//邻接矩阵 
typedef struct data{
	int ID;//编号 
	char  name[30];//名称 
	char account[256]; //功能简介 
}data;//网点信息
typedef struct structure{
	data vexs[MAX];//顶点向量 
	adjmatrix arcs;// 邻接矩阵 
	int apeum,sidnum;//顶点数和边数 
}structure; 
//初始化地图 
structure initmap(){//这里为什么用结构体。用void不行吗，我不理解 
	structure a;
	a.apeum=6;//顶点个数 
	a.sidnum=8;//边的个数
	for(i=0;i<a.apeum;i++)
		a.vexs[i].ID=i;//编号
	strcpy(a.vexs[0].name,"正门测温区");
	strcpy(a.vexs[0].account,"测量体温，由此进出银行。");
	strcpy(a.vexs[1].name,"自助服务区（ATM机）");
	strcpy(a.vexs[1].account,"客户自主完成存取款、查询余额、修改密码（仅限开户地设备）、转账。");
	strcpy(a.vexs[2].name,"产品展示区");
	strcpy(a.vexs[2].account,"展示银行产品");
	strcpy(a.vexs[3].name,"等候区");
	strcpy(a.vexs[3].account,"客户休息、等待业务场地");
	strcpy(a.vexs[4].name,"综合业务柜");
	strcpy(a.vexs[4].account,"人工办理各种业务");
	strcpy(a.vexs[5].name,"理财服务区");
	strcpy(a.vexs[5].account,"理财产品介绍、推荐");
	for(i=0;i<a.apeum;i++)
		for(j=0;j<a.apeum;j++)
			a.arcs[i][j].assign=MAXINT;//初始化邻接矩阵 
	a.arcs[0][1].assign=2;a.arcs[0][3].assign=4;a.arcs[0][5].assign=6;
	a.arcs[1][5].assign=4;a.arcs[2][3].assign=1;a.arcs[3][4].assign=2;
	a.arcs[3][5].assign=2;a.arcs[4][5].assign=2;//邻接矩阵赋权值 
	for(i=0;i<a.apeum;i++)
		for(j=0;j<a.apeum;j++)
			a.arcs[j][i].assign=a.arcs[i][j].assign;
	return a;}

//查询网点信息 输出附近所有路径 
void inquire(structure a){
	j=1;
	printf("请选择查找地点:1:大门测温区；2：自助服务区；3：产品展示区；4：客户等候区；5：综合业务柜；6：理财服务区\n");
	scanf("%d",&i);
	while(j){
		if(i<=6&&i>=1){
			printf("编号  名称             简介\n");
			printf("%-2d%-18s%-40s\n",a.vexs[i-1].ID,a.vexs[i-1].name,a.vexs[i-1].account);
			j=0;}
		else {
			printf("您所输入的编号不存在，请重新输入:");
			scanf("%d",&i);}}
}
void print(structure a){//打印所有信息
	printf("编号  名称             简介\n");
	for(i=0;i<a.apeum;i++)
		printf("%-2d%-18s%-40s\n",a.vexs[i].ID,a.vexs[i].name,a.vexs[i].account);}
int locID(structure a,int b){
	for(i=0;i<a.apeum;i++)
		{if(b==a.vexs[i].ID) 
			return i;}
		printf("您输入的编号不存在，请重新输入：\n");
	 	scanf("%d",&j);
	 	locID(a,j);} 
/*int locNA(structure a,char b[]){
	for(i=0;i<a.apeum;i++)
		if(!strcmp(b,a.vexs[i].name)) return a.vexs[i].ID;
	else {char c[20];
		printf("您输入的名称有误，请重新输入：\n");
	 	scanf("%s",c);
	 	locNA(a,c);}} */
void lane(structure a,int m,int n,int k ){
	int s,x=0,t=k+1;
	if(d[k]==n){
		for(s=0;s<k;s++)
			printf("%s-->",a.vexs[d[s]].name);
		printf("%s\n\n",a.vexs[d[s]].name); 
	}
	else {
		s=0;
		while(s<a.apeum){
			if((a.arcs[d[k]][s].assign<MAXINT)&&(visited[s]==0))
			{	visited[s]=1;
				d[k+1]=s;
				lane(a,m,n,t);
				visited[s]=0;
			}
			s++;
		}
	}

}
void path(structure a){//路径 
	int q,w;
	print(a);
	printf("选择起始点编号\n");
	scanf("%d",&q);
	q=locID(a,q);
	scanf("%d",&w);
	w=locID(a,w);
	d[0]=q;
	for(i=0;i<a.apeum;i++)
		visited[i]=0;
	visited[q]=1;
	lane(a,q,w,0);}
int up(structure &a,int i,int b){
	if(b==1){
		printf("请输入修改名称\n");
		scanf("%s",&a.vexs[i].name);
		return 1;}
	else if(b==2){
		printf("请输入修改简介\n");
		scanf("%s",&a.vexs[i].account);
		return 1;}
	else {
		printf("请输入依次修改的名称、简介\n");
		scanf("%s",&a.vexs[i].name);
		scanf("%s",&a.vexs[i].account);
		return 1;
		
	}
	
}
int update(structure &a){//修改信息 
	print(a); 
	printf("请输入要修改的编号\n");
	scanf("%d",&i);
	locID(a,i);
	printf("选择修改项目：1：修改名称；2：修改简介；3：修改全部");
	scanf("%d",&j);
	while(j<1||j>3){
		printf("输入有误，请重新输入：\n");
		scanf("%d",&j);}
	up(a,i,j);} 
void enside(structure &a){//增加一条边 
	int k;
	printf("以下是现存详细信息\n");
	print(a);
	printf("请依次输入边起始点和权值\n");
	scanf("%d%d%d",&i,&j,&k);
	i=locID(a,i);j=locID(a,i);//错误的话不好区分起始点那个错误 
	a.arcs[i][j].assign=k;
	a.arcs[j][i].assign=k;
	a.sidnum++;}
void envex(structure &a){//增加一个节点 
	printf("请依次输入增加结点的编号、名称、简介\n");
	scanf("%d%s%s",&a.vexs[a.apeum].ID,&a.vexs[a.apeum].name,&a.vexs[a.apeum].account);
	a.apeum++;
	for(i=0;i<a.apeum;i++)
		{a.arcs[a.apeum][i].assign=MAXINT;
		a.arcs[i][a.apeum].assign=MAXINT;}}
void deves(structure &a){
	int k;
	printf("现在已存在的信息:\n");
	print(a);
	printf("请输入要删除的景点编号\n");
	scanf("%d",&k);
	locID(a,k);
	for(i=k;i<a.apeum-1;i++){
		strcpy(a.vexs[i].name,a.vexs[i+1].name);
		strcpy(a.vexs[i].account,a.vexs[i+1].account);}
	for(i=k;i<a.apeum-1;i++)
		for(j=0;j<a.apeum;j++)
			a.arcs[j][i]=a.arcs[j][i+1];
	a.apeum=a.apeum-1;}
void deape(structure &a){//删除一条边
	printf("现在已存在的信息:\n") ;
	printf("请依次输入要删除边的起始点\n");
	scanf("%d %d",&i,&j);
	a.arcs[i][j].assign=MAXINT;
	a.arcs[j][i].assign=MAXINT;
	a.sidnum=a.sidnum-1; 
	
}
void work(){
	structure a=initmap();
	printf("**********欢迎使用网点导航系统**********\n");
	printf("          菜               单           \n");
	printf("         ->1、网点信息介绍                \n"); 
	printf("         ->2、查询路线                     \n");
	printf("         ->3、更改图信息                   \n");
	printf("         ->4、退出                       \n");
	printf("****************************************\n");
	printf("请输入你的选择：\n");
	scanf("%d",&i);
	while(i!=4){
		switch(i){
			case 1:print(a);break;
			case 2:path(a);break;
			case 3:printf("请选择更改类型：1、修改信息；2、增加边；3、增加点\n");
				   printf("                4、删除边  ；5、删除点           \n");
				   scanf("%d",&j);
				   if(j<1||j>5){
				   		printf("输入有误,请重新输入\n");
				   		scanf("%d",&j);}
				   	else if(j==1)update(a);
				   	else if(j==2)enside(a);
				   	else if(j==3)envex(a);
				   	else if(j==4)deape(a);
				   	else if(j==5)deves(a);
				   	break;
			case 4:exit(0);
			default:printf("没有此功能，请重新输入\n");}//endswitch
		printf("选择功能：\n");
		scanf("%d",&i);}// endwhile
	
}
int wangdianchaxun(){
work();
return 1;
}


#include <stdio.h>
#include <stdlib.h>
#define MAXSTRLEN 255         //最大串长
typedef char SString[MAXSTRLEN+1];   //串的定长顺序存储表示，0号单元存放串的长度
int next[MAXSTRLEN];            //KMP算法中用到的next数组

//1. 求模式串T的next函数值并存入数组next
void get_next(SString T,int next[ ])   
{   // 求模式串T的next函数值，并存入数组next
	int j=1,k=0;
	next[1]=0;
    while (j<T[0])
	{
		if (k==0 || T[k]==T[j]) 
		{
			++j; ++k; 
			if (T[j]!=T[k])  next[j]=k;
			else next[j]=next[k];
		}
		else k=next[k];
	}
}
//2. KMP匹配函数
int Index(SString S,SString T,int pos) 
{    // 利用模式串T的next函数求T在主串S中第pos个字符之后的位置的KMP算法
     // 其中T非空，1 pos  StrLength(s)
	int i=pos,j=1;
	while (i<=S[0]&&j<=T[0])
	{
		if (j==0||S[i]==T[j]) {++i;++j;}  // 继续比较后继字符
		else j=next[j];                // 模式串向右移动
	}
   if (j>T[0])  return (i-T[0]);           // 匹配成功
   else return 0;                       // 匹配失败
}

//3. 求串长
int lenth(SString str)    
{
	int i=1;
	while(str[i]) i++;
	return(i-1);
}
//4. 查找函数
void find(char name[],SString keys) //该函数是整个程序的重要部分，对于输入的每一个
{                                    //要查找的关键字，从存储客户信息的文件中逐行读取字符串查找
	SString text; //存放从客户信息文件读取的一行字符串      
	int i=1,j=0,k;   //i用于存放行号，j用于存放列号,k用于输出格式的控制
	int n=0;  //n记录出现次数
	FILE *fp;
	if (!(fp=(fopen(name,"r")))) //打开存储客户信息的文件
	{
		printf("Open file error!\n");
		exit(0);
	}
	keys[0]=lenth(keys);        //调用lenth函数求关键字的长度
    get_next(keys,next);        //调用get_next函数求模式串（关键字）每一个字符对应的next值
    printf("\n%s出现于：\n",&keys[1]);    //打印关键字
	while (!feof(fp))        //如果还没到客户信息文件末尾
	{
		k=0;		
		fgets(&text[1],MAXSTRLEN,fp);     //从客户信息文件中读取一行字符串，存入text串中
		text[0]=lenth(text);              //求读入的串的长度
		j=Index(text,keys,j+1);        //调用KMP算法，统计关键字在该行出现的位置，若匹配不成功则返回0
		if (j!=0)
		{ printf("\trow=%d,\tcol=%d",i,j); k++; n++;}   //若匹配成功则打印行号和列号
		while(j!=0)         //若该行找到了关键字，则继续寻找看是否还能匹配成功
		{
			j=Index(text,keys,j+1); //调用KMP算法从刚找到的列号后一字符起匹配
			if (j!=0)         
			{   n++;
				printf(",%d",j); } //若匹配成功，则打印列号
		}
		i++; //行号加1，在下一行中寻找
		if (k) printf("\n");  //输出格式控
	}
	printf("%s共出现%d次\n",&keys[1],n); 
}
//5. 主函数
int zifuchuanchazhao()
{
	char name[50];   //存储输入的客户信息路径字符串
	SString words[10];   //定义字符串数组，用于存储输入的关键字
	int n,i;
	printf("请输入已创建的客户信息文件的路径 (如D:\\message.txt):\n");
	scanf("%s",name);   //用户输入包含路径的文本文件名
	printf("请输入要查找的关键字n (n<10)：\n");
	scanf("%d",&n);  //用户输入要查找的关键字个数
	printf("请输入要查找的编号:\n");
	for (i=0;i<n;i++)
		scanf("%s",&words[i][1]); //用户一次性输入要查找的关键字，words[i][0]用于存放字符串的长度
	for (i=0;i<n;i++)
		find(name,words[i]);    //对于每一个关键字，调用find函数进行查找统计
	return 0; 
}




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	}while((yn=getchare())=='y' || yn=='Y');
	printf("\n");
	L->length=i-1;
	//RadixSort(L);
	//Arrange(L);
	return true;
}


// 11. 主函数 
int client_info_query()
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

void print_info()
{
    puts("1:) 银行系统");
    puts("2:) 用户信息查询系统");
    puts("3:) 贷款系统");
    puts("4:) VIP系统");
    puts("5:) 网点查询系统");
    puts("6:) 字符串查找系统");
    puts("7:) 湖北二师分行系统");
}

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
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
    getchar();
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
				 ch[k]=getchar();
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

void hubei()            //主函数
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
				  getchar();
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
			 getchar();
			 system("cls");
			 break;
		  }
	  case 3:
		  {   
			  system("cls");
	          printf("\n****************************业务查询界面*****************************\n\n");
              printl();
	          getchar();
	          system("cls");
              break;
	   
		  }
	  case 4:
		  {
			  system("cls");
	          printf("\n****************************排队查询界面*****************************\n\n");
              print2();
	          getchar();
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
				  cool[k]=getchar();
	              k++;
                  printf("*");
			  }
			  if(i==000 && cool[0]=='1' && cool[1]=='1' && cool[2]=='1' && cool[3]=='1')
			  {	
				  average=allsum/w;
		          printf("\n  至今已有 %d 位普通用户，%d 位vip用户成功办理业务!",w,vip1);
		          printf("\n  普通用户业务办理总共用时 %0.2f秒,平均用时 %0.2f秒\n",allsum,average);
			  }
			  getchar();
	          system("cls");
			  break;
		  }
		  return;
		  getchar();
		  system("cls");
	  case 6:
		  return;
		  getchar();
		  system("cls");
	  default: printf("     输入有误！请重新输入：\n");
		  getchar();
		  system("cls");
    }
  }
}


int main()
{
    int input;

    while (1) {
        print_info();
        printf("输入你的选择:");
        scanf("%d", &input);

        switch (input) {
            case 1:
                bank_queue();
                break;
            case 2:
                client_info_query();
                break;
            case 3:
                daikuan();
                break;
            case 4:
                vip_system();
                break;
            case 5:
                wangdianchaxun();
                break;
            case 6:
                zifuchuanchazhao();
                break;
            case 7:
                hubei();
                break;
        }
    }
}
