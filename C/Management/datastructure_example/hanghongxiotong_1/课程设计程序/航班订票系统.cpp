#include<stdio.h>

#include<stdlib.h>

#include<string.h>

typedef struct{

double number;//�������

char name[20];//����

char id[20];//���֤��

int count;//����

char p[20];//�����

}GUEST;

typedef struct{

char num[20];//�����

char depart[30];//��������

char arrive[30];//�������

char start[20];//���ʱ��

char end[20];//����ʱ��

int price;//�۸�

int discount;//�ۿ��ʣ�%��

int total;//��Ʊ��

int rest;//ʣ��Ʊ��

int t;//������

GUEST guest[20];//�˿�

}PLANE;

PLANE plane[20];

int n;//nΪ������

void inputplane(){//���뺽��

int i;

printf("�����ܺ�������");

scanf("%d",&n);

printf("���뺽����Ϣ��\n");

printf("�����  ��������  �������  ���ʱ��  ����ʱ��  �۸�  �ۿ���  ��Ʊ��  ʣ��Ʊ��\n");

for(i=0;i<n;i++)

scanf("%s   %s     %s     %s     %s     %d     %d    %d    %d",plane[i].num,plane[i].depart,plane[i].arrive,plane[i].start,plane[i].end,&plane[i].price,&plane[i].discount,&plane[i].total,&plane[i].rest);

}

void list(){//��ʾ

int i;

printf("�����  ��������  �������  ���ʱ��  ����ʱ��  �۸�  �ۿ���  ��Ʊ��  ʣ��Ʊ��\n");

for(i=0;i<n;i++)

printf("%s     %s     %s     %s    \t%s\t%d      %d\t%d \t%d\n",plane[i].num,plane[i].depart,plane[i].arrive,plane[i].start,plane[i].end,plane[i].price,plane[i].discount,plane[i].total,plane[i].rest);

}

void search1(){//������Ų�ѯ

int i;

char num[20];

printf("�������ѯ�ĺ���ţ�");

scanf("%s",num);

for(i=0;i<n;i++)

{

if(strcmp(num,plane[i].num)==0)

{

printf("�����  ��������  �������  ���ʱ��  ����ʱ��  �۸�  �ۿ���  ��Ʊ��  ʣ��Ʊ��\n");

printf("%s     %s     %s     %s    \t%s\t%d     %d\t%d \t%d\n",plane[i].num,plane[i].depart,plane[i].arrive,plane[i].start,plane[i].end,plane[i].price,plane[i].discount,plane[i].total,plane[i].rest);

break;

}

}

if(i==n)

printf("û�д˺��࣡\n");

}

void search2(){//����ɵִ���в�ѯ

int i;

char a[50],b[50];

printf("������ɳ��к͵�����У�");

scanf("%s %s",a,b);

printf("�����  ��������  �������  ���ʱ��  ����ʱ��  �۸�  �ۿ���  ��Ʊ��  ʣ��Ʊ��\n");

for(i=0;i<n;i++)

{

if((strcmp(a,plane[i].depart)==0)&&(strcmp(b,plane[i].arrive)==0))

printf("%s     %s     %s     %s   \t%s\t%d    %d\t%d \t%d\n",plane[i].num,plane[i].depart,plane[i].arrive,plane[i].start,plane[i].end,plane[i].price,plane[i].discount,plane[i].total,plane[i].rest);

}

printf("\n");

for(i=0;i<n;i++)

{

if((strcmp(a,plane[i].depart)==0)&&(strcmp(b,plane[i].arrive)==0))

break;

}

if(i==n)

printf("û�д˺��࣡\n");

}

void book(){//��Ʊ

char name[20],p[20],id[20];

double number;

int i,j,k,y,count;

for(i=0;i<n;i++)

plane[i].t=0;

do

{

printf("���붩����Ϣ��\n");

printf("�������  ����  ���֤��  ��Ʊ��  �����\n");

scanf("%d %s %s %d %s",&number,name,id,&count,p);

for(i=0;i<n;i++)

{

if(strcmp(p,plane[i].num)==0)

break;

}

if(i==n)

printf("û�д˺���\n");

else

{

if(plane[i].rest>=count)

{

j=plane[i].t;

plane[i].guest[j].number=number;

strcpy(plane[i].guest[j].name,name);

strcpy(plane[i].guest[j].id,id);

plane[i].guest[j].count=count;

strcpy(plane[i].guest[j].p,p);

plane[i].rest-=count;

plane[i].t++;

}

else

{

printf("�ܱ�Ǹ���ú���ʣ��Ʊ��Ϊ %d ��\n",plane[i].rest);

for(k=0;k<n;k++)

{

if((strcmp(plane[i].depart,plane[k].depart)==0)&&(strcmp(plane[i].depart,plane[k].depart)==0))

break;

}

if(k==n)

printf("û��������%s��%s�ĺ���\n",plane[i].depart,plane[i].arrive);

else

{

printf("��%s��%s���� %s ����\n\n",plane[k].depart,plane[k].arrive,plane[k].num);

printf("�����  ��������  �������  ���ʱ��  ����ʱ��  �۸�  �ۿ���  ��Ʊ��  ʣ��Ʊ��\n");

printf("%s     %s     %s     %s   \t%s\t%d     %d\t%d \t%d\n",plane[k].num,plane[k].depart,plane[k].arrive,plane[k].start,plane[k].end,plane[k].price,plane[k].discount,plane[k].total,plane[k].rest);

}

}

}

printf("�Ƿ������Ʊ�����ǡ�����1����������0\n");

scanf("%d",&y);

}while(y);

}

