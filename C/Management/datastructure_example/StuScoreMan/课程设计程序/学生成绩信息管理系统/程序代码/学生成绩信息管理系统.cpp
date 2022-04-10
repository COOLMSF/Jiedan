#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
typedef struct{     //����ϵͳ�ڵ�����
	char num[10];	//ѧ�� 
	char name[20];  //����
	float score[3];	//���Ƴɼ� 
	float average;  //ƽ���ɼ� 
	float pass_rate;  //�ɼ������� 
}DataType;

typedef struct node{   //�ڵ����Ͷ��� 
	DataType data;     //�ڵ�������
	struct node *next; //�ڵ�ָ����
}ListNode;
typedef ListNode *LinkList;
LinkList head;
ListNode *p;

int menu_select();    //����˵��
LinkList CreateList(void);    //β�巨��������ϵͳ������ 
void InsertNode(LinkList head,ListNode *p);  //���뺯�� 
ListNode *ListFind(LinkList head);           //���Һ��� 
void DelNode(LinkList head);                 //ɾ������ 
void PrintList(LinkList head);               //������� 
ListNode *Sorting_order(LinkList head);      //������ 
void ChangeNode(LinkList head);              //�޸ĺ��� 
float average(LinkList head,int i);          //ƽ���ɼ� 
float pass_rate(LinkList head,int i);        //������ 
//������
int main ()
{
	for (;;){
	switch(menu_select())
	{
		case 1:
			printf("**************************************\n");
			printf("*        �� �� �� Ϣ �� �� ��        *\n");
			printf("**************************************\n");
			head=CreateList();
			break;
		case 2:
			printf("**************************************\n");
			printf("*        �� �� �� Ϣ �� �� ��        *\n");
			printf("**************************************\n");
			printf("��˳������ѧ�š����������ݽṹ�ɼ������簲ȫ�ɼ��Ͳ���ϵͳ�ɼ�\n");
			printf("**************************************\n");
			p=(ListNode *)malloc(sizeof(ListNode));      //�����½ڵ� 
			scanf("%s%s%f%f%f",p->data.num,p->data.name,&p->data.score[0],&p->data.score[1],&p->data.score[2]);
			InsertNode(head,p);
			break;
		case 3:
			printf("***************************************\n");
			printf("*        �� �� �� Ϣ �� �� ��        *\n");
			printf("***************************************\n");
			p=ListFind(head);
			if(p!=NULL){
			printf("ѧ��\t����\t���ݽṹ�ɼ�\t���簲ȫ�ɼ�\t����ϵͳ�ɼ�\n");
			printf("----------------------------------------------------------------\n");
			printf("%s\t%s\t%5.1f\t\t%5.1f\t\t%5.1f\n",p->data.num,p->data.name,p->data.score[0],p->data.score[1],p->data.score[2]);
			printf("----------------------------------------------------------------\n");
		}
			else
				printf("û�鵽Ҫ��ѯ����Ϣ��\n");
				break;
		case 4:
			printf("***************************************\n");
			printf("*        �� �� �� Ϣ �� ɾ ��         *\n");
			printf("***************************************\n");
			DelNode(head);     //ɾ���ڵ� 
			break;
		case 5:
			printf("***************************************\n");
			printf("*        �� �� �� Ϣ �� �� ��         *\n");
			printf("***************************************\n");
			ChangeNode(head);
			break;
		case 6:
			printf("***************************************\n");
			printf("*        �� �� �� Ϣ �� �� ��         *\n");
			printf("***************************************\n");	
			PrintList(Sorting_order(head));
			break;
		case 7:
			printf("***************************************\n");
			printf("*        �� �� �� Ϣ �� �� ��         *\n");
			printf("***************************************\n");	
			PrintList(head);
			break;
		case 8:
			printf("***************************************\n");
			printf("*        �� �� �� �� �� ƽ �� ��      *\n");
			printf("***************************************\n");	
			printf("���ݽṹ�ɼ���ƽ����:%8.3f\n",average(head,0));
			printf("���簲ȫ�ɼ���ƽ����:%8.3f\n",average(head,1));
			printf("����ϵͳ�ɼ���ƽ����:%8.3f\n",average(head,2));
			printf("---------------------------------------\n");
			break;
		case 9:
			printf("***************************************\n");
			printf("*        �� �� �� �� �� �� �� ��      *\n");
			printf("***************************************\n");	
			printf("���ݽṹ�ɼ��ļ�����:%6.2f%%\n",pass_rate(head,0));
			printf("���簲ȫ�ɼ��ļ�����:%6.2f%%\n",pass_rate(head,1));
			printf("����ϵͳ�ɼ��ļ�����:%6.2f%%\n",pass_rate(head,2));
			printf("---------------------------------------\n");
			break;
		case 0:
			printf("   �ǳ���л����ʹ�ã�лл!\n��������ߣ�������\n");
			//return;
		}
	}
}

