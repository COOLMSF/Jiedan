#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
typedef struct{     //管理系统节点类型
	char num[10];	//学号 
	char name[20];  //姓名
	float score[3];	//各科成绩 
	float average;  //平均成绩 
	float pass_rate;  //成绩及格率 
}DataType;

typedef struct node{   //节点类型定义 
	DataType data;     //节点数据域
	struct node *next; //节点指针域
}ListNode;
typedef ListNode *LinkList;
LinkList head;
ListNode *p;

int menu_select();    //函数说明
LinkList CreateList(void);    //尾插法建立管理系统链表函数 
void InsertNode(LinkList head,ListNode *p);  //插入函数 
ListNode *ListFind(LinkList head);           //查找函数 
void DelNode(LinkList head);                 //删除函数 
void PrintList(LinkList head);               //输出函数 
ListNode *Sorting_order(LinkList head);      //排序函数 
void ChangeNode(LinkList head);              //修改函数 
float average(LinkList head,int i);          //平均成绩 
float pass_rate(LinkList head,int i);        //及格率 
//主函数
int main ()
{
	for (;;){
	switch(menu_select())
	{
		case 1:
			printf("**************************************\n");
			printf("*        成 绩 信 息 的 输 入        *\n");
			printf("**************************************\n");
			head=CreateList();
			break;
		case 2:
			printf("**************************************\n");
			printf("*        成 绩 信 息 的 插 入        *\n");
			printf("**************************************\n");
			printf("请顺序输入学号、姓名、数据结构成绩、网络安全成绩和操作系统成绩\n");
			printf("**************************************\n");
			p=(ListNode *)malloc(sizeof(ListNode));      //申请新节点 
			scanf("%s%s%f%f%f",p->data.num,p->data.name,&p->data.score[0],&p->data.score[1],&p->data.score[2]);
			InsertNode(head,p);
			break;
		case 3:
			printf("***************************************\n");
			printf("*        成 绩 信 息 的 查 找        *\n");
			printf("***************************************\n");
			p=ListFind(head);
			if(p!=NULL){
			printf("学号\t姓名\t数据结构成绩\t网络安全成绩\t操作系统成绩\n");
			printf("----------------------------------------------------------------\n");
			printf("%s\t%s\t%5.1f\t\t%5.1f\t\t%5.1f\n",p->data.num,p->data.name,p->data.score[0],p->data.score[1],p->data.score[2]);
			printf("----------------------------------------------------------------\n");
		}
			else
				printf("没查到要查询的信息！\n");
				break;
		case 4:
			printf("***************************************\n");
			printf("*        成 绩 信 息 的 删 除         *\n");
			printf("***************************************\n");
			DelNode(head);     //删除节点 
			break;
		case 5:
			printf("***************************************\n");
			printf("*        成 绩 信 息 的 修 改         *\n");
			printf("***************************************\n");
			ChangeNode(head);
			break;
		case 6:
			printf("***************************************\n");
			printf("*        成 绩 信 息 的 排 序         *\n");
			printf("***************************************\n");	
			PrintList(Sorting_order(head));
			break;
		case 7:
			printf("***************************************\n");
			printf("*        成 绩 信 息 的 输 出         *\n");
			printf("***************************************\n");	
			PrintList(head);
			break;
		case 8:
			printf("***************************************\n");
			printf("*        各 科 成 绩 的 平 均 分      *\n");
			printf("***************************************\n");	
			printf("数据结构成绩的平均分:%8.3f\n",average(head,0));
			printf("网络安全成绩的平均分:%8.3f\n",average(head,1));
			printf("操作系统成绩的平均分:%8.3f\n",average(head,2));
			printf("---------------------------------------\n");
			break;
		case 9:
			printf("***************************************\n");
			printf("*        各 科 成 绩 的 及 格 率      *\n");
			printf("***************************************\n");	
			printf("数据结构成绩的及格率:%6.2f%%\n",pass_rate(head,0));
			printf("网络安全成绩的及格率:%6.2f%%\n",pass_rate(head,1));
			printf("操作系统成绩的及格率:%6.2f%%\n",pass_rate(head,2));
			printf("---------------------------------------\n");
			break;
		case 0:
			printf("   非常感谢您的使用，谢谢!\n程序设计者：赵宇湘\n");
			//return;
		}
	}
}

