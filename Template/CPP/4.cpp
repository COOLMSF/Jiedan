

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
//�궨��
#define MaxSpace 100
#define keylen 6
#define RADIX_n 10
#define RADIX_c 26
#define SHOW_MSG_ERROR "\n�������ݴ��󣬳�����ִֹ�У�\n" 
#define true 1
#define false 0
typedef char KeyType;
typedef struct 
{//�ṹ����
	char number[6];								//��� 
	char name[6];								//����
	char sche[6];								//������� 
	char time[6];								//����ʱ��
}InfoType;
typedef struct
{//�ؼ���-��̬����������
	KeyType keys[keylen];						//�ؼ��֣��ŶӺţ�
	InfoType others;
	int next;
}SLNode;
typedef struct 
{//�ؼ�������-��̬��������
	SLNode sl[MaxSpace];						//��̬����
	int keynum;									//�ؼ����ַ���
	int length;									//��
}SLList;

typedef int ArrType_n[RADIX_n];  				//�����ַ�
typedef int ArrType_c[RADIX_c];  				//��ĸ�ַ�

KeyType key[keylen],kl[4];

//���ܺ������� ϵͳ�ӳ��򼰹������
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

// 1. �����ַ����亯�� 
void Distribute(SLNode *sl, int i, int *f, int *e)///////
{
    int j,p;
    for ( j=0;j<RADIX_n;j++)	
		f[j]=0;
	for ( p=sl[0].next; p; p=sl[p].next)
	{
		j=sl[p].keys[i]%48;				//�������ַ�ӳ��Ϊʮ��������
		if ( !f[j])	f[j]=p;			
		else		sl[e[j]].next=p;	//��pָ��Ľ����뵽��j���ӱ���
		e[j]=p;			
	}
}

// 2. ��ĸ�ַ����亯�� 
void Distribute_c(SLNode *sl, int i, int *f, int *e)///////
{  
	int j,p;
	for ( j=0;j<RADIX_c;j++)
		f[j]=0;
	for ( p=sl[0].next; p!=0; p=sl[p].next)
	{
		j=sl[p].keys[i]%65;				//����ĸ�ַ�ӳ��Ϊ��ĸ���е���Ӧ���
		if ( !f[j])	f[j]=p;		
		else	sl[e[j]].next=p;		//��pָ��Ľ����뵽��j���ӱ���
		e[j]=p;			
	}
}


// 3. ��ָ�����������Ա� 
void Arrange(SLList *L)
{   
	int p,q,i;
    SLNode temp;
	p=L->sl[0].next;							//pָ���һ�����
	for ( i=1;i<L->length;i++)
	{
		while ( p<i)							//���ҵ�i����㣬����pָ��˽��
			p=L->sl[p].next;
		q=L->sl[p].next;
		if ( p!=i)					//����i����㲻�ڵ�ǰλ�ã������������
		{
			temp=L->sl[p];
            L->sl[p]=L->sl[i];
            L->sl[i]=temp;
			L->sl[i].next=p;
		}
		p=q;					 	//pָ����һ��δ�������
	}
}

// 4. �۰���Һ��� 
int BinSearch(SLList L, KeyType key[])
{   	//�۰���Һ������������L�в��ҹؼ���Ϊkey[]�ļ�¼
    int high, low, mid;						    //���½����ֵ
    	low=1; 								//�½��ʼ��Ϊ1
    high=L.length;							    //�Ͻ��ʼ��Ϊ��
	while (low<=high)						//�б��������
	{
		mid=(low+high)/2;					//������ֵ
		if ( strcmp(key,L.sl[mid].keys)==0)	//�����õ�����ֵ
			return mid;						//���ҳɹ�, ������ֵ
		else if ( strcmp(key,L.sl[mid].keys)<0)		//����ֵ���
			high=mid-1;						//�����Ͻ�, ������������
		else 								//����ֵ�ұ�
            low=mid+1;						//�����½�, ������������
	}
	return 0;								//����ʧ��, ����0
}

