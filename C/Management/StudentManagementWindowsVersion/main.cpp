#include"Student.h"
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)
int main()//�������
{ 
	
	while(1)//��ѭ��
	{
		int a = 0;
		printf("***********************************\n");
	    printf("*     ��ӭ����ѧ������ϵͳ        *\n");
	    printf("***********************************\n");
		printf("***********************************\n");
	    printf("*        ��ѡ�����ֽ��в���       *\n");
		printf("*---------------------------------*\n");
	    printf("*        1.¼��ѧ����Ϣ           *\n");
        printf("*---------------------------------*\n");
	    printf("*        2.���ѧ����Ϣ           *\n");
		printf("*---------------------------------*\n");
	    printf("*        3.ɾ��ѧ��               *\n");
		printf("*---------------------------------*\n");
	    printf("*        4.�޸�ѧ��               *\n");
		printf("*---------------------------------*\n");
	    printf("*        5.����ѧ����Ϣ           *\n");
	    printf("*---------------------------------*\n");
		printf("*        6.�˳�                   *\n");
	    printf("*---------------------------------*\n");
	    printf("*       ���������ѡ��            *\n");
		printf("***********************************\n");
		scanf("%d",&a);//��ȡ����Ĺ������
		printf("\n");
	switch(a)//�������
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
		printf("��ӭ�´�ʹ�ã��ټ���\n");
		return 0;//break�����������ѭ����ʹ��return������������
		break;
		}
	printf("\n");//�˵�ÿ��ѭ��֮����ò�Ҫ����
	}
	return 0;
}

int IncludeChinese(char *str)//����0�������ģ�����1��������
{
   char c;
   while(1)
   {
       c=*str++;
       if (c==0) break;  //������ַ���β��˵�����ַ���û�������ַ�
       if (c&0x80)        //����ַ���λΪ1����һ�ַ���λҲ��1���������ַ�
               if ((*str & 0x80)) return 1;
   }
   return 0;
}