void quit(){ //��Ʊ

double number;

char id[20];

int i,j,temp,k,y;

temp=0;

printf("���������Ķ������:\n");

scanf("%d",&number);

printf("�������������֤��\n");

scanf("%s",id);

for(i=0;i<n;i++)

{

for(j=0;j<plane[i].t;j++)

{

if(number==plane[i].guest[j].number&&(strcmp(id,plane[i].guest[j].id)==0))

{

temp=1;

break;

}

}

if(temp==1)

break;

}

if(i==n)

printf("û�д˶�����\n");

else

{

printf("�������  ����  ���֤��  ��Ʊ��  �����\n");

printf("    %d",plane[i].guest[j].number);

printf("     %s",plane[i].guest[j].name);

printf("     %s",plane[i].guest[j].id);

printf("     %d",plane[i].guest[j].count);

printf("     %s\n",plane[i].guest[j].p);

printf("���Ƿ�ȷ��ɾ��(1/0)\n");

scanf("%d",&y);

if(y==1)

{

plane[i].rest+=plane[i].guest[j].count;

for(k=j+1;k<plane[i].t;k++)

{

plane[i].guest[k-1].number=plane[i].guest[k].number;

strcpy(plane[i].guest[k-1].name,plane[i].guest[k].name);

strcpy(plane[i].guest[k-1].id,plane[i].guest[k].id);

plane[i].guest[k-1].count=plane[i].guest[k].count;

strcpy(plane[i].guest[k-1].p,plane[i].guest[k].p);

}

plane[i].t--;

printf("��Ʊ�ɹ�!!\n");

}

}

}


void change()//�޸�

{

char a[20];

int i;

printf("��������Ҫ�޸ĵĺ����:");

scanf("%s",a);

for(i=0;i<n;i++)

{

if(strcmp(a,plane[i].num)==0)

break;

}

if(i==n)

printf("û�д˺��࣡\n");

else

{

printf("ԭ��Ϣ:\n");

printf("�����  ��������  �������  ���ʱ��  ����ʱ��  �۸�  �ۿ���  ��Ʊ��  ʣ��Ʊ��\n");

printf("%s    %s     %s     %s    \t%s\t%d    %d\t%d \t%d\n",plane[i].num,plane[i].depart,plane[i].arrive,plane[i].start,plane[i].end,plane[i].price,plane[i].discount,plane[i].total,plane[i].rest);

printf("�������޸ĺ����Ϣ:\n");

printf("�����  ��������  �������  ���ʱ��  ����ʱ��  �۸�  �ۿ���  ��Ʊ��  ʣ��Ʊ��\n");

scanf(" %s    %s    %s    %s    %s   %d    %d    %d    %d",plane[i].num,plane[i].depart,plane[i].arrive,plane[i].start,plane[i].end,&plane[i].price,&plane[i].discount,&plane[i].total,&plane[i].rest);

}

}

int main()

{

int a,b;

do

{

system("cls");

for(a=0;a<50;a++)

printf("*");

printf("\n");

printf("\t\t1�� ���뺽����Ϣ\n");

printf("\t\t2�� �г�������Ϣ\n");

printf("\t\t3�� ������Ų�ѯ������Ϣ\n");

printf("\t\t4�� ������������в�ѯ������Ϣ\n");

printf("\t\t5�� ��Ʊ\n");

printf("\t\t6�� ��Ʊ\n");

printf("\t\t7�� �޸ĺ�����Ϣ\n");

printf("\t\t8�� �˳�����\n");

for(a=0;a<50;a++)

printf("*");

printf("\n");

printf("�����빦��ѡ��1-8)��\n");

scanf("%d",&b);

switch(b)

{

case 1:

inputplane();

system("pause");

break;

case 2:

list();

system("pause");

break;

case 3:

search1();

system("pause");

break;

case 4:

search2();

system("pause");

break;

case 5:

book();

system("pause");

break;

case 6:

quit();

system("pause");

break;

case 7:

change();

system("pause");

break;

case 8:
	
return 0;

}

}while(1);

}
