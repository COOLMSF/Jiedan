#include<stdio.h>//标准输入输出文件
#include<conio.h>//控制台输入输出文件
#include<stdlib.h>////标准库函数头文件
#include<ctype.h>
typedef struct _Student  //学生信息结构体 
{
	int no;       //学生学号
	char name[20];   //学生姓名
	char zhuanye[20];   //学生专业
	char sex[20]; //学生性别
	int age;     //学生年龄
	int phone;   //联系方式
	int yuwen;     //语文成绩 
	int shu;       //数学成绩 
	int ying;      //英语成绩 
}Student;
typedef struct _Node  //链表结点结构体 
{
	Student stu;//数据域
	struct _Node* pNext;//指针域
}Node;

Node* g_pHead=NULL;//头结点

void inputpeople();//录入学生的声明
void viewpeople();//浏览学生的声明
void delpeople();//删除学生的声明
void changepeople();//修改学生的声明
void searchpeople();//查找学生的声明