int onlyChinese(char *str)//����0�������ģ�����1��������
{
   char c;
   int n = 0;
   while(1)
   {
       c=*str++;
       if (c==0) break;  //������ַ���β��˵�����ַ���û�������ַ�
       if ((!(c&0x80)) || (!(*str & 0x80))) 
	   		return 0;
	   	n++;
	   	if (n == strlen(str))
	   		return 1;
   }
   return 1;
}
//¼��ѧ����ʵ��
void inputpeople()
{
	char m;
	while (1)
	{
		//����һ���½��
		Node* pNewNode = (Node*)malloc(sizeof(Node));//����һ��Node���ʹ�С���ڴ�ռ䣬����������Node*�͵ı���pNewNode
		pNewNode->pNext = NULL;//pNewNode�½�����һ�����ǿ�
		//ͷ�巨
		if (g_pHead == NULL)//ʲô��û��
		{
			g_pHead = pNewNode;
		}
		else				
		{
			pNewNode->pNext = g_pHead;//��pNewNode���뵽ͷ���ǰ
			g_pHead = pNewNode;//��������ͷ�������pNewNode
		}
		
		int idTemp;
		printf("������ѧ��ѧ��:\n");
		scanf("%d", &idTemp);
		
		// ����������Ѱ���Ƿ����ظ���id
		Node *p = g_pHead;
		while (p) {
			if (p->stu.no == idTemp) {
				puts("ѧ���Ѵ���");
				exit(-1);
			}
			p = p->pNext;
		}
		
		// scanf("%d", &pNewNode->stu.no);//no����������Ҫȡ��ַ��
		printf("������ѧ������:\n");
		char buf[1024];
		scanf("%s", buf);
		if (!onlyChinese(buf)) {
			puts("������������������ַ�");
			exit(-1);
		}
		strcpy(pNewNode->stu.name, buf);
		// scanf("%s", pNewNode->stu.name);//name[]�������������ü�ȡ��ַ��
		printf("������ѧ��רҵ:\n");
		scanf("%s", pNewNode->stu.zhuanye);
		printf("������ѧ���Ա�:\n");
		
		char sexTemp[1024];
		scanf("%s", sexTemp);
		if (!(strstr(sexTemp, "��")) || !(strstr(sexTemp, "Ů"))) {
			puts("�Ա��������");
			exit(-1);
		}
		strcpy(pNewNode->stu.sex, sexTemp);
		// scanf("%s", pNewNode->stu.sex);
		
		int ageTemp;
		printf("������ѧ������:\n");
		scanf("%d", &ageTemp);
		if (ageTemp <= 0 || ageTemp >= 100) {
			puts("���䳬����Χ");
			exit(-1); 
		}
		pNewNode->stu.age = ageTemp;
		
		// scanf("%d", &pNewNode->stu.age);
		printf("������ѧ����ϵ��ʽ:\n");
		scanf("%d", &pNewNode->stu.phone);
		printf("������ѧ�����ĳɼ�:\n");
		scanf("%d", &pNewNode->stu.yuwen);
		printf("������ѧ����ѧ�ɼ�:\n");
		scanf("%d", &pNewNode->stu.shu);
		printf("������ѧ��Ӣ��ɼ�:\n");
		scanf("%d", &pNewNode->stu.ying);
		printf("�Ƿ�Ҫ�������ѧ����(y or n)\n");
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
	printf("*                  ��ӭ����ѧ������ϵͳ                     *\n");
	printf("*************************************************************\n");
	printf("*\tѧ��\t*\t����\t*\tרҵ\t*\t�Ա�\t*\t����\t*\t��ϵ��ʽ\t*\t����\t*\t��ѧ\t*\tӢ��*\n");
	//��������
	p = g_pHead;//��÷���ִ�д���֮ǰ���壬�������ױ������
	while (p != NULL)
	{
		printf("*\t%d\t*\t%s\t*\t%s\t*\t%s\t*\t%d\t*\t%d\t*\t%d\t*\t%d\t*\t%d*\n", p->stu.no, p->stu.name, p->stu.zhuanye,p->stu.sex,p->stu.age,p->stu.phone,p->stu.yuwen, p->stu.shu, p->stu.ying);//���ýṹ���Ա
		p = p->pNext;
	}
	printf("***********************************\n");
	system("pause");
}

void delpeople()
{
	char m;
	while(1){
  Node*p=g_pHead;//��ֹ�ı�ͷ����ָ��
  Node*p1;//����p1
  Node*p2;//����p2
  int noo;
  printf("������Ҫɾ����ѧ��:");
  scanf("%d",&noo);
  if(g_pHead->stu.no==noo)//�ж��ǲ���ͷ���
  {
	  p1=g_pHead;
	  g_pHead=g_pHead->pNext;//ͷ���ɾ�ˣ���һ�������ͷ
	  free(p1);
	  return;
  }
  while(p->pNext!=NULL)
  {
	if (p->pNext->stu.no==noo)
	{
		p2=p->pNext;
		p->pNext=p->pNext->pNext;//�ѶϵĽ�����½�����
		free(p2);
		return ;
  }
	p=p->pNext;//��������

	if(p->pNext==NULL)//��β�����
	{
		break;
	}
  }
  if(p->pNext==NULL)//�Ѿ�������whlieѭ��
  {
	printf("û�и�ѧ��");
  }
  printf("�Ƿ�Ҫ����ɾ��ѧ����(y or n)\n");
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
	printf("������Ҫ����ѧ����ѧ��:");
	scanf("%d",&nooo);
	while(p!=NULL)
	{
		if(p->stu.no==nooo)
		{
			printf("ѧ��:%d",p->stu.no);
			printf("����:%s",p->stu.name);
			printf("����:%s",p->stu.zhuanye);
			printf("����:%s",p->stu.sex);
			printf("����:%d",p->stu.age);
			printf("����:%d",p->stu.phone);
			printf("����:%d",p->stu.yuwen);
			printf("��ѧ:%d",p->stu.shu);
			printf("Ӣ��:%d",p->stu.ying);
			break;
		}
		p=p->pNext;
	}
	if(p==NULL)
	{
		printf("û���ҵ���ѧ��\n");
	}
	printf("�Ƿ�Ҫ��������ѧ����(y or n)\n");
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
		printf("������Ҫ�ı��ѧ��ѧ��:");
		scanf("%d",&noooo);
		while(p!=NULL)
		{
			if(p->stu.no==noooo)
			{
				printf("������Ҫ�޸ĵ�ѧ��������:\n");
				scanf("%s",p->stu.name);
				printf("������Ҫ�޸ĵ�ѧ����ѧ��:\n");
				scanf("%s",&p->stu.no);
				printf("������Ҫ�޸ĵ�ѧ����רҵ:\n");
				scanf("%s",p->stu.zhuanye);
				printf("������Ҫ�޸ĵ�ѧ�����Ա�:\n");
				scanf("%s",p->stu.age);
				printf("������Ҫ�޸ĵ�ѧ��������:\n");
				scanf("%d",&p->stu.no);
				printf("������Ҫ�޸ĵ�ѧ������ϵ��ʽ:\n");
				scanf("%s",&p->stu.phone);
				printf("������Ҫ�޸ĵ�ѧ��������:\n");
				scanf("%s",&p->stu.yuwen);
				printf("������Ҫ�޸ĵ�ѧ������ѧ:\n");
				scanf("%s",&p->stu.shu);
				printf("������Ҫ�޸ĵ�ѧ����Ӣ��:\n");
				scanf("%s",&p->stu.ying);
				printf("�޸ĳɹ�\n");
				break;

			}
			p=p->pNext;
		}
		if(p==NULL)
		{
			printf("û���ҵ���ѧ���ĳɼ�\n");
		}
		printf("�Ƿ�Ҫ��������ѧ����(y or n)\n");
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