//菜单 
int menu_select()
{
	int sn;
	printf("学生成绩信息管理系统\n");
	printf("=======================\n");
	printf("   1.成绩信息的输入\n");
	printf("   2.成绩信息的插入\n");
	printf("   3.成绩信息的查找\n");
	printf("   4.成绩信息的删除\n");
	printf("   5.成绩信息的修改\n");
	printf("   6.成绩信息的排序\n");
	printf("   7.成绩信息的输出\n");
	printf("   8.成绩信息的平均分\n");
	printf("   9.成绩信息的及格率\n");
	printf("   0.退出管理系统\n"); 
	printf("=======================\n");
	printf("    请 选 择 0-9："); 
    for(;;)
    {
		scanf("%d",&sn);
   	    if(sn<0||sn>9)
    		printf("\n\t输入错误,重选0-9:  ");
  		else
 			 break;
 	}
 	return sn;
}

//用尾插法建立管理系统链表函数
LinkList CreateList(void)      
{  //尾插法建立带头节点的管理系统链表算法 
	LinkList head=(ListNode *)malloc(sizeof(ListNode));  //申请头节点
	ListNode *p,*rear;
	int flag='y';        //是否结束标志
	rear=head;           //尾指针初始指向头节点
	while(flag=='y')
	{p=(ListNode *)malloc(sizeof(ListNode));  //申请新节点
	  printf("请顺序输入学号、姓名、数据结构成绩、网络安全成绩和操作系统成绩\n");
	  printf("--------------------------------------------------------------\n");
	  scanf("%s%s%f%f%f",p->data.num,p->data.name,&p->data.score[0],&p->data.score[1],&p->data.score[2]);
	  rear->next=p;      //新节点连接到尾节点之后
	  rear=p;            //尾指针指向新节点
	  printf("继续输入吗?(y/n):");
	  getchar();
	  scanf("%c",&flag);  //读入一个标志数据
	}
	rear->next=NULL;    //终端节点指针域置空
	return head;       //返回链表头指针
}

//管理系统的插入函数 
void InsertNode(LinkList head,ListNode *p)
{
	ListNode *p1,*p2;
	p1=head;
	p2=p1->next;
	while(p2!=NULL && strcmp(p2->data.num,p->data.num)<0)
	{
		p1=p2;        //p1指向刚访问过的节点
		p2=p2->next;  //p2指向表的下一个节点
	}
	p1->next=p;      //插入p所指向的节点
	p->next=p2;      //连接表中剩余部分
}

//管理系统的查找函数 
ListNode *ListFind(LinkList head)
{    //有序链表上的查找
	ListNode *p;
  	char num[10];
  	char name[20];
  	int xz;
 	printf("=====================\n");
  	printf(" 1.按学号查询  \n");
  	printf(" 2.按姓名查询  \n");
  	printf("=====================\n");
 	printf("  请选择: ");
  	p=head->next;                    //假定学生成绩表带头节点
  	scanf("%d",&xz);
  	if(xz==1){                        //按学号查找 
  		printf("请输入要查找者的学号: ");
  		scanf("%s",&num);
  		getchar();
  		while(p&&strcmp(p->data.num,num)<0)
  			p=p->next;
  		if(p==NULL||strcmp(p->data.num,num)>0)
  			p=NULL;
  	}
	else if(xz==2)                   //按姓名查找 
	{ 
		printf("请输入要查找者的姓名: ");
  		scanf("%s",&name);
  		while(p&&strcmp(p->data.name,name)!=0)
    		p=p->next;
    }
    return p;
}

