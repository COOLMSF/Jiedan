/*ʵ��һ
   ����һ�л�����ɡ�#����β��C����ʶ��������еı�ʶ���ͳ�����
�������룺
void main()
{ int x1,x2,y;
  x1=34;
  x2=56.78;
  y=x1+x2*3; 
}#
���:(��ʶ��,void)(��ʶ��,main)(��ʶ��,int)(��ʶ��,x1)(��ʶ��,x2)(��ʶ��,y)(��ʶ��,x1)(����,34)(��ʶ��,x2)(����,56.78)(��ʶ��,y)
(��ʶ��,x1)(��ʶ��,x2)(����,3) 
*/
#include <iostream>
#include <string.h>
using namespace std;

//��������
void input(char b[]);
int SaveBid(char a[], int i,  struct node Id[], int N);
int SaveNum(char a[], int i, struct node Num[], int N);
int Isletter (char a[], int i);
int IsNum(char a[], int i);
void Compile(char a[], struct node Id[], struct node Num[]);
void output(struct node Id[], struct node Num[]);

const int SIZE=300;
const int size=20;

struct node
{	char list[size];
	int flag;	//flag=0����û��С���㣬��������
};
int IdLen=0;   //���б�ʶ���ĸ����������ظ���
int NumLen=0;  //���г����ĸ����������ظ��ĺ���������ʵ����
struct node Id[SIZE/2], Num[SIZE/2];

void main()
{	char a[SIZE];

	cout <<"������Դ������룬����'#'�Ž�����" <<endl;
	input(a);
	Compile(a, Id , Num);
	output(Id, Num);
}

void input(char b[])
{// �������Դ���뱣��������b�У���"#"����
	int i=0;
	char c=getchar();
	while(c != '#')
	{   b[i++]=c;
		c=getchar();
	}
	b[i]='#';
}
int SaveBid(char a[], int i,  struct node Id[], int N)
{//�Ѿ�ʶ������a�д��±�i������a���±꣩��ʼ���Ǳ�ʶ������ȡ�õ��ʲ����䱣����//����Id�У����±�N������Id���±꣩��ʼ��š����ظñ�ʶ���ĳ��ȡ�

	//��ɸú���
}

int SaveNum(char a[], int i, struct node Num[], int N)
{//�Ѿ�ʶ������a�н������ǳ�����ʶ���䲢���䱣��������Num��
 //���ش˴α���ĳ����ĳ���

	//��ɸú���
}

int Isletter(char a[], int i)
{//������ĸ��ͷ������Ϊ��������һ����ʶ��
	char c=a[i];
	if(c>='a' && c<='z' || c>='A' && c<='Z' || c=='_' )
	    return 1;
	return 0;
}

int IsNum(char a[], int i)
{//�жϽ������Ƿ�Ϊһ������
	if(a[i]>='0' && a[i]<='9')
		return 1;
	return 0;
}

void Compile(char a[], struct node Id[], struct node Num[])
{
	//����ɸú���
}

void output(struct node Id[], struct node Num[])
{
	int i, j;
	cout<<"��ʶ����";
	for(i=0; i<IdLen; i++)
	{int flag1=0;
	 for(j=i+1; j<IdLen;j++)
			if(!strcmp(Id[i].list, Id[j].list))   //������ַ�����ȣ������
			{
				 flag1=1;  //���
				 break;
			}
		if(flag1 !=1)//����ȣ���û���ظ���ʶ�����������
		{int k=0;
		 while(Id[i].list[k] != '#')
				{
					cout <<Id[i].list[k];
					k++;
				}
		  cout << "  ";
		}
	  }
	  cout<<endl;

	cout<<"��������";
	for(i=0; i<NumLen; i++)
	{int flag2=0;
	 if(Num[i].flag !=1)
		for(j=i+1; j<NumLen;j++)
				if(!strcmp(Num[i].list, Num[j].list))
				{
					flag2=1; break;
				}
		if(flag2 !=1 && Num[i].flag !=1)
		{int k=0;
		 while(Num[i].list[k] != '#')
			{
						cout <<Num[i].list[k];
						k++;
			}
		  cout << "  ";
		 }
	   }
	cout << endl;

	cout <<"ʵ������";
	for(i=0; i<NumLen; i++)
	{int flag3=0;
	 if(Num[i].flag ==1)
		 for(j=i+1; j<NumLen;j++)
		     if(!strcmp(Num[i].list, Num[j].list))
				{flag3=1;  break;}

		   if(flag3 !=1 && Num[i].flag==1)
			{int k=0;
			 while(Num[i].list[k] != '#')
			 {
						cout <<Num[i].list[k];
						k++;
			 }
			 cout << " ";
			}
		}
	  cout <<endl;
}