// 5.˳����Һ��� 
void SeqSearch(SLList L, KeyType key[],int i)
{  	//˳����Һ������������L�в��ҹؼ���Ϊkey[]�ļ�¼
    int j, k, m=0;
   	for (j=1; j<=L.length; j++)
   	{
		switch(i)						//����ͬ�ؼ��ֲ���
		{
           case 2:  k=strcmp(key,L.sl[j].others.number);	 break;  
                    //��˳�����ε���strcmp�������бȽ�
           case 3:  k=strcmp(key,L.sl[j].others.name);  break;  
                    //��˳�����ε���strcmp�������бȽ�
           case 4:  k=strcmp(key,L.sl[j].others.time); break;  
                    //��˳�����ε���strcmp�������бȽ�
          
		}
	 	if ( k==0) 						//���ҳɹ�
	   	{
			m=1;						//���ұ�ʶ��Ϊ1
			Display(L,j);				//��ʾ���ҽ��
	   	}
  	}//namefor
   	if (m==0)							//����ʧ��
	   printf ( "�ܱ�Ǹ���޴˿ͻ���Ϣ��\n");	//�����ʾ��Ϣ
}

// 6. ��ӡ�ͻ���Ϣ���� 
void Display(SLList L, int i)
{
	printf ( "��� ���� ������� �������\n");
	DisplayStyle(6, L.sl[i].keys);
DisplayStyle(7, L.sl[i].others.number);	        //���ƶ������
 	DisplayStyle(7, L.sl[i].others.name);
DisplayStyle(7, L.sl[i].others.sche);       //���ƶ������
   
	printf ( "\n");
}

// 7. ���������ʽ���� 
void DisplayStyle(int i, char *s)
{	//������ʽ�������������ж���
	int j;
	i -= strlen(s);
	for ( j=0; j<i; ++j)  printf ( " ");		//���ռλ�ո�, �Ա����
	printf ( "%s,", s);
}

// 8. ���ҽ������溯�� 
void searchcon(SLList L)
{
	int i=1,k;
	while (i>=1 && i<=6)
	{
		printf(" \n��ѡ���������(0---6), 0 Ϊ�˳�ϵͳ:  ");
		scanf("%d", &i);
		switch(i)
		{
			case 1:
  				   printf("����Ҫ��ѯ�����:  ");
			   	   scanf(" %s", key);k=BinSearch(L, key);
				   if (k)  Display(L,k);
				   else printf("�ܱ�Ǹ���޴˿ͻ���Ϣ��\n");
				   break;
			case 2: 
                   printf("����Ҫ��ѯ�Ŀͻ�����: ");
			       scanf("%s", key); SeqSearch(L, key, i);
			       break;
			case 3: 
                   printf("����Ҫ��ѯ�Ĵ������: ");
			       scanf( "%s", key); SeqSearch(L, key, i);
				   break;
			case 4: 
                   printf("����Ҫ��ѯ�ĵ���ʱ��: ");
			       scanf( "%s", kl); SeqSearch(L, kl, i);
			       break;
			case 5: 
                   printf("������¼��ͻ���Ϣ����:\n");
			       InputData(&L);
			       break;
			case 0:  
				   exit(0);
		}
		Prompt();                          	//ѭ����ʾ���˵�
	}
}

// 9. ��ʾ���˵����� 
void Prompt()
{
	printf ( "***************************************************\n");
	printf ( "     	*          �ͻ���Ϣ��ѯ�����ϵͳ         	*\n");	
	printf ( "      	*          1. ����Ų�ѯ               	*\n");
	printf ( "      	*          2. ��������ѯ               	*\n");
	printf ( "      	*          3. ��������ڲ�ѯ               	*\n");
	printf ( "      	*          4. ������ʱ���ѯ             	*\n");
	printf ( "      	*          5. ����¼��ͻ���Ϣ             	*\n");
	printf ( "      	*          0. �˳�ϵͳ                   	*\n");
	printf ( "***************************************************\n");
}

// 10. ����ͻ���¼���� 
bool InputData(SLList *L)
{
	int i=++L->length;
	char yn='y';
	printf ( "\n������¼��ͻ���Ϣ����:");
	do
	{
		printf("\n��� ���� ������� ����ʱ�� \n");
		scanf ("%s %s %s %s",  &L->sl[i].others.number, &L->sl[i].others.name,&L->sl[i].others.sche,
			&L->sl[i].others.time);
		fflush(stdin);   					//������뻺����
		++i;
		printf ( "����������? y/n:");
	}while((yn=getche())=='y' || yn=='Y');
	printf("\n");
	L->length=i-1;
	//RadixSort(L);
	//Arrange(L);
	return true;
}


// 11. ������ 
int main()
{
	SLList L;
	L.keynum=6; L.length=0;				//��ʼ��
	Prompt();	  						//��ʾ���˵�
	if (!InputData(&L))					//��Ϣ¼�룬��������Ч��
	{
		printf ( SHOW_MSG_ERROR);
		return 1;
	}
	searchcon(L);						//ִ����ز�ѯ
	return 0;
}


