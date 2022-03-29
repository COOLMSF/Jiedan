#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct ADDRESS
{
	char name[10];
	char tele[12];
	char add[50];
	char group[50];
}ADDRESS;

ADDRESS Capa[30];                             //�ṹ������
ADDRESS Temp[30];                             //���ڱ�������Ľṹ������

int Search_Name(char a[],int num[]);          //�������������
void NameRes();                               //����������
int Search_Group(char a[]);                   //��Ⱥ���������
void GroupRes();                              //��Ⱥ�����
void Order(ADDRESS *p,int pnum);              //������
int AddressList();
int Menu();                                   //�˵�����
void ReMenu();                                //���ز˵�����
int Get(char *fileName);                      //���뺯��
void Trans(ADDRESS a);                        //���亯��
void Edit(char a[]);                          //�޸ĺ���
void Add();                                   //��Ӻ���
void ShowAll(ADDRESS *p,int pnum);            //��ʾͨѶ¼��������Ϣ
void ShowOne(ADDRESS *p,int pnum);		      //�����ʾ��ϵ����Ϣ
void DelectOne();                             //ɾ����������
void DelectAll();                             //ɾ��ȫ������
int Save(char* fileName);                     //���溯��
int TotalNum=0;

int Get(char *fileName)                                          //�ļ����ݻ�ȡ����
{
	FILE *pFile = fopen(fileName,"r");
	if(!pFile)
	{
		return 0;
	}
	char str[200];
	while(fgets(str,200,pFile))                                  //���ļ��ж�����������������str��
	{
		ADDRESS data;
		sscanf(str,"%s",data.name);                              //���ַ����ж�����Ϣ�浽�ṹ����
		sscanf(str+strlen(data.name)+1,"%s",data.tele);
		sscanf(str+strlen(data.name)+1+strlen(data.tele)+1,"%s",data.add);
		sscanf(str+strlen(data.name)+1+strlen(data.tele)+1+strlen(data.add)+1,"%s",data.group);
		Trans(data);                                             //���ú��������ṹ����Ϣ����ṹ��������
	}
	fclose(pFile);
	return 1;
}


void Trans(ADDRESS a)                   //���亯�������ṹ��ADDRESS��Ϣ����ṹ������Capa��
{
	Capa[TotalNum] = a;
	TotalNum++;
	Order(Capa,TotalNum);
}


void Order(ADDRESS *p,int pnum)         //��������ƴ������
{
	int i,j,m;
	ADDRESS temp;
	for(i=0;i<pnum;i++)
	{
		m=i;
		for(j=0;j<i;j++)
		{
			if(strcmp(p[j].name,p[m].name)>0)
			{
				m=j;
				temp=p[i];
				p[i]=p[m];
				p[m]=temp;
			}
		}
	}
}


int Search_Name(char a[],int num[])                                                   //�������������
{
	int i,j=-1;
	for(i=0;i<TotalNum;i++)
	{
		if(strcmp(Capa[i].name,a)==0)
			num[++j]=i;
	}
	return j;
}


void NameRes()                                                       //�����ֲ���
{

	int n,m;
	int num[50]={-1};
	char a[100];
	printf("    ��������ϵ��������");
	gets(a);
	n=Search_Name(a,num);
	if(n==-1)
	{
		fflush(stdin);
		printf("    �����ڸ���ϵ�ˣ����������룡\n");
		printf("    �Ƿ񷵻����˵���1�����أ�2������");
		char go[50];
		gets(go);
		int i = 0;
		while(go[i]==' ')
			i++;
		if(go[i]=='1')
		{
			fflush(stdin);                          //������뻺��
			ReMenu();
		}
		else
			NameRes();
	}
	else
	{
		fflush(stdin);
		for(m=0;m<=n;m++)
		{
			printf("    ��ϵ����ţ�%d\n",m);
			printf("    ��ϵ��������%s\n",Capa[num[m]].name);
			printf("    ��ϵ�˵绰���룺%s\n",Capa[num[m]].tele);
			printf("    ��ϵ�˵�ַ��%s\n",Capa[num[m]].add);
			printf("    ��ϵ��Ⱥ�飺%s\n",Capa[num[m]].group);
		}
		printf("    1.��������  0.�������˵�\n");
		while(1)
		{
			printf("    ��ѡ��");
			char go[50];
			gets(go);
			int i = 0;
			while(go[i]==' ')
				i++;
			if(go[i]=='1')
			{
				fflush(stdin);
				NameRes();
				return;
			}
			else if(go[i]=='0')
			{
				ReMenu();
				return;
			}
			else
			{
				printf("    ���벻�Ϸ���");
				continue;
			}
		}
	}
}


