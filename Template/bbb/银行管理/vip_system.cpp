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
}branch_account;//分帐号表的结点，包括账号和余额，余额在函数3中进行修改
typedef struct {
	branch_account* a;
	int length;
}SqList;//分帐号表，包括一个分帐号结点类型的数组和数组长度
typedef struct LNode {
	long long int account;//账号
	char name[20];//姓名
	long long int telephone;//联系方式
	long long int ID;//身份证号
	double money;//余额
	SqList branch;//分帐号表
	int VIP;//1表示是VIP，0表示不是VIP 
	struct LNode* next;//指向下一结点的指针
}LNode, * LinkList;//用户信息链表
void InitList(LinkList& L) {
	L = (LinkList)malloc(sizeof(LNode));
	if (!L)
		exit(OVERFLOW);
	L->next = NULL;
}//链表初始化
void Create(LinkList& L) {
	LinkList p;
	int flag = 1;
	cout << "请输入客户账号、姓名、联系方式、身份证号等信息。" << endl;
	p = (LinkList)malloc(sizeof(LNode));
	if (!p)
		exit(OVERFLOW);
	p->branch.length = 0;
	cout << "请输入16位或19位账号" << endl;
	cin >> p->account;
	cout << "请输入姓名" << endl;
	cin >> p->name;
	cout << "请输入联系方式（11位号码）" << endl;
	cin >> p->telephone;
	cout << "请输入18位身份证号" << endl;
	cin >> p->ID;
	cout<<"请选择用户是否是VIP，是请输入1,否则请输入0";
	cin >> p->VIP;
	//cin >> p->account >> p->name >> p->telephone >> p->ID >> flag;
	cout << "若客户开设分帐户，请输入1，否则输入0" << endl;
	cin >> flag;
	if (flag) {
		cout << "请输入分帐户数目" << endl;
		cin >> p->branch.length;
		p->branch.a = (branch_account*)malloc(sizeof(branch_account)*MAXSIZE);
		for (int i = 0; i < p->branch.length; i++) {
			cout << "请输入分帐户" << i+1 << "的账号";
			cin >> p->branch.a[i].account;
			p->branch.a[i].money = 0;
		}
	}//根据flag判断是否有分帐户，建立分帐户
	p->money = 0;
	p->next = L->next;
	L->next = p;
}//建立一个客户信息系统
void insert(LinkList& L) {
	LinkList s = L->next;
	int flag;
	s = (LinkList)malloc(sizeof(LNode));
	if (!s)
		exit(OVERFLOW);
	s->branch.length = 0;
	cout << "请输入客户账号、姓名、联系方式、身份证号等信息。" << endl;
	cout << "请输入16位或19位账号" << endl;
	cin >> s->account;
	cout << "请输入姓名" << endl;
	cin >> s->name;
	cout << "请输入联系方式（11位号码）" << endl;
	cin >> s->telephone;
	cout << "请输入18位身份证号" << endl;
	cin >> s->ID;
	cout<<"请选择用户是否是VIP，是请输入1,否则请输入0";
	cin >> s->VIP;
	cout << "若客户开设分帐户，请输入1，否则输入0" << endl;
	cin >> flag;
	if (flag) {
		cout << "请输入分帐户数目" << endl;
		cin >> s->branch.length;
		s->branch.a = (branch_account*)malloc(sizeof(branch_account) * MAXSIZE);
		for (int i = 0; i < s->branch.length; i++) {
			cout << "请输入分帐户" << i+1 << "的账号";
			cin >> s->branch.a[i].account;
			s->branch.a[i].money = 0;
		}
	}
	s->money = 0;
	s->next = L->next;
	L->next = s;
}//依次插入客户信息，与创建基本类似
void DestroyList (LinkList& L) {
	LinkList p;
	while (L) {
		p = L;
		L = L->next;
		free(p);
	}
}//销毁链表，用于文件操作中信息存盘后内存的清空
void DeleteElem(LinkList& L, int i) {
	LinkList p = L;
	LinkList q;
	int j;
	for (j = 0; p->next && j < i - 1; j++)
		p = p->next;
	if (!(p->next) || j > i - 1)
		cout << "删除失败" << endl;
	q = p->next;
	p->next = q->next;
	free(q);
}//按序号对客户信息进行删除
void DeleteName(LinkList& L) {
	LinkList p = L->next;
	LinkList q;
	string name;
	int count=1,flag=0;
	cout << "请输入你想删除的客户的姓名" << endl;
	cin >> name;
	if (!p)
		cout << "系统中没有任何客户信息，查找失败" << endl;
	else {
		while (p!= NULL) {
			if (name == p->name) {
				flag = 1;
				DeleteElem(L, count);
				cout << name << "客户删除成功" << endl;
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
		//cout << "删除失败" << endl;
}//按姓名对客户信息进行删除
void DeleteAccount(LinkList& L) {
	LinkList p = L->next;
	LinkList q;
	int account;
	int count = 1, flag = 0;
	cout << "请输入你想删除的客户的账号" << endl;
	cin >> account;
	if (!p)
		cout << "系统中没有任何客户信息，查找失败" << endl;
	else {
		while (p != NULL) {
			if (account == p->account) {
				flag = 1;
				DeleteElem(L, count);
				cout << "删除成功" << endl;
				break;
			}
			else {
				p = p->next;
				count++;
			}
		}
	}
	//if (!flag)
		//cout << "删除失败" << endl;
}//按账号对客户信息进行删除
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
}//对客户信息按照账号顺序进行排序
void printList(LinkList L) {
	LinkList p = L->next;
	int n = 1;
	cout << endl << "    --------------------------------------------------------------------------------------------------------"<< endl;
	cout << "            账户                 姓名         联系方式           身份证号               分账号" << endl;
	cout << "    --------------------------------------------------------------------------------------------------------" << endl;
	if (p==NULL)
		cout << "系统中没有任何信息" << endl;
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
				cout << "                无" << endl;
			p = p->next;
			n++;	
		}
	}
	cout<< "    --------------------------------------------------------------------------------------------------------" << endl;
}//输出所有用户的信息
void SearchName(LinkList L) {
	int flag = 0;
	LinkList p = L->next;
	int count = 1;
	string name;
	cout << "请输入你想查找的客户的姓名" << endl;
	cin >> name;
	if (p == NULL)
		cout << "系统中没有任何客户信息，查找失败" << endl;
	else {
		while (p) {
			if (name == p->name) {
				flag = 1;
				cout << "要查找的是第" << count << "位客户" << endl;
				cout<< "账号  "<<p->account << "  姓名  " << p->name << "  联系方式  " << p->telephone << "  身份证号  " << p->ID << endl;
			}
			p = p->next;
			count++;
		}
	}
	if (!flag)
		cout << "查找失败" << endl;
}//按照姓名进行查找
void Revise(LinkList &L){
	LinkList p=L->next;
	int flag = 0;
	string name;
	char name1[20];
	long long int telephone,telephone1;
	long long int account,account1;
	cout<<"请输入你要修改的项目"<<endl;
	cout<<"1.修改姓名"<<endl;
	cout<<"2.修改联系方式"<<endl;
	cout<<"3.修改账号"<<endl;
	int way;
	cin>>way;
	switch(way){
		case 1:
			cout<<"请输入原始姓名" <<endl;
			cin>>name;
			if(p==NULL)
				cout<< "系统中没有任何客户信息" << endl;
			else{
				while(p){
					if(name==p->name){
						flag=1;
						cout<<"请输入你要修改的姓名"<<endl;
						cin>>name1;
						strcpy(p->name,name1);
						break;
					}
					p=p->next;
				}
			}
			if(!flag)
				cout<<"系统中没有该客户"<<endl;
			break;
		case 2:
			p=L->next;
			cout<<"请输入原始联系方式"<<endl;
			cin>>telephone;
			if(p==NULL)
				cout<< "系统中没有任何客户信息" << endl;
			else{
				while(p){
					if(telephone==p->telephone){
						flag=1;
						cout<<"请输入你要修改的联系方式"<<endl;
						cin>>telephone1;
						p->telephone=telephone1;
						break;
					}
					p=p->next;
				}
			}
			if(!flag)
				cout<<"系统中没有该客户"<<endl;
			break;
		case 3:
			p=L->next;
			cout<<"请输入原始账号"<<endl;
			cin>>account;
			if(p==NULL)
				cout<< "系统中没有任何客户信息" << endl;
			else{
				while(p){
					for(int i=0;i<p->branch.length;i++){
						if(account==p->account){
							flag=1;
							cout<<"请输入你要修改的账号"<<endl;
							cin>>account1;
							p->account=account1;
							break;
						}
						else
							if(account==p->branch.a[i].account){
								flag=1;
								cout<<"请输入你要修改的账号"<<endl;
								cin>>account1;
								p->branch.a[i].account=account1;
								break;
							}
					} 
					p=p->next;	
				}
			}
			if(!flag)
				cout<<"系统中没有该客户"<<endl;
			break;
		default:
			cout<<"没有该功能"<<endl;			
	}
}
void SearchAccount(LinkList L) {
	int flag = 0;
	LinkList p = L->next;
	int count = 1;
	int account;
	cout << "请输入你想查找的客户的账号" << endl;
	cin >> account;
	if (p == NULL)
		cout << "系统中没有任何客户信息，查找失败" << endl;
	else {
		while (p) {
			if (account == p->account) {
				flag = 1;
				cout << "要查找的是第" << count << "位客户" << endl;
				cout << "账号 " << p->account << "姓名 " << p->name << "联系方式 " << p->telephone << "身份证号 " << p->ID << endl;
			}
			p = p->next;
			count++;
		}
	}
	if (!flag)
		cout << "查找失败" << endl;
}//按照账号进行查找
void mainwork_7(LinkList& L);
void shixian(LinkList&L);
void mainwork_2(LinkList &L) {
	int flag = 0;
	int menu;
	char temp;
	//system("color lf");
	cout << "                ***************欢迎使用客户信息系统***************" << endl;
	cout << "           **                  " << "1.客户信息系统的建立" << "                **                  " << endl;
	cout << "           **                  " << "2.插入客户信息" << "                      **                  " << endl;
	cout << "           **                  " << "3.查询客户信息" << "                      **                  " << endl;
	cout << "           **                  " << "4.删除客户信息" << "                      **                  " << endl;
	cout << "           **                  " << "5.显示客户信息系统记录" << "              **                  " << endl;
	cout << "           **                  " << "6.修改客户信息"<< "                       **                  " << endl;
	cout << "           **                  " << "7.进行文件存取操作" << "                  **                  " << endl;
	cout << "           **                  " << "0.退出信息系统" << "                      **                  " << endl;
	cout << "                **************************************************" << endl;
	cout << "请选择0-7" << endl;
	cin >> menu;
	while (menu != 0) {
		switch (menu)
		{
			case 1:
				if (flag == 0) {
					Create(L);
					cout << "建立系统" << endl;
					printList(L);
					flag = 1;
				}
				else
					cout << "已建立系统，请选择其他功能" << endl;
				break;
			case 2:
				if (flag == 1||L->next) {
				insert(L);
				cout << "插入后" << endl;
				sort(L);
				printList(L);
				}
				else
					cout << "还未建立系统，请先建立"<<endl;
				break;
			case 3:
				int way;
				if (L!= NULL) {
					if (flag||L->next) {
						cout << "选择查找方式" << endl;
						cout << "按姓名请输入1，按账号请输入2" << endl;
						cin >> way;
						if (way == 1)
							SearchName(L);
						else
							SearchAccount(L);

					}
				}
				else
					cout << "系统中没有任何信息" << endl;
				break;
			case 4:
				if (L!= NULL) {
					if (flag||L->next) {
						cout << "选择删除方式" << endl;
						cout << "按姓名请输入1，按账号请输入2" << endl;
						cin >> way;
						if (way == 1)
							DeleteName(L);
						else
							DeleteAccount(L);

					}
				}
				else
					cout << "系统中没有任何信息" << endl;
				break;
			case 5:
				cout << "当前系统信息如下" << endl;
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
				cout << "没有此功能,请重新输入" << endl;
		}
		cout << "选择功能：";
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
}//写入文件
void WriteFile(char* fname, LinkList L) {
	FILE* fp;
	fp = fopen(fname, "wb");
	if (fp == NULL) {
		cout << "文件产生失败" << endl;
	}
	write(fp, L);
	fclose(fp);
}//写入文件
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
}//读出文件
void ReadFile(char* fname, LinkList &L) {
	FILE* fp;
	int b;
	fp = fopen(fname, "rb");
	if (fp == NULL) {
		cout << "文件打开失败" << endl;
	}
	b = sizeof(struct LNode);
	L = (LinkList)malloc(b);
	if (!L)
		exit(OVERFLOW);
	L->next = NULL;
	//fread(L, b, 1, fp);
	read(fp, L, b);
	fclose(fp);
}//读出文件
void mainwork_7(LinkList &L) {
	int menu;
	cout << "****************文件操作******************" << endl;
	cout << "             1.客户信息存盘                           " << endl;
	cout << "             2.从文件恢复内存的客户信息               " << endl;
	cout << "             0.退出                                   " << endl;
	cout << "******************************************" << endl;
	cout << "选择功能" << endl;
	cin >> menu;
	char* fname = new char[20];
	//fname = "customer.txt";
	strcpy(fname, "customer.dat");
	while (menu != 0) {
		switch (menu)
		{
		case 1:
			cout << "存储信息到文件customer.dat中" << endl;
			WriteFile(fname, L);
			DestroyList(L);
			cout << "数据文件customer.dat建立成功";
			cout << "内存已清空" << endl;
			break;
		case 2:
			cout << "准备将数据文件customer.dat恢复到内存中" << endl;
			LinkList L;
			ReadFile(fname, L);
			cout << "数据文件customer.dat已经读入内存" << endl;
			cout << "是否继续对客户信息进行操作？继续操作请按3,否则请选择（0-2）中的操作" << endl;
			int way;
			cin >> way;
			if (way == 3)
				mainwork_2(L);
			break;
		case 0:
			exit(0);
		default:
			cout << "没有此功能,请重新输入" << endl;
		}
		cout << "选择功能：";
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
}//按资产划分
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
	cout<<"请输入文件名"<<endl;
	cin>>filename1;
	strcpy(filename, filename1);
	WriteFile(filename,LOW);
	cout<<"资产低于十万的客户信息为"<<endl;
	ReadFile(filename,LOW);
	WriteFile(filename,M);
	cout<<"资产高于十万低于一百万的客户资料为"<<endl;
	ReadFile(filename,M);
	WriteFile(filename,H);
	cout<<"资产高于一百万的客户信息为"<<endl;
	ReadFile(filename,H);
	LinkList Y=(LinkList)malloc(sizeof(LNode));
	LinkList N=(LinkList)malloc(sizeof(LNode));
	VClassify(L,Y,N);
	WriteFile(filename,Y);
	cout<<"VIP客户信息为"<<endl;
	ReadFile(filename,Y);
	WriteFile(filename,N);
	cout<<"不是VIP客户信息为"<<endl;
	ReadFile(filename,N);
}

int main() {
	LinkList L;
	InitList(L);
	mainwork_2(L);  //363行 
	//mainwork_7(L);
}
