#include<stdio.h>//��׼��������ļ�
#include<conio.h>//����̨��������ļ�
#include<stdlib.h>////��׼�⺯��ͷ�ļ�
#include<ctype.h>
typedef struct _Student  //ѧ����Ϣ�ṹ�� 
{
	int no;       //ѧ��ѧ��
	char name[20];   //ѧ������
	char zhuanye[20];   //ѧ��רҵ
	char sex[20]; //ѧ���Ա�
	int age;     //ѧ������
	int phone;   //��ϵ��ʽ
	int yuwen;     //���ĳɼ� 
	int shu;       //��ѧ�ɼ� 
	int ying;      //Ӣ��ɼ� 
}Student;
typedef struct _Node  //������ṹ�� 
{
	Student stu;//������
	struct _Node* pNext;//ָ����
}Node;

Node* g_pHead=NULL;//ͷ���

void inputpeople();//¼��ѧ��������
void viewpeople();//���ѧ��������
void delpeople();//ɾ��ѧ��������
void changepeople();//�޸�ѧ��������
void searchpeople();//����ѧ��������
