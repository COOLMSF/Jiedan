#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#define OK 1
#define ERROR 0
#define OVERFLOW -2
using namespace std;
typedef int Status;
#define MAXSIZE 50000
//#define _CRT_SECURE_NO_WARNINGS
static int number;
typedef struct branch_account {
	long long int account;
	double money;
}branch_account;//���ʺű�Ľ�㣬�����˺ź�������ں���3�н����޸�
typedef struct {
	branch_account* a;
	int length;
}SqList;//���ʺű�����һ�����ʺŽ�����͵���������鳤��
typedef struct LNode {
	long long int account;//�˺�
	char name[20];//����
	long long int telephone;//��ϵ��ʽ
	long long int ID;//���֤��
	double money;//���
	SqList branch;//���ʺű�
	int VIP;//1��ʾ��VIP��0��ʾ����VIP 
	struct LNode* next;//ָ����һ����ָ��
}LNode, * LinkList;//�û���Ϣ����
void InitList(LinkList& L) {
	L = (LinkList)malloc(sizeof(LNode));
	if (!L)
		exit(OVERFLOW);
	L->next = NULL;
}//�����ʼ��
void Create(LinkList& L) {
	LinkList p;
	int flag = 1;
	cout << "������ͻ��˺š���������ϵ��ʽ�����֤�ŵ���Ϣ��" << endl;
	p = (LinkList)malloc(sizeof(LNode));
	if (!p)
		exit(OVERFLOW);
	p->branch.length = 0;
	cout << "������16λ��19λ�˺�" << endl;
	cin >> p->account;
	cout << "����������" << endl;
	cin >> p->name;
	cout << "��������ϵ��ʽ��11λ���룩" << endl;
	cin >> p->telephone;
	cout << "������18λ���֤��" << endl;
	cin >> p->ID;
	cout<<"��ѡ���û��Ƿ���VIP����������1,����������0";
	cin >> p->VIP;
	//cin >> p->account >> p->name >> p->telephone >> p->ID >> flag;
	cout << "���ͻ�������ʻ���������1����������0" << endl;
	cin >> flag;
	if (flag) {
		cout << "��������ʻ���Ŀ" << endl;
		cin >> p->branch.length;
		p->branch.a = (branch_account*)malloc(sizeof(branch_account)*MAXSIZE);
		for (int i = 0; i < p->branch.length; i++) {
			cout << "��������ʻ�" << i+1 << "���˺�";
			cin >> p->branch.a[i].account;
			p->branch.a[i].money = 0;
		}
	}//����flag�ж��Ƿ��з��ʻ����������ʻ�
	p->money = 0;
	p->next = L->next;
	L->next = p;
}//����һ���ͻ���Ϣϵͳ
void insert(LinkList& L) {
	LinkList s = L->next;
	int flag;
	s = (LinkList)malloc(sizeof(LNode));
	if (!s)
		exit(OVERFLOW);
	s->branch.length = 0;
	cout << "������ͻ��˺š���������ϵ��ʽ�����֤�ŵ���Ϣ��" << endl;
	cout << "������16λ��19λ�˺�" << endl;
	cin >> s->account;
	cout << "����������" << endl;
	cin >> s->name;
	cout << "��������ϵ��ʽ��11λ���룩" << endl;
	cin >> s->telephone;
	cout << "������18λ���֤��" << endl;
	cin >> s->ID;
	cout<<"��ѡ���û��Ƿ���VIP����������1,����������0";
	cin >> s->VIP;
	cout << "���ͻ�������ʻ���������1����������0" << endl;
	cin >> flag;
	if (flag) {
		cout << "��������ʻ���Ŀ" << endl;
		cin >> s->branch.length;
		s->branch.a = (branch_account*)malloc(sizeof(branch_account) * MAXSIZE);
		for (int i = 0; i < s->branch.length; i++) {
			cout << "��������ʻ�" << i+1 << "���˺�";
			cin >> s->branch.a[i].account;
			s->branch.a[i].money = 0;
		}
	}
	s->money = 0;
	s->next = L->next;
	L->next = s;
}//���β���ͻ���Ϣ���봴����������
void DestroyList (LinkList& L) {
	LinkList p;
	while (L) {
		p = L;
		L = L->next;
		free(p);
	}
}//�������������ļ���������Ϣ���̺��ڴ�����
void DeleteElem(LinkList& L, int i) {
	LinkList p = L;
	LinkList q;
	int j;
	for (j = 0; p->next && j < i - 1; j++)
		p = p->next;
	if (!(p->next) || j > i - 1)
		cout << "ɾ��ʧ��" << endl;
	q = p->next;
	p->next = q->next;
	free(q);
}//����ŶԿͻ���Ϣ����ɾ��
void DeleteName(LinkList& L) {
	LinkList p = L->next;
	LinkList q;
	string name;
	int count=1,flag=0;
	cout << "����������ɾ���Ŀͻ�������" << endl;
	cin >> name;
	if (!p)
		cout << "ϵͳ��û���κοͻ���Ϣ������ʧ��" << endl;
	else {
		while (p!= NULL) {
			if (name == p->name) {
				flag = 1;
				DeleteElem(L, count);
				cout << name << "�ͻ�ɾ���ɹ�" << endl;
				break;
				//p = p->next;
				
			}
			else {
				p = p->next;
				count++;
			}	
		}
	}
	//if (!flag)
		//cout << "ɾ��ʧ��" << endl;
}//�������Կͻ���Ϣ����ɾ��
void DeleteAccount(LinkList& L) {
	LinkList p = L->next;
	LinkList q;
	int account;
	int count = 1, flag = 0;
	cout << "����������ɾ���Ŀͻ����˺�" << endl;
	cin >> account;
	if (!p)
		cout << "ϵͳ��û���κοͻ���Ϣ������ʧ��" << endl;
	else {
		while (p != NULL) {
			if (account == p->account) {
				flag = 1;
				DeleteElem(L, count);
				cout << "ɾ���ɹ�" << endl;
				break;
			}
			else {
				p = p->next;
				count++;
			}
		}
	}
	//if (!flag)
		//cout << "ɾ��ʧ��" << endl;
}//���˺ŶԿͻ���Ϣ����ɾ��
void sort(LinkList& L) {
	LinkList p;
	LinkList q;
	LinkList tail = NULL;
	while (L->next->next!= tail) {
		p = L;
		q = L->next;
		while (q->next != tail) {
			if (q->account > q->next->account) {
				p->next = q->next;
				q->next = q->next->next;
				p->next->next = q;
				q = p->next;
			}
			p = p->next;
			q = q->next;
		}
		tail = q;
	}
}//�Կͻ���Ϣ�����˺�˳���������
void printList(LinkList L) {
	LinkList p = L->next;
	int n = 1;
	cout << endl << "    --------------------------------------------------------------------------------------------------------"<< endl;
	cout << "            �˻�                 ����         ��ϵ��ʽ           ���֤��               ���˺�" << endl;
	cout << "    --------------------------------------------------------------------------------------------------------" << endl;
	if (p==NULL)
		cout << "ϵͳ��û���κ���Ϣ" << endl;
	else {
		while (p) {
			cout << n << "   " << p->account << "        " << p->name << "        " << p->telephone << "        " << p->ID;
			if (p->branch.length != 0) {
				cout << "        " << p->branch.a[0].account << endl;
				for (int i = 1; i < p->branch.length; i++) {
					cout<<"                                                                                       "<< p->branch.a[i].account << endl;
				}
			}
			else
				cout << "                ��" << endl;
			p = p->next;
			n++;	
		}
	}
	cout<< "    --------------------------------------------------------------------------------------------------------" << endl;
}//��������û�����Ϣ
void SearchName(LinkList L) {
	int flag = 0;
	LinkList p = L->next;
	int count = 1;
	string name;
	cout << "������������ҵĿͻ�������" << endl;
	cin >> name;
	if (p == NULL)
		cout << "ϵͳ��û���κοͻ���Ϣ������ʧ��" << endl;
	else {
		while (p) {
			if (name == p->name) {
				flag = 1;
				cout << "Ҫ���ҵ��ǵ�" << count << "λ�ͻ�" << endl;
				cout<< "�˺�  "<<p->account << "  ����  " << p->name << "  ��ϵ��ʽ  " << p->telephone << "  ���֤��  " << p->ID << endl;
			}
			p = p->next;
			count++;
		}
	}
	if (!flag)
		cout << "����ʧ��" << endl;
}//�����������в���
void Revise(LinkList &L){
	LinkList p=L->next;
	int flag = 0;
	string name;
	char name1[20];
	long long int telephone,telephone1;
	long long int account,account1;
	cout<<"��������Ҫ�޸ĵ���Ŀ"<<endl;
	cout<<"1.�޸�����"<<endl;
	cout<<"2.�޸���ϵ��ʽ"<<endl;
	cout<<"3.�޸��˺�"<<endl;
	int way;
	cin>>way;
	switch(way){
		case 1:
			cout<<"������ԭʼ����" <<endl;
			cin>>name;
			if(p==NULL)
				cout<< "ϵͳ��û���κοͻ���Ϣ" << endl;
			else{
				while(p){
					if(name==p->name){
						flag=1;
						cout<<"��������Ҫ�޸ĵ�����"<<endl;
						cin>>name1;
						strcpy(p->name,name1);
						break;
					}
					p=p->next;
				}
			}
			if(!flag)
				cout<<"ϵͳ��û�иÿͻ�"<<endl;
			break;
		case 2:
			p=L->next;
			cout<<"������ԭʼ��ϵ��ʽ"<<endl;
			cin>>telephone;
			if(p==NULL)
				cout<< "ϵͳ��û���κοͻ���Ϣ" << endl;
			else{
				while(p){
					if(telephone==p->telephone){
						flag=1;
						cout<<"��������Ҫ�޸ĵ���ϵ��ʽ"<<endl;
						cin>>telephone1;
						p->telephone=telephone1;
						break;
					}
					p=p->next;
				}
			}
			if(!flag)
				cout<<"ϵͳ��û�иÿͻ�"<<endl;
			break;
		case 3:
			p=L->next;
			cout<<"������ԭʼ�˺�"<<endl;
			cin>>account;
			if(p==NULL)
				cout<< "ϵͳ��û���κοͻ���Ϣ" << endl;
			else{
				while(p){
					for(int i=0;i<p->branch.length;i++){
						if(account==p->account){
							flag=1;
							cout<<"��������Ҫ�޸ĵ��˺�"<<endl;
							cin>>account1;
							p->account=account1;
							break;
						}
						else
							if(account==p->branch.a[i].account){
								flag=1;
								cout<<"��������Ҫ�޸ĵ��˺�"<<endl;
								cin>>account1;
								p->branch.a[i].account=account1;
								break;
							}
					} 
					p=p->next;	
				}
			}
			if(!flag)
				cout<<"ϵͳ��û�иÿͻ�"<<endl;
			break;
		default:
			cout<<"û�иù���"<<endl;			
	}
}
void SearchAccount(LinkList L) {
	int flag = 0;
	LinkList p = L->next;
	int count = 1;
	int account;
	cout << "������������ҵĿͻ����˺�" << endl;
	cin >> account;
	if (p == NULL)
		cout << "ϵͳ��û���κοͻ���Ϣ������ʧ��" << endl;
	else {
		while (p) {
			if (account == p->account) {
				flag = 1;
				cout << "Ҫ���ҵ��ǵ�" << count << "λ�ͻ�" << endl;
				cout << "�˺� " << p->account << "���� " << p->name << "��ϵ��ʽ " << p->telephone << "���֤�� " << p->ID << endl;
			}
			p = p->next;
			count++;
		}
	}
	if (!flag)
		cout << "����ʧ��" << endl;
}//�����˺Ž��в���
void mainwork_7(LinkList& L);
void shixian(LinkList&L);
void mainwork_2(LinkList &L) {
	int flag = 0;
	int menu;
	char temp;
	//system("color lf");
	cout << "                ***************��ӭʹ�ÿͻ���Ϣϵͳ***************" << endl;
	cout << "           **                  " << "1.�ͻ���Ϣϵͳ�Ľ���" << "                **                  " << endl;
	cout << "           **                  " << "2.����ͻ���Ϣ" << "                      **                  " << endl;
	cout << "           **                  " << "3.��ѯ�ͻ���Ϣ" << "                      **                  " << endl;
	cout << "           **                  " << "4.ɾ���ͻ���Ϣ" << "                      **                  " << endl;
	cout << "           **                  " << "5.��ʾ�ͻ���Ϣϵͳ��¼" << "              **                  " << endl;
	cout << "           **                  " << "6.�޸Ŀͻ���Ϣ"<< "                       **                  " << endl;
	cout << "           **                  " << "7.�����ļ���ȡ����" << "                  **                  " << endl;
	cout << "           **                  " << "0.�˳���Ϣϵͳ" << "                      **                  " << endl;
	cout << "                **************************************************" << endl;
	cout << "��ѡ��0-7" << endl;
	cin >> menu;
	while (menu != 0) {
		switch (menu)
		{
			case 1:
				if (flag == 0) {
					Create(L);
					cout << "����ϵͳ" << endl;
					printList(L);
					flag = 1;
				}
				else
					cout << "�ѽ���ϵͳ����ѡ����������" << endl;
				break;
			case 2:
				if (flag == 1||L->next) {
				insert(L);
				cout << "�����" << endl;
				sort(L);
				printList(L);
				}
				else
					cout << "��δ����ϵͳ�����Ƚ���"<<endl;
				break;
			case 3:
				int way;
				if (L!= NULL) {
					if (flag||L->next) {
						cout << "ѡ����ҷ�ʽ" << endl;
						cout << "������������1�����˺�������2" << endl;
						cin >> way;
						if (way == 1)
							SearchName(L);
						else
							SearchAccount(L);

					}
				}
				else
					cout << "ϵͳ��û���κ���Ϣ" << endl;
				break;
			case 4:
				if (L!= NULL) {
					if (flag||L->next) {
						cout << "ѡ��ɾ����ʽ" << endl;
						cout << "������������1�����˺�������2" << endl;
						cin >> way;
						if (way == 1)
							DeleteName(L);
						else
							DeleteAccount(L);

					}
				}
				else
					cout << "ϵͳ��û���κ���Ϣ" << endl;
				break;
			case 5:
				cout << "��ǰϵͳ��Ϣ����" << endl;
				printList(L);
				break;
			case 6:
				Revise(L); 
				break;
			case 7:
				mainwork_7(L);
				break;
			case 8:
				shixian(L);
				break;
			case 0:
				exit(0);
			default:
				cout << "û�д˹���,����������" << endl;
		}
		cout << "ѡ���ܣ�";
		cin >> menu;
	}
}
static void write(FILE* fp, LinkList L) {
	LinkList p = L->next;
	while (p != NULL) {
		//fwrite(&p, sizeof(struct LNode), 1, fp);
		fprintf(fp, "%lld %s %lld %lld %lf %d %d ", p->account, p->name, p->telephone, p->ID, p->money, p->VIP, p->branch.length);
		for (int i = 0; i < p->branch.length; i++) {
			fprintf(fp, "%lld %lf ", p->branch.a[i].account,p->branch.a[i].money);
		}
		fprintf(fp, "\n");
		p = p->next;
	}
}//д���ļ�
void WriteFile(char* fname, LinkList L) {
	FILE* fp;
	fp = fopen(fname, "wb");
	if (fp == NULL) {
		cout << "�ļ�����ʧ��" << endl;
	}
	write(fp, L);
	fclose(fp);
}//д���ļ�
static void read(FILE* fp, LinkList &L, int b) {
	/*while (L->next != NULL) {
		LinkList p = (LinkList)malloc(b);
		//fread(&p, b, 1, fp);
		fscanf(fp, "%lld %s %lld %lld %lf ", &p->account, &p->name, &p->telephone, &p->ID, &p->money);
		for (int i = 0; i < p->branch.length; i++) {
			fscanf(fp, "%lld %lf", &p->branch.a[i].account, &p->branch.a[i].money);
		}
		p = p->next;
	}*/
	LinkList tail=L;
	while(!feof(fp)) {
		LinkList p = (LinkList)malloc(b);
		//fread(&p, b, 1, fp);
		fscanf(fp, "%lld%s%lld%lld%lf%d%d", &p->account, &p->name, &p->telephone, &p->ID, &p->money, &p->VIP, &p->branch.length);
		if (p->branch.length != 0) {
			p->branch.a = (branch_account*)malloc(sizeof(branch_account) * MAXSIZE);
			for (int i = 0; i < p->branch.length; i++) {
				fscanf(fp, "%lld%lf", &p->branch.a[i].account, &p->branch.a[i].money);
			}
		}
		fscanf(fp, " ");
		/*if (L == NULL) {
			L = p;
			p->next = NULL;
		}
		else {
			q = L;
			while (q->next != NULL)
				q = q->next;
		}
		q->next = p;
		p->next = NULL;*/
		tail->next = p;
		tail = p;
		tail->next = NULL;
	}
}//�����ļ�
void ReadFile(char* fname, LinkList &L) {
	FILE* fp;
	int b;
	fp = fopen(fname, "rb");
	if (fp == NULL) {
		cout << "�ļ���ʧ��" << endl;
	}
	b = sizeof(struct LNode);
	L = (LinkList)malloc(b);
	if (!L)
		exit(OVERFLOW);
	L->next = NULL;
	//fread(L, b, 1, fp);
	read(fp, L, b);
	fclose(fp);
}//�����ļ�
void mainwork_7(LinkList &L) {
	int menu;
	cout << "****************�ļ�����******************" << endl;
	cout << "             1.�ͻ���Ϣ����                           " << endl;
	cout << "             2.���ļ��ָ��ڴ�Ŀͻ���Ϣ               " << endl;
	cout << "             0.�˳�                                   " << endl;
	cout << "******************************************" << endl;
	cout << "ѡ����" << endl;
	cin >> menu;
	char* fname = new char[20];
	//fname = "customer.txt";
	strcpy(fname, "customer.dat");
	while (menu != 0) {
		switch (menu)
		{
		case 1:
			cout << "�洢��Ϣ���ļ�customer.dat��" << endl;
			WriteFile(fname, L);
			DestroyList(L);
			cout << "�����ļ�customer.dat�����ɹ�";
			cout << "�ڴ������" << endl;
			break;
		case 2:
			cout << "׼���������ļ�customer.dat�ָ����ڴ���" << endl;
			LinkList L;
			ReadFile(fname, L);
			cout << "�����ļ�customer.dat�Ѿ������ڴ�" << endl;
			cout << "�Ƿ�����Կͻ���Ϣ���в��������������밴3,������ѡ��0-2���еĲ���" << endl;
			int way;
			cin >> way;
			if (way == 3)
				mainwork_2(L);
			break;
		case 0:
			exit(0);
		default:
			cout << "û�д˹���,����������" << endl;
		}
		cout << "ѡ���ܣ�";
		cin >> menu;
	}
}
void ZClassify(LinkList &L,LinkList &H,LinkList &M,LinkList &LOW){
	while(L){
		if(L->money>=1000000)
		H->next=L;
		if(L->money>=100000&&L->money<1000000)
		M->next=L;
		if(L->money<100000)
		LOW->next=L;
		L=L->next;
	}
}//���ʲ�����
void VClassify(LinkList &L,LinkList &Y,LinkList &N){
	while(L){
		if(L->VIP)
		Y->next=L;
		else
		N->next=L;
		L=L->next;
	}
} 
void shixian(LinkList &L){
	LinkList H=(LinkList)malloc(sizeof(LNode));
	LinkList M=(LinkList)malloc(sizeof(LNode));
	LinkList LOW=(LinkList)malloc(sizeof(LNode));
	char *filename= new char[20];
	ZClassify(L,H,M,LOW);
	char *filename1= new char[20];
	cout<<"�������ļ���"<<endl;
	cin>>filename1;
	strcpy(filename, filename1);
	WriteFile(filename,LOW);
	cout<<"�ʲ�����ʮ��Ŀͻ���ϢΪ"<<endl;
	ReadFile(filename,LOW);
	WriteFile(filename,M);
	cout<<"�ʲ�����ʮ�����һ����Ŀͻ�����Ϊ"<<endl;
	ReadFile(filename,M);
	WriteFile(filename,H);
	cout<<"�ʲ�����һ����Ŀͻ���ϢΪ"<<endl;
	ReadFile(filename,H);
	LinkList Y=(LinkList)malloc(sizeof(LNode));
	LinkList N=(LinkList)malloc(sizeof(LNode));
	VClassify(L,Y,N);
	WriteFile(filename,Y);
	cout<<"VIP�ͻ���ϢΪ"<<endl;
	ReadFile(filename,Y);
	WriteFile(filename,N);
	cout<<"����VIP�ͻ���ϢΪ"<<endl;
	ReadFile(filename,N);
}

int main() {
	LinkList L;
	InitList(L);
	mainwork_2(L);  //363�� 
	//mainwork_7(L);
}