//管理系统的删除函数 
void DelNode(LinkList head)
{
	char jx;
    ListNode *p,*q;
    p=ListFind(head);      //调用函数 
    if(p==NULL)
    {
		printf("没有查到要删除的信息!\n");
    	return;
    }
    printf("真的要删除该结点吗?(y/n): ");    //选择是否删除 
    scanf("%c",&jx);
    if(jx=='y'||jx=='Y') 
    {
		q=head;
	    while(q!=NULL&&q->next!=p)
	    	q=q->next;
	    if(q!=NULL)
	    	q->next=p->next;              //删除节点 
	    	free(p);                     //释放被删除的节点空间 
	    printf("该学生的信息已被删除！\n");
    }
}

//管理系统的信息的修改函数 
void ChangeNode(LinkList head)
{
	ListNode *p;
	p=ListFind(head);      //调用查找函数，找到要修改的信息的节点 
	if(p){                 //修改该节点 
		printf("学号\t姓名\t数据结构\t网络安全\t操作系统\n");
		printf("---------------------------------------------------------\n");
		printf("%s\t%s\t%5.1f\t\t%5.1f\t\t%5.1f\n",p->data.num,p->data.name,p->data.score[0],p->data.score[1],p->data.score[2]);
		printf("---------------------------------------------------------\n");
		printf("请依次输入该学生的数据结构成绩、网络安全成绩和操作系统成绩:\n");
		scanf("%f%f%f",&p->data.score[0],&p->data.score[1],&p->data.score[2]);
		printf("该学生的信息已修改成功！\n");
	}
	else         //没找到该节点 
		printf("没有查到要查找的信息！\n");
}

//管理系统的排序函数 
ListNode *Sorting_order(LinkList head){
	ListNode *p,*q;
	int xz;
	printf("================\n");
	printf("1.按学号排序 \n");
	printf("2.按姓名排序 \n");
	printf("================\n");
	printf("   请选择：");
	scanf("%d",&xz);
	if(xz==1){           //按学号排序 
		p=head->next->next;
		head->next->next=NULL;
		while(p){
			q=p->next;
			InsertNode(head,p);
			p=q;
		}
		return head;
	}
	if(xz==2){           //按姓名排序 
		p=head->next->next;
		head->next->next=NULL;
		while(p){
			ListNode *p1,*p2;
			p1=head;
			p2=p1->next;
			q=p->next;
			while(p2 && strcmp(p2->data.name,p->data.name)<0)
			{
				p1=p2;
				p2=p2->next;
			}
			p1->next=p;
			p->next=p2;
			p=q;
		}
		return head;
	}
}

//输出管理系统的各个数据 
void PrintList(LinkList head)
{
	p=head->next;
    printf("学号\t姓名\t数据结构\t网络安全\t操作系统\n");
    printf("---------------------------------------------------------\n");
    while(p!=NULL)
    { printf("%s\t%s\t%5.1f\t\t%5.1f\t\t%5.1f\n",p->data.num,p->data.name,p->data.score[0],p->data.score[1],p->data.score[2]);
      printf("-------------------------------------------------------\n");
      p=p->next;
    }
}

//管理系统的求平均成绩的函数 
float average(LinkList head,int i){
	float sum=0.0;    //总成绩 
	int j=0;          //成绩个数 
	ListNode *p;
	p=head->next;
	while(p){
		sum=sum+p->data.score[i];
		p=p->next;
		j++;
	}
	return(sum/j);   //求平均成绩 
}

//各科成绩的及格率函数 
float pass_rate(LinkList head,int i){    
	double sum=0.0,pass=0; 
	int PA=60;       //最低60分，超过60分算通过 
	ListNode *p=head->next;
	while(p){
		sum++;
		if(p->data.score[i]>=PA)
			pass++;
		p=p->next;	
	}
	return(pass/sum*100);   //求该门课成绩通过率 
}