int Search_Group(char a[])                                //��Ⱥ���������
{
	int i,r=0;
	for(i=0;i<TotalNum;i++)
	{
		if(strcmp(Capa[i].group,a)==0)
		{
			Temp[r] = Capa[i];
			r++;
		}
	}
	return r;
}


void GroupRes()                                     //��Ⱥ�����
{
	printf("    ������Ҫ���ҵ�Ⱥ�����ƣ�");
	char a[100];
	int num[50]={-1};
	gets(a);
	int n;
	n = Search_Group(a);
	if(!n)
	{
		fflush(stdin);
		printf("    ��Ⱥ����û����ϵ�ˣ�\n");
		printf("    �Ƿ񷵻����˵���1�����أ�2������");
		char go[50];
		gets(go);
		int i = 0;
		while(go[i]==' ')
			i++;
		if(go[i]=='1')
		{
			fflush(stdin);
			ReMenu();
		}
		else
			GroupRes();
	}
	else
	{
		fflush(stdin);
		ShowAll(Temp,n);                           //�����Ⱥ��������ϵ����Ϣ
	}
}


void Edit(char a[])           //�޸���ϵ�˺���
{
	int n,m,p;
	int num[50]={-1};
	n=Search_Name(a,num);
    while(1)
		{
			m=0;
			for(m=0;m<=n;m++)
			{
				printf("    \n��ϵ����ţ�%4d\n",m);
				printf("    ��ϵ��������%s\n",Capa[num[m]].name);
				printf("    ��ϵ�˵绰���룺%s\n",Capa[num[m]].tele);
				printf("    ��ϵ�˵�ַ��%s\n",Capa[num[m]].add);
				printf("    ��ϵ��Ⱥ�飺%s\n",Capa[num[m]].group);
			}
			if(m<=n+1)
			{
				printf("    \n��ѡ��Ҫ�޸ĵ���ϵ����ţ�");
				scanf("%d",&p);
				fflush(stdin);
			}
			if(p>=0&&p<=m)
			{
				printf("    \n��ѡ��Ҫ�޸ĵ���Ŀ��\n1.��ϵ������\n2.��ϵ�˵绰����\n3.��ϵ�˵�ַ\n4.��ϵ��Ⱥ��\n0.�������˵�\n");
				printf("    ��ѡ��");
				char go[100];
				gets(go);
				int i = 0;
				while(go[i]==' ')                      //��Ч���룬������һ�ַ�
					i++;
				if(go[i]=='1')
				{
					printf("    �����޸ĺ����ϵ��������");
					gets(Capa[num[p]].name);
					Order(Capa,TotalNum);
					fflush(stdin);
					printf("    �޸ĳɹ����������˵�\n");
					fflush(stdin);
					ReMenu();
					break;
				}
				else if(go[i]=='2')
				{
					printf("    �����޸ĺ����ϵ�˵绰���룺");
					gets(Capa[num[p]].tele);
					fflush(stdin);
					printf("    �޸ĳɹ����������˵�\n");
					fflush(stdin);
					ReMenu();
					break;
				}
				else if(go[i]=='3')
				{
					printf("    �����޸ĺ����ϵ�˵�ַ��");
					gets(Capa[num[p]].add);
					fflush(stdin);
					printf("    �޸ĳɹ����������˵�\n");
					fflush(stdin);
					ReMenu();
					break;
				}
				else if(go[i]=='4')
				{
					printf("    �����޸ĺ����ϵ��Ⱥ�飺");
					gets(Capa[num[p]].group);
					fflush(stdin);
					printf("    �޸ĳɹ����������˵�\n");
					fflush(stdin);
					ReMenu();
					break;
				}
				else if(go[i]=='0')
				{
					fflush(stdin);
					ReMenu();
					break;
				}
				else                                       //������
				{
					fflush(stdin);
					printf("    ��������Ϸ������������룡\n");
				}
			}
			else
			{
				fflush(stdin);
				printf("    ��������Ϸ������������룡\n");
				scanf("%d",&p);
				fflush(stdin);
			}
		}
}


