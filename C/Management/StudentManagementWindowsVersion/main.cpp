#include"Student.h"
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)
int main()//程序入口
{ 
	
	while(1)//死循环
	{
		int a = 0;
		printf("***********************************\n");
	    printf("*     欢迎进入学生管理系统        *\n");
	    printf("***********************************\n");
		printf("***********************************\n");
	    printf("*        请选择数字进行操作       *\n");
		printf("*---------------------------------*\n");
	    printf("*        1.录入学生信息           *\n");
        printf("*---------------------------------*\n");
	    printf("*        2.浏览学生信息           *\n");
		printf("*---------------------------------*\n");
	    printf("*        3.删除学生               *\n");
		printf("*---------------------------------*\n");
	    printf("*        4.修改学生               *\n");
		printf("*---------------------------------*\n");
	    printf("*        5.查找学生信息           *\n");
	    printf("*---------------------------------*\n");
		printf("*        6.退出                   *\n");
	    printf("*---------------------------------*\n");
	    printf("*       请输入你的选择            *\n");
		printf("***********************************\n");
		scanf("%d",&a);//获取输入的功能序号
		printf("\n");
	switch(a)//分流语句
		{
		case 1:
			inputpeople();
			break;
		case 2:
			viewpeople();
			break;
		case 3:
			delpeople();
			break;
		case 4:
			changepeople();
			break;
		case 5:
			searchpeople();
			break;
		case 6:
		printf("欢迎下次使用，再见！\n");
		return 0;//break不能跳出这个循环，使用return结束函数更好
		break;
		}
	printf("\n");//菜单每次循环之后最好不要相连
	}
	return 0;
}

int IncludeChinese(char *str)//返回0：无中文，返回1：有中文
{
   char c;
   while(1)
   {
       c=*str++;
       if (c==0) break;  //如果到字符串尾则说明该字符串没有中文字符
       if (c&0x80)        //如果字符高位为1且下一字符高位也是1则有中文字符
               if ((*str & 0x80)) return 1;
   }
   return 0;
}

int onlyChinese(char *str)//返回0：无中文，返回1：有中文
{
   char c;
   int n = 0;
   while(1)
   {
       c=*str++;
       if (c==0) break;  //如果到字符串尾则说明该字符串没有中文字符
       if ((!(c&0x80)) || (!(*str & 0x80))) 
	   		return 0;
	   	n++;
	   	if (n == strlen(str))
	   		return 1;
   }
   return 1;
}
//录入学生的实现
void inputpeople()
{
	char m;
	while (1)
	{
		//创建一个新结点
		Node* pNewNode = (Node*)malloc(sizeof(Node));//分配一个Node类型大小的内存空间，并把它赋给Node*型的变量pNewNode
		pNewNode->pNext = NULL;//pNewNode新结点的下一个还是空
		//头插法
		if (g_pHead == NULL)//什么都没有
		{
			g_pHead = pNewNode;
		}
		else				
		{
			pNewNode->pNext = g_pHead;//把pNewNode插入到头结点前
			g_pHead = pNewNode;//所以现在头结点变成了pNewNode
		}
		
		int idTemp;
		printf("请输入学生学号:\n");
		scanf("%d", &idTemp);
		
		// 在链表里面寻找是否有重复的id
		Node *p = g_pHead;
		while (p) {
			if (p->stu.no == idTemp) {
				puts("学号已存在");
				exit(-1);
			}
			p = p->pNext;
		}
		
		// scanf("%d", &pNewNode->stu.no);//no是整数，需要取地址符
		printf("请输入学生姓名:\n");
		char buf[1024];
		scanf("%s", buf);
		if (!onlyChinese(buf)) {
			puts("不能输入中文以外的字符");
			exit(-1);
		}
		strcpy(pNewNode->stu.name, buf);
		// scanf("%s", pNewNode->stu.name);//name[]是数组名，不用加取地址符
		printf("请输入学生专业:\n");
		scanf("%s", pNewNode->stu.zhuanye);
		printf("请输入学生性别:\n");
		
		char sexTemp[1024];
		scanf("%s", sexTemp);
		if (!(strstr(sexTemp, "男")) || !(strstr(sexTemp, "女"))) {
			puts("性别输入错误");
			exit(-1);
		}
		strcpy(pNewNode->stu.sex, sexTemp);
		// scanf("%s", pNewNode->stu.sex);
		
		int ageTemp;
		printf("请输入学生年龄:\n");
		scanf("%d", &ageTemp);
		if (ageTemp <= 0 || ageTemp >= 100) {
			puts("年龄超过范围");
			exit(-1); 
		}
		pNewNode->stu.age = ageTemp;
		
		// scanf("%d", &pNewNode->stu.age);
		printf("请输入学生联系方式:\n");
		scanf("%d", &pNewNode->stu.phone);
		printf("请输入学生语文成绩:\n");
		scanf("%d", &pNewNode->stu.yuwen);
		printf("请输入学生数学成绩:\n");
		scanf("%d", &pNewNode->stu.shu);
		printf("请输入学生英语成绩:\n");
		scanf("%d", &pNewNode->stu.ying);
		printf("是否要继续添加学生？(y or n)\n");
		m=getchar();
		while(m!='y'&&m!='n')
		{
			m=getchar();
		}
		if(m=='y')
		{

			continue;
		}
		else
			break;
	}
	viewpeople();
 }


