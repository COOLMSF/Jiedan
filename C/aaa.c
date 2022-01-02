#include <stdio.h>
#include <string.h>
#include <math.h>
// #include "malloc.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#define   MAX_LEN  99                	   /* �ַ�����󳤶� */
#define   USER_NUM 99                       /* �����ƶ��û����� */

typedef struct User {
	char Name[MAX_LEN];            						/* ÿ���û������� */
	char Sex[MAX_LEN];                     				/* ÿ���û����Ա� */
	char Age[MAX_LEN];	   							    /* ÿ���û������� */
	char CardNumber[MAX_LEN];	                        /* ÿ���û������֤�� */
	char PhoneNumber[MAX_LEN];							/* ÿ���û����ֻ��� */
	char Address[MAX_LEN];								/*ÿ���û��ĵ�ַ*/
} User ;

struct User Us[MAX_LEN];
int   Menu();
int   Menu1();
int   Menu2();//�����˵�
int search();
int modify();
int Delete(User Us[], int n);
void SortbyAge(User Us[], int n);
void SortbyName(User Us[], int n);
void SortbyCardNumber(User Us[], int n);
void Readfromf(User Us[]);
void WritetoF(User Us[]) ;
int Create(User Us[]);

int main() {
	int i, h, f;
	int num = 0;
	char x;
	while (1) {
		i = Menu();
		switch (i) {
			case 1:
				num = Create(Us);
				// system("cls");  //����
				break;
			case 2:
				// system("cls");  //����
				printf("\n\n\n");
				h = Menu1();
				switch (h) {
					case 1:
						search(Us);
						break;
					case 2:
						modify(Us);
						break;
					case 3:
						if (Delete(Us, num)) {
							Readfromf(Us);
						} else {
							printf("can not delete!\n");
						}
						break;
				}
				break;
			case 3:
				// system("cls");  //����
				printf("\n\n\n");
				f = Menu2();
				switch (f) {
					case 1:
						Readfromf(Us);
						break;
					case 2:
						SortbyAge(Us, num);
						Readfromf(Us);
					case 3:
						SortbyName(Us, num);
						Readfromf(Us);
					case 4:
						SortbyCardNumber(Us, num);
						Readfromf(Us);
						break;
					case 0:
						// system("cls");  //����
						printf("\n\n\n");
						printf("\t\t\t******************************************************************************\n");
						printf("\t\t\tEnd of program!\n");
						printf("\t\t\t******************************************************************************\n");
						break;
					default:
						// system("cls");  //����
						printf("\n\n\n");
						printf("\t\t\t******************************************************************************\n");
						printf("\t\t\t�������!\n");
						printf("\t\t\t******************************************************************************\n");
						break;

				}
		}
	}
	return 0;
}

int   Menu() {
	int i;
	// system("title �ƶ��û�����ϵͳ  ");
	printf("\n\n");
	printf("\t\t\t                         �ƶ��û�����ϵͳ\n");
	printf("\t\t\t******************************************************************************\n");
	printf("\t\t\t*                �� �� �� �� �� �� ϵ ͳ                                     *\n");
	printf("\t\t\t*                1.  ¼�����û���Ϣ                                          *\n");
	printf("\t\t\t*                2.  �����ƶ��û�                                            *\n");
	printf("\t\t\t*                3.  ��ʾ�����б�                                            *\n");
	printf("\t\t\t*                0.  �˳�                                                    *\n");
	printf("\t\t\t******************************************************************************\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\t\t\t*****************��ѡ��:");
	scanf("%d", &i);
	return i;

}

int Menu1() {
	int s;
	printf("\t\t\t******************************************************************************\n");
	printf("\t\t\t*                1.  �����ƶ��û�                                            *\n");
	printf("\t\t\t*                2.  �޸��ƶ��û�                                            *\n");
	printf("\t\t\t*                3.  ɾ���ƶ��û�                                            *\n");
	printf("\t\t\t******************************************************************************\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\t\t\t*****************��ѡ��:");
	scanf("%d", &s);
	return s;
}

int Menu2() {
	int q;
	printf("\t\t\t******************************************************************************\n");
	printf("\t\t\t*                1.  ��ʾ�û�����                                            *\n");
	printf("\t\t\t*                2.  �����û��������������                                  *\n");
	printf("\t\t\t*                3.  �����û���������������                                  *\n");
	printf("\t\t\t*                3.  �����û������֤��������                                *\n");
	printf("\t\t\t******************************************************************************\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\t\t\t*****************��ѡ��:");
	scanf("%d", &q);
	return q;


}

int search() {
	int n, g, k;
	char a[20] = {};
	printf("�����������û������֤�ţ�\n");
	scanf("%s", &a[20]);
	g = 0;
	do {
		n = strcmp(a[20], Us[g].CardNumber);
		g++;
	} while (n == 1 || n == -1);
	g = g - 1;
	printf("�����ҵ��û���ϢΪ��/n");
	printf("name %s/n cardnumber %s/n sex %s/n age %d/n phone %s/n ad %s/n", Us[g].Name, Us[g].CardNumber, Us[g].Sex,
	       Us[g].Age, Us[g].PhoneNumber, Us[g].Address);//��ʾ��ѯ�����û���Ϣ
	g = k;
	return k;//���ز���ֵ
}