void Add()     //�����ϵ�˺���
{
	while(1)
	{
		char a[30];
		int num[50]={-1};
		printf("    ������Ҫ��ӵ���ϵ��������");
		gets(a);
		fflush(stdin);
		if(Search_Name(a,num)==-1)                 //��ԭ������û��������ӵ������ص������
		{
			strcpy(Capa[TotalNum].name,a);     //������a�е����ݸ��Ƶ��ṹ�������е�name����
			printf("    ��ϵ�˵绰��");
			gets(Capa[TotalNum].tele);
			printf("    ��ϵ�˵�ַ��");
			gets(Capa[TotalNum].add);
			printf("    ��ϵ�����");
			gets(Capa[TotalNum].group);
			TotalNum++;
			Order(Capa,TotalNum);
			printf("    ��ϵ����ӳɹ���");
			printf("    ��������������˵���");
			if(getchar())                     //���������
				ReMenu();                     //���÷��ز˵�����
			break;
		}
		else
		{
			printf("    ��ʾ���Ѿ����ڸ��û���" );
			printf("    1.�滻�Ѵ��ڵ��û�  2.���������ϵ�� 3. �½���������ϵ�� 0.�������˵�\n " );
			printf("    ��ѡ��");
			char go[100];
			gets(go);
			int i=0;
			while(go[i]==' ')
				i++;
			if(go[i]=='1')
			{
				Edit(a);
				break;
			}
			else if(go[i]=='2')
			{
				fflush(stdin);
				continue;
			}
			else if(go[i]=='0')
			{
				fflush(stdin);
				ReMenu();
			}
			else if(go[i]=='3')
			{
				strcpy(Capa[TotalNum].name,a);     //������a�е����ݸ��Ƶ��ṹ�������е�name����
				printf("    ��ϵ�˵绰��");
				gets(Capa[TotalNum].tele);
				printf("    ��ϵ�˵�ַ��");
				gets(Capa[TotalNum].add);
				printf("    ��ϵ�����");
				gets(Capa[TotalNum].group);
				TotalNum++;
				Order(Capa,TotalNum);
				printf("    ��ϵ����ӳɹ���");
				fflush(stdin);
				printf("    ��������������˵���");
				if(getchar())                      //���������
				{
					fflush(stdin);
					ReMenu();
				}
			}
		}
	}
}


void ShowOne(ADDRESS *p,int pnum)											//�����ʾ��ϵ����Ϣ
{
	int j=0;
	int i;
	while(j<pnum)
	{
		printf("\n\n");
		printf("    --------------------------------------------------------\n" );
		printf("\t����	     �绰����          ��ַ           Ⱥ�� \n" );
		printf("    --------------------------------------------------------\n" );
		printf("  %10s   %15s   %10s	%10s\n",p[j].name,p[j].tele,p[j].add,p[j].group);
		printf("    --------------------------------------------------------\n" );
		printf("    �������˵�0 ��һҳ1   ��һҳ2   ��ǰҳ���� %d   �� %d ҳ\n" ,j+1,pnum);
		printf("    ��ҳ����:");
		char go[100];
		gets(go);
		fflush(stdin);
		i = 0;
		while(go[i]==' ')
			i++;
		if(go[i]=='1')
		{
			fflush(stdin);
			if(j>1)
				j--;
			else
			{
				printf("\n��ǰ��Ϊ��һҳ!\n\n\n");
			}
		}
		else if(go[i]=='2')
		{
			fflush(stdin);
			if(j+1<pnum)
				j++;
			else
			{
				printf("\n��ǰ��Ϊ���һҳ!\n\n\n");
			}
		}
		else if(go[i]=='0')
		{
			fflush(stdin);
			ReMenu();
			break;
		}
		else
		{
			fflush(stdin);
			printf("    ��ʾ������ָ��Ϸ������������룡\n");
			continue;
		}
	}
}