void viewpeople()
{
	Node* p;
  printf("***************************************************************\n");
	printf("*                  欢迎进入学生管理系统                     *\n");
	printf("*************************************************************\n");
	printf("*\t学号\t*\t姓名\t*\t专业\t*\t性别\t*\t年龄\t*\t联系方式\t*\t语文\t*\t数学\t*\t英语*\n");
	//遍历链表
	p = g_pHead;//最好放在执行代码之前定义，否则容易编译出错
	while (p != NULL)
	{
		printf("*\t%d\t*\t%s\t*\t%s\t*\t%s\t*\t%d\t*\t%d\t*\t%d\t*\t%d\t*\t%d*\n", p->stu.no, p->stu.name, p->stu.zhuanye,p->stu.sex,p->stu.age,p->stu.phone,p->stu.yuwen, p->stu.shu, p->stu.ying);//引用结构体成员
		p = p->pNext;
	}
	printf("***********************************\n");
	system("pause");
}

void delpeople()
{
	char m;
	while(1){
  Node*p=g_pHead;//防止改变头结点的指针
  Node*p1;//备份p1
  Node*p2;//备份p2
  int noo;
  printf("请输入要删除的学号:");
  scanf("%d",&noo);
  if(g_pHead->stu.no==noo)//判断是不是头结点
  {
	  p1=g_pHead;
	  g_pHead=g_pHead->pNext;//头结点删了，下一个结点做头
	  free(p1);
	  return;
  }
  while(p->pNext!=NULL)
  {
	if (p->pNext->stu.no==noo)
	{
		p2=p->pNext;
		p->pNext=p->pNext->pNext;//把断的结点重新接起来
		free(p2);
		return ;
  }
	p=p->pNext;//继续遍历

	if(p->pNext==NULL)//到尾结点了
	{
		break;
	}
  }
  if(p->pNext==NULL)//已经跳出了whlie循环
  {
	printf("没有该学号");
  }
  printf("是否要继续删除学生？(y or n)\n");
  m=getchar();
		while(m!='y'&&m!='n')
		{
			m=getchar();
		}
		if(m=='y')
		{
			continue;
		}
		else
			break;
}
	viewpeople();
}

void searchpeople()
{
	char m;
	while(1){
	Node*p=g_pHead;
	int nooo;
	printf("请输入要查找学生的学号:");
	scanf("%d",&nooo);
	while(p!=NULL)
	{
		if(p->stu.no==nooo)
		{
			printf("学号:%d",p->stu.no);
			printf("姓名:%s",p->stu.name);
			printf("姓名:%s",p->stu.zhuanye);
			printf("姓名:%s",p->stu.sex);
			printf("姓名:%d",p->stu.age);
			printf("姓名:%d",p->stu.phone);
			printf("语文:%d",p->stu.yuwen);
			printf("数学:%d",p->stu.shu);
			printf("英语:%d",p->stu.ying);
			break;
		}
		p=p->pNext;
	}
	if(p==NULL)
	{
		printf("没有找到该学号\n");
	}
	printf("是否要继续查找学生？(y or n)\n");
		m=getchar();
		while(m!='y'&&m!='n')
		{
			m=getchar();
		}
		if(m=='y')
		{

			continue;
		}
		else
			break;
	}
}
void changepeople()
{
	
	char m;
	viewpeople();
	while(1){
		Node*p=g_pHead;
		int noooo;
		printf("请输入要改变的学生学号:");
		scanf("%d",&noooo);
		while(p!=NULL)
		{
			if(p->stu.no==noooo)
			{
				printf("请输入要修改的学生的姓名:\n");
				scanf("%s",p->stu.name);
				printf("请输入要修改的学生的学号:\n");
				scanf("%s",&p->stu.no);
				printf("请输入要修改的学生的专业:\n");
				scanf("%s",p->stu.zhuanye);
				printf("请输入要修改的学生的性别:\n");
				scanf("%s",p->stu.age);
				printf("请输入要修改的学生的年龄:\n");
				scanf("%d",&p->stu.no);
				printf("请输入要修改的学生的联系方式:\n");
				scanf("%s",&p->stu.phone);
				printf("请输入要修改的学生的语文:\n");
				scanf("%s",&p->stu.yuwen);
				printf("请输入要修改的学生的数学:\n");
				scanf("%s",&p->stu.shu);
				printf("请输入要修改的学生的英语:\n");
				scanf("%s",&p->stu.ying);
				printf("修改成功\n");
				break;

			}
			p=p->pNext;
		}
		if(p==NULL)
		{
			printf("没有找到该学生的成绩\n");
		}
		printf("是否要继续查找学生？(y or n)\n");
		m=getchar();
		while(m!='y'&&m!='n')
		{
			m=getchar();
		}
		if(m=='y')
		{
			continue;
		}
		else
			break;
	}
	viewpeople();
}