int modify() {
	int s, z;
	int o;
	const char *a[MAX_LEN];
	const char *c;
	o = search(Us[MAX_LEN]); //�����������л�ȡ����
	printf ("ѡ��Ҫ�޸ĵ���Ϣ��");
	do {

		printf("1 CardNumber/n2 Name/n3 Age/n4 Sex/n5 Phonenumber/n6 Address/n7 finish");
		scanf ("%d", &s);
		// system("cls");
		switch (s) {
			case 1:
				printf("�������µ���Ϣ��");
				scanf("%s", &a[MAX_LEN]);
				strcpy (Us[o].CardNumber, a[MAX_LEN]);
				break;
			case 2:
				printf("�������µ���Ϣ��");
				scanf("%s", &a[MAX_LEN]);
				strcpy (Us[o].Name, a[MAX_LEN]);
				break;
			case 3:
				printf("�������µ���Ϣ��");
				scanf("%d", &a[MAX_LEN]);
				strcpy ((char *)Us[o].Age, a[MAX_LEN]);
				break;
			case 4:
				printf("�������µ���Ϣ��");
				scanf("%s", &a[MAX_LEN]);
				strcpy (Us[o].Sex, a[MAX_LEN]);
				break;
			case 5:
				printf("�������µ���Ϣ��");
				scanf("%s", &c);
				strcpy(Us[o].PhoneNumber, c);
				break;
			case 6:
				printf("�������µ���Ϣ��");
				scanf("%s", &a[MAX_LEN]);
				strcpy (Us[o].Address, a[MAX_LEN]);
				break;
		}
		// system("cls");
	} while (s == 7);
	return 0;
}

int Create( User Us[]) {
	int n;
	int m;
	int Need;
	printf("\t\t\t��������Ҫ¼����û�����\n(һ�����¼��99��)");
	scanf("%d/n", &Need) ;
	printf("\t\t\t�������û�������\n");
	for (m = 0; m < Need; m++) {
		scanf("%s/n", &Us[m].Name); //���û���Ϣ˳��洢��������
	}
	printf("\t\t\t�������û����Ա�\n");
	for (m = 0; m < Need; m++) {
		scanf("%s/n", &Us[m].Sex); //���û���Ϣ˳��洢��������
	}
	printf("\t\t\t�������û�������\n");
	for (m = 0; m < Need; m++) {
		scanf("%s/n", &Us[m].Age); //���û���Ϣ˳��洢��������
	}
	printf("\t\t\t�������û������֤����\n");
	for (m = 0; m < Need; m++) {
		scanf("%s/n", &Us[m].CardNumber); //���û���Ϣ˳��洢��������
	}
	printf("\t\t\t�������û����ֻ���\n");
	for (m = 0; m < Need; m++) {
		scanf("%s/n", &Us[m].PhoneNumber); //���û���Ϣ˳��洢��������
	}
	printf("\t\t\t�������û��ļ�ͥסַ\n");
	for (m = 0; m < Need; m++) {
		scanf("%s/n", &Us[m].Address); //���û���Ϣ˳��洢��������
	}
	WritetoF(Us) ;
	// system("cls") ;
	return 0;
}

void WritetoF(User Us[]) {
	FILE *fp;					                     /*�����ļ�ָ��*/
	fp = fopen("UserInformation.txt", "w");          /*���ı��ļ�׼��д������*/
	if ( fp == 0 ) {                				 /*����ļ���ʧ�� */
		printf( "source file error\n" );
		exit(1);
	}
	fwrite(Us, sizeof(User), MAX_LEN, fp);
	fclose(fp);
}

//¼�����û���Ϣ
int Delete(User Us[], int n) {
	int i, j;
	char a[1];
	printf("����������ɾ���û�������");
	scanf("%s", &a[0]);
	int flag = 1;
	for (i = 0; i < n && strcmp(Us[i].Name, &a[0]) != 0; i++)
		if (i == n)
			flag = 0;
		else {
			for (j = i; j < n - 1; j++)
				Us[j] = Us[j + 1];
		}
	return flag;
}

void Readfromf(User Us[]) {
	FILE *fp;                     					/*�����ļ�ָ��*/
	fp = fopen("UserInformation.txt", "r");         /*���ı��ļ�׼����������*/
	if ( fp == 0 ) {                 				/*����ļ���ʧ�� */
		printf( "source file error\n" );
		exit(1);
	}
	struct stat buf;
	int rows;										/*����һ���ļ�������¼���� */
	stat("UserInformation", &buf);
	rows = buf.st_size / sizeof(User);				/*���ļ��е�����*/
	fread((char *)Us, sizeof(User), rows, fp);			/*���ļ��ж�ȡ����*/
	fclose(fp);                    					/*�ر��ļ�*/
}

void SortbyAge(User Us[], int n) {
	int i, j, k;
	User temp;
	for (i = 0; i < n - 1; i++) {
		k = i;
		for  (j = i + 1; j < n; j++)
			if (Us[j].Age > Us[k].Age)
				k = j;
		if (k != i) {
			temp = Us[i];
			Us[i] = Us[k];
			Us[k] = temp;
		}
	}
}

void SortbyName(User Us[], int n) {
	int i, j;
	User temp;
	for (i = 0; i < n - 1; i++)
		for (j = i + 1; j < n; j++)
			if (strcmp(Us[i].Name, Us[j].Name) > 0) {
				temp = Us[i];
				Us[i] = Us[j];
				Us[j] = temp;
			}
}

void SortbyCardNumber(User Us[], int n) {
	int i, j;
	User temp;
	for (i = 0; i < n - 1; i++)
		for (j = i + 1; j < n; j++)
			if (strcmp(Us[i].CardNumber, Us[j].CardNumber) > 0) {
				temp = Us[i];
				Us[i] = Us[j];
				Us[j] = temp;
			}
}