void ShowAll(ADDRESS *p,int pnum)		//��ʾȫ����ϵ����Ϣ
{
	int pagenumber = 1;
	while(pagenumber)
	{
		printf("    --------------------------------------------------------\n" );//��ʾͨѶ¼������Ϣ
		printf("\t����	     �绰����          ��ַ           Ⱥ�� \n" );
		printf("    --------------------------------------------------------\n" );
		int i;
		int end;
		if(pagenumber*10>pnum)          //ÿҳ��ʾ10����¼
			end = pnum%10;
		else
			end = 10;
		for(i=0+(pagenumber-1)*10;i<end+(pagenumber-1)*10;i++)
		{
			printf("  %10s   %15s   %10s	%10s\n",p[i].name,p[i].tele,p[i].add,p[i].group); //�����ϵ����Ϣ
		}
		printf("    --------------------------------------------------------\n" );
		printf("    �������˵�0 ��һҳ1   ��һҳ2              ��ǰҳ���� %d\n" ,pagenumber);
		printf("    ��ҳ����:");
		char go[100];
		gets(go);
		i = 0;
		while(go[i]==' ')                                     //��ȡ�ո�֮�����Ч����
			i++;
		if(go[i]=='1')
		{
			fflush(stdin);
			if(pagenumber>1)
				pagenumber--;
			else
			{
				printf("\n��ǰ��Ϊ��һҳ!\n\n\n");
			}
		}
		else if(go[i]=='2')
		{
			fflush(stdin);
			if(pagenumber*10<pnum)
				pagenumber++;
			else
			{
				printf("\n��ǰ��Ϊ���һҳ!\n\n\n");
			}
		}
		else if(go[i]=='0')
		{
			fflush(stdin);
			ReMenu();
			break;
		}
		else
		{
			fflush(stdin);
			printf("    ��ʾ������ָ��Ϸ������������룡\n");
			continue;
		}
	}
}


void DelectOne()                                  //ɾ��������ϵ��
{
	char a[100];
	int num[50]={-1};
	int m,p;
	printf("    ������Ҫɾ������ϵ�˵�������");
	gets(a);
	int n;
	n = Search_Name(a,num);
	if(n==-1)
	{
		fflush(stdin);
		printf("    �����ڸ���ϵ�ˣ�2����������  0���������˵�");
		char go[100];
		fflush(stdin);
		gets(go);
		fflush(stdin);
		int i=0;
		while(go[i]==' ')
			i++;
		if(go[i]=='2')
		{
			DelectOne();
		}
		else if(go[i]=='0')
		{
			ReMenu();
		}
	}
	else
	{
		for(m=0;m<=n;m++)
		{
			printf("    ��ϵ����ţ�%4d\n",m);
			printf("    ��ϵ��������%s\n",Capa[num[m]].name);
			printf("    ��ϵ�˵绰���룺%s\n",Capa[num[m]].tele);
			printf("    ��ϵ�˵�ַ��%s\n",Capa[num[m]].add);
			printf("    ��ϵ��Ⱥ�飺%s\n",Capa[num[m]].group);
		}
abc:	printf("    ������Ҫɾ������ϵ����ţ�");
		scanf("%d",&p);
		fflush(stdin);
		if(p>=0&&p<=m)
		{
			printf("    ȷ��Ҫɾ����ǰ��ϵ����Ϣ��");
			printf("    1.�� 2.��   0.�������˵�\n");
			while(1)
			{
				printf("    ��ѡ��");
				char go[100];
				gets(go);
				int i = 0;
				while(go[i]==' ')
					i++;
				if(go[i]=='1')
				{
					int i;
					for(i=num[p]+1;i<TotalNum;i++)
					{
						Capa[i-1] = Capa[i];
					}
					TotalNum--;
					printf("    ��ϵ��ɾ���ɹ���2������ɾ�� 0���������˵�   ");
				}
				else if(go[i]=='2')
				{
					DelectOne();
					return;
				}
				else if(go[i]=='0')
				{
					ReMenu();
					return;
				}
				else
				{
					printf("    ��������Ϸ���2:�������룡0:�������˵�   ");
					continue;
				}
			}
		}
		else
		{
			fflush(stdin);
			printf("    ��������Ϸ������������룡\n");
			scanf("%d",&p);
			fflush(stdin);
			goto abc;

		}
	}
}


void DelectAll()                                                /*ɾ��ȫ����ϵ����Ϣ*/
{
	printf("    ȷ��Ҫɾ��ȫ������ϵ����Ϣô��\n");
	printf("    1.�� 2.��    0.�������˵�\n");
	while(1)
	{
		printf("    ��ѡ��");
		char go[100];
		gets(go);
		int i = 0;
		while(go[i]==' ')
			i++;
		if(go[i]=='1')
		{
			TotalNum = 0;
			printf("    ��ϵ��ɾ���ɹ���\n");

			printf("    �������˵�������1.");
			char go[100];
			fflush(stdin);
			gets(go);
			fflush(stdin);
			int i=0;
			while(go[i]==' ')
				i++;
			if(go[i]=='1')
			{
				ReMenu();
			}
		}
		else if(go[i]=='2')
		{
			ReMenu();
			return;
		}
		else if(go[i]=='0')
		{
			ReMenu();
			return;
		}
		else
		{
			printf("    ��������Ϸ������������룡\n");
			continue;
		}
	}
}