//�˵� 
int menu_select()
{
	int sn;
	printf("ѧ���ɼ���Ϣ����ϵͳ\n");
	printf("=======================\n");
	printf("   1.�ɼ���Ϣ������\n");
	printf("   2.�ɼ���Ϣ�Ĳ���\n");
	printf("   3.�ɼ���Ϣ�Ĳ���\n");
	printf("   4.�ɼ���Ϣ��ɾ��\n");
	printf("   5.�ɼ���Ϣ���޸�\n");
	printf("   6.�ɼ���Ϣ������\n");
	printf("   7.�ɼ���Ϣ�����\n");
	printf("   8.�ɼ���Ϣ��ƽ����\n");
	printf("   9.�ɼ���Ϣ�ļ�����\n");
	printf("   0.�˳�����ϵͳ\n"); 
	printf("=======================\n");
	printf("    �� ѡ �� 0-9��"); 
    for(;;)
    {
		scanf("%d",&sn);
   	    if(sn<0||sn>9)
    		printf("\n\t�������,��ѡ0-9:  ");
  		else
 			 break;
 	}
 	return sn;
}

//��β�巨��������ϵͳ������
LinkList CreateList(void)      
{  //β�巨������ͷ�ڵ�Ĺ���ϵͳ�����㷨 
	LinkList head=(ListNode *)malloc(sizeof(ListNode));  //����ͷ�ڵ�
	ListNode *p,*rear;
	int flag='y';        //�Ƿ������־
	rear=head;           //βָ���ʼָ��ͷ�ڵ�
	while(flag=='y')
	{p=(ListNode *)malloc(sizeof(ListNode));  //�����½ڵ�
	  printf("��˳������ѧ�š����������ݽṹ�ɼ������簲ȫ�ɼ��Ͳ���ϵͳ�ɼ�\n");
	  printf("--------------------------------------------------------------\n");
	  scanf("%s%s%f%f%f",p->data.num,p->data.name,&p->data.score[0],&p->data.score[1],&p->data.score[2]);
	  rear->next=p;      //�½ڵ����ӵ�β�ڵ�֮��
	  rear=p;            //βָ��ָ���½ڵ�
	  printf("����������?(y/n):");
	  getchar();
	  scanf("%c",&flag);  //����һ����־����
	}
	rear->next=NULL;    //�ն˽ڵ�ָ�����ÿ�
	return head;       //��������ͷָ��
}

//����ϵͳ�Ĳ��뺯�� 
void InsertNode(LinkList head,ListNode *p)
{
	ListNode *p1,*p2;
	p1=head;
	p2=p1->next;
	while(p2!=NULL && strcmp(p2->data.num,p->data.num)<0)
	{
		p1=p2;        //p1ָ��շ��ʹ��Ľڵ�
		p2=p2->next;  //p2ָ������һ���ڵ�
	}
	p1->next=p;      //����p��ָ��Ľڵ�
	p->next=p2;      //���ӱ���ʣ�ಿ��
}

//����ϵͳ�Ĳ��Һ��� 
ListNode *ListFind(LinkList head)
{    //���������ϵĲ���
	ListNode *p;
  	char num[10];
  	char name[20];
  	int xz;
 	printf("=====================\n");
  	printf(" 1.��ѧ�Ų�ѯ  \n");
  	printf(" 2.��������ѯ  \n");
  	printf("=====================\n");
 	printf("  ��ѡ��: ");
  	p=head->next;                    //�ٶ�ѧ���ɼ����ͷ�ڵ�
  	scanf("%d",&xz);
  	if(xz==1){                        //��ѧ�Ų��� 
  		printf("������Ҫ�����ߵ�ѧ��: ");
  		scanf("%s",&num);
  		getchar();
  		while(p&&strcmp(p->data.num,num)<0)
  			p=p->next;
  		if(p==NULL||strcmp(p->data.num,num)>0)
  			p=NULL;
  	}
	else if(xz==2)                   //���������� 
	{ 
		printf("������Ҫ�����ߵ�����: ");
  		scanf("%s",&name);
  		while(p&&strcmp(p->data.name,name)!=0)
    		p=p->next;
    }
    return p;
}