int Save(char *fileName)                                                     //�������ļ�����
{
	FILE *pFile = fopen(fileName,"w");
	if(!pFile)
	{
		return 0;
	}
	int i = 0;
	while(i<TotalNum)
	{
		fprintf(pFile,"%s\t%s\t%s\t%s\n",Capa[i].name,Capa[i].tele,Capa[i].add,Capa[i].group); //����д���ļ���
		i++;
	}
	fclose(pFile);
	return 1;
}

int AddressList()
{
    puts("    --------------------------------------------------------");
	puts("");
	puts("                      cxh���ֻ�ͨѶ¼                       ");
	puts("");
	puts("    --------------------------------------------------------");
	ShowAll(Capa,TotalNum);
}

int Menu()                 //�û��˵�����
{
	printf("       ��         �����б����£�       ��\n");
	printf("       ��   1.����Ⱥ���ѯ��ϵ����Ϣ�� ��\n");
	printf("       ��   2.����������ѯ��ϵ����Ϣ�� ��\n");
	printf("       ��   3.����µ���ϵ����Ϣ��     ��\n");
	printf("       ��   4.ɾ��ָ������ϵ����Ϣ��   ��\n");
	printf("       ��   5.ɾ��ȫ������ϵ����Ϣ��   ��\n");
	printf("       ��   6.��ѯȫ����ϵ����Ϣ��     ��\n");
	printf("       ��   7.�����ʾȫ����ϵ����Ϣ�� ��\n");
	printf("       ��   0.�˳���ϵͳ�������ļ���   ��\n");
	printf("                ������ѡ����:");
	char go[100];
	gets(go);
	int i = 0;
	while(go[i]==' ')
		i++;
	if(go[i]>='0'&&go[i]<='8')
		return go[i]-'0';
	else
	{
		fflush(stdin);
		printf("    ��ʾ������ָ��Ϸ������������룡\n");
		Menu();
	}
}

void ReMenu()                             //������Ϊ����ʱ�Ľ��溯��
{
	fflush(stdin);
	switch(Menu())                        //���ò˵������������û��������ѡ�����
	{
	case 1:
		fflush(stdin);
		GroupRes();                       //��Ⱥ���ѯ
		break;
	case 2:
		fflush(stdin);
		NameRes();                        //��������ѯ
		break;
	case 3:
		fflush(stdin);
		Add();                            //�����ϵ��
		break;
	case 4:                               //ɾ��һ����ϵ��
		fflush(stdin);
		DelectOne();
		break;
	case 5:                               //ɾ��ȫ����ϵ��
		fflush(stdin);
		DelectAll();
		break;
	case 6:                               //��ѯȫ����ϵ��
		fflush(stdin);
		ShowAll(Capa,TotalNum);
		break;
	case 7:
		fflush(stdin);
		ShowOne(Capa,TotalNum);
	case 0:                                  //�˳�������
		Save("Contact.txt");
		exit(0);
		break;
	default:
		fflush(stdin);
		printf("    ��ʾ������ָ��Ϸ������������룡\n");
		Menu();
	}
}

int main()
{
	Get("Contact.txt");
	Order(Capa,TotalNum);
	AddressList();
	switch(Menu())
	{
	case 1:                             //��Ⱥ�����
		fflush(stdin);
		GroupRes();
		break;
	case 2:                             //��������ѯ
		fflush(stdin);
		NameRes();
		break;
	case 3:                             //�����ϵ��
		fflush(stdin);
		Add();
		break;
	case 4:                             // ɾ��ָ����ϵ��
		fflush(stdin);
		DelectOne();
		break;
	case 5:                             //ɾ��ȫ����ϵ��
		fflush(stdin);
		DelectAll();
		break;
	case 6:
		fflush(stdin);
		ShowAll(Capa,TotalNum);         //��ʾȫ����ϵ��
		break;
	case 7:                             //�����ʾȫ����ϵ��
		fflush(stdin);
		ShowOne(Capa,TotalNum);
	case 0:                             //�˳�������
		Save("Contact.txt");
		exit(0);
		break;
	}
}