//����ϵͳ��ɾ������ 
void DelNode(LinkList head)
{
	char jx;
    ListNode *p,*q;
    p=ListFind(head);      //���ú��� 
    if(p==NULL)
    {
		printf("û�в鵽Ҫɾ������Ϣ!\n");
    	return;
    }
    printf("���Ҫɾ���ý����?(y/n): ");    //ѡ���Ƿ�ɾ�� 
    scanf("%c",&jx);
    if(jx=='y'||jx=='Y') 
    {
		q=head;
	    while(q!=NULL&&q->next!=p)
	    	q=q->next;
	    if(q!=NULL)
	    	q->next=p->next;              //ɾ���ڵ� 
	    	free(p);                     //�ͷű�ɾ���Ľڵ�ռ� 
	    printf("��ѧ������Ϣ�ѱ�ɾ����\n");
    }
}

//����ϵͳ����Ϣ���޸ĺ��� 
void ChangeNode(LinkList head)
{
	ListNode *p;
	p=ListFind(head);      //���ò��Һ������ҵ�Ҫ�޸ĵ���Ϣ�Ľڵ� 
	if(p){                 //�޸ĸýڵ� 
		printf("ѧ��\t����\t���ݽṹ\t���簲ȫ\t����ϵͳ\n");
		printf("---------------------------------------------------------\n");
		printf("%s\t%s\t%5.1f\t\t%5.1f\t\t%5.1f\n",p->data.num,p->data.name,p->data.score[0],p->data.score[1],p->data.score[2]);
		printf("---------------------------------------------------------\n");
		printf("�����������ѧ�������ݽṹ�ɼ������簲ȫ�ɼ��Ͳ���ϵͳ�ɼ�:\n");
		scanf("%f%f%f",&p->data.score[0],&p->data.score[1],&p->data.score[2]);
		printf("��ѧ������Ϣ���޸ĳɹ���\n");
	}
	else         //û�ҵ��ýڵ� 
		printf("û�в鵽Ҫ���ҵ���Ϣ��\n");
}

//����ϵͳ�������� 
ListNode *Sorting_order(LinkList head){
	ListNode *p,*q;
	int xz;
	printf("================\n");
	printf("1.��ѧ������ \n");
	printf("2.���������� \n");
	printf("================\n");
	printf("   ��ѡ��");
	scanf("%d",&xz);
	if(xz==1){           //��ѧ������ 
		p=head->next->next;
		head->next->next=NULL;
		while(p){
			q=p->next;
			InsertNode(head,p);
			p=q;
		}
		return head;
	}
	if(xz==2){           //���������� 
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

//�������ϵͳ�ĸ������� 
void PrintList(LinkList head)
{
	p=head->next;
    printf("ѧ��\t����\t���ݽṹ\t���簲ȫ\t����ϵͳ\n");
    printf("---------------------------------------------------------\n");
    while(p!=NULL)
    { printf("%s\t%s\t%5.1f\t\t%5.1f\t\t%5.1f\n",p->data.num,p->data.name,p->data.score[0],p->data.score[1],p->data.score[2]);
      printf("-------------------------------------------------------\n");
      p=p->next;
    }
}

//����ϵͳ����ƽ���ɼ��ĺ��� 
float average(LinkList head,int i){
	float sum=0.0;    //�ܳɼ� 
	int j=0;          //�ɼ����� 
	ListNode *p;
	p=head->next;
	while(p){
		sum=sum+p->data.score[i];
		p=p->next;
		j++;
	}
	return(sum/j);   //��ƽ���ɼ� 
}

//���Ƴɼ��ļ����ʺ��� 
float pass_rate(LinkList head,int i){    
	double sum=0.0,pass=0; 
	int PA=60;       //���60�֣�����60����ͨ�� 
	ListNode *p=head->next;
	while(p){
		sum++;
		if(p->data.score[i]>=PA)
			pass++;
		p=p->next;	
	}
	return(pass/sum*100);   //����ſγɼ�ͨ���� 
}
