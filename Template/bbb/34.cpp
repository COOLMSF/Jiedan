#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 1000
#include <conio.h>
//3.��ȡ��ҵ�����
//��ȡ������Ϣ���㡢�˻����ȣ��ο����ն�Ʊ��ͼ�����
//4.ҵ���ѯ�����ݲ�ͬ�ؼ��ֲ�ѯҵ����Ϣ�����ο������ѯ��
int jin;
char a;
void chuangjian();

int denglu();   //��¼�˻�
int huyan();   //�˻���֤
int miyan();  //������֤
void cunkuan(int);   //���
void qukuan(int);     //ȡ��
void daikuan(int);    //����
void lixi(int);       //��Ϣ����
void display(int);//��ѯ
//
void date();      //��ʾ����
void flag(int);    //������
void flag1();     //��ʼ����
//
int i;    //����ѭ��
struct users {
	char idnum[9];   //�˻�
	char password[7];    //����
	char name[10]; //����
	char idnumber[20];  //���֤����
	double YuE;     //���
} user[N];
char id[11], password[7];


int  main() {
	fflush(stdin);
	chuangjian();
	flag1();
	int m = denglu();
	while (m != -1) {
		flag(m);
	}
}

void flag1() {
	fflush(stdin);
	printf("\n#################################################################################\n");
	printf("\n��                               * ��ӭʹ��**����  *                               ��\n");
	printf("\n#################################################################################\n");
	printf("\n          ����������������������������������������������������������������       \n");
	printf("          ����������������������������������������������������������������         \n");
	printf("\n#################################################################################\n");
	printf("\n��                          ************���ȵ�¼*******************                ��\n");
	printf("\n#################################################################################\n");
}

void flag(int m) {
	int a;//ѡ���ܵı���
	do {
		date();
		printf("\n#################################################################################\n");
		printf("\n��                               * ��ӭʹ��  *                                 ��\n");
		printf("\n#################################################################################\n");
		printf("\n          ����������������������������������������������������������������\n");
		printf("          |��|******|��|        �� ���ҵ��       �밴 1        |��|******|��|\n");
		printf("          |��|******|��|        �� ȡ��ҵ��       �밴 2        |��|******|��|\n");
		printf("          |��|******|��|        �� ��ѯ���       �밴 3        |��|******|��|\n");
		printf("          |��|******|��|        �� ����ҵ��       �밴 4        |��|******|��|\n");
		printf("          |��|******|��|        �� ��Ϣ����       �밴 5        |��|******|��|\n");
		printf("          |��|******|��|        �� �˳�ϵͳ       �밴 6        |��|******|��|\n");
		printf("          |��|******|��|                                        |��|******|��|\n");
		printf("          ����������������������������������������������������������������\n");
		printf("\n#################################################################################\n");
		printf("\n��                          *******************************                    ��\n");
		printf("\n#################################################################################\n");
		printf("\n\n\t\t##���������ѡ��");
		fflush(stdin);
		scanf("%d", &a);
		switch (a) {
			case 1: {
				fflush(stdin);
				cunkuan(m);
				break;//���

			}
			case 2:  {

				fflush(stdin);
				qukuan(m);
				break;//ȡ��

			}
			case 3: {

				fflush(stdin);
				display(m);
				break;//��ѯҵ��
			}
			case 4: {

				fflush(stdin);
				daikuan(m);
				break;//����

			}
			case 5: {

				fflush(stdin);
				lixi(m);
				break;//��Ϣ

			}
			case 6:
				exit(0);
			default:
				printf("�������ѡ��������������ȷ��ѡ�");

		}
	} while (1);
}
//********************************************************************************************************************
//�û�����ѡ�����

//***************************************************************************
void chuangjian() { //�����û�ʵ��
	fflush(stdin);
	date();
	printf("�����봴���û�������");
	int n;
	scanf("%d", &n);
	for (i = 1; i <= n; i++) {
		printf("��������������\n");
		scanf("%s", user[i].name);
		printf("�������������֤��\n");
		scanf("%s", user[i].idnumber);
		printf("�����������˻�\n");
		scanf("%s", user[i].idnum);
		printf("����������λ������\n");
		scanf("%s", user[i].password);
		user[i].YuE = 0;
	}
}
int huyan(char *s) {
	fflush(stdin);
	for (i = 0; i < N; i++)
		if (strcmp(s, user[i].idnum ) == 0 )
			break;
	if (i < N)
		return i;
	else
		return 0;
}

int miyan(char *s, int i) {
	fflush(stdin);
	if (strcmp(s, user[i].password ) == 0)
		return 1;
	else
		return 0;
}
int denglu() {
	fflush(stdin);
	date();
	printf("�����������˻���¼��\n");
	scanf("%s", id);
	while (huyan(id) == 0) {
		printf("��������ȷ���ڱ��п����ĵ��˻���\n");
		scanf("%s", id);
	}
	int k = huyan(id);
	printf("������������λ���룺\n");
	for (i = 0; i < 6; i++) {
		password[i] = getch();
		printf("*");
	}
	while (miyan(password, k) != 1) {
		printf("�������������\n");
		printf("��������ȷ��λ���룺\n");
		for (i = 0; i < 6; i++) {
			password[i] = getch();
			printf("*");
		}
	}
	if (miyan(password, k) == 1) {
		printf("���ѳɹ���¼\n");
		return k;
	} else
		return -1;
}
void cunkuan(int m) { //���
	fflush(stdin);
	int k;
	printf("\n\n");
	printf("\t\t||================================================================||\n");
	printf("\t\t||                           *�����*                           ||\n");
	printf("\t\t||================================================================||\n");
	printf("\t\t||                                                                ||\n");
	printf("\t\t||                                                                ||\n");
	printf("\t\t||         1��200        2��400        3��600        4��800       ||\n");
	printf("\t\t||                                                                ||\n");
	printf("\t\t||                                                                ||\n");
	printf("\t\t||         5��1000        6��2000        7��4000        8��6000   ||\n");
	printf("\t\t||                                                                ||\n");
	printf("\t\t||         9���������           0���˳����                      ||\n");
	printf("\t\t||================================================================||\n");
	printf("\t\t||================================================================||\n");
	printf("\n\n\t\t\t���������ѡ��");
	scanf("%d", &k);
	while (k != 0) {
		switch (k) {
			case 1: {
				jin = 200;
				printf("�����ǰ���Ϊ��%lf\n", user[m].YuE);
				user[m].YuE += jin;
				printf("���������Ϊ��%lf,���Ѵ��ɹ���\n", user[m].YuE);
				break;
			}
			case 2: {
				jin = 400;
				printf("�����ǰ���Ϊ��%lf\n", user[m].YuE);
				user[m].YuE += jin;
				printf("���������Ϊ��%lf,���Ѵ��ɹ���\n", user[m].YuE);
				break;
			}
			case 3: {
				jin = 600;
				printf("�����ǰ���Ϊ��%lf\n", user[m].YuE);
				user[m].YuE += jin;
				printf("���������Ϊ��%lf,���Ѵ��ɹ���\n", user[m].YuE);
				break;
			}
			case 4: {
				jin = 800;
				printf("�����ǰ���Ϊ��%lf\n", user[m].YuE);
				user[m].YuE += jin;
				printf("���������Ϊ��%lf,���Ѵ��ɹ���\n", user[m].YuE);
				break;
			}
			case 5: {
				jin = 1000;
				printf("�����ǰ���Ϊ��%lf\n", user[m].YuE);
				user[m].YuE += jin;
				printf("���������Ϊ��%lf,���Ѵ��ɹ���\n", user[m].YuE);
				break;
			}
			case 6: {
				jin = 2000;
				printf("�����ǰ���Ϊ��%lf\n", user[m].YuE);
				user[m].YuE += jin;
				printf("���������Ϊ��%lf,���Ѵ��ɹ���\n", user[m].YuE);
				break;

			}
			case 7: {
				jin = 4000;
				printf("�����ǰ���Ϊ��%lf\n", user[m].YuE);
				user[m].YuE += jin;
				printf("���������Ϊ��%lf,���Ѵ��ɹ���\n", user[m].YuE);
				break;
			}
			case 8: {
				jin = 8000;
				printf("�����ǰ���Ϊ��%lf\n", user[m].YuE);
				user[m].YuE += jin;
				printf("���������Ϊ��%lf,���Ѵ��ɹ���\n", user[m].YuE);
				break;
			}
			case 9: {
				printf("���������Ĵ����%d\n", &jin);
				printf("�����ǰ���Ϊ��%lf\n", user[m].YuE);
				user[m].YuE += jin;
				printf("���������Ϊ��%lf,���Ѵ��ɹ���\n", user[m].YuE);

				break;
			}
		}
		printf("����0������ҳ�棬������������ѡ����������.\n");
		scanf("%d", &k);
	}
}
void qukuan(int m) { //ȡ��
	fflush(stdin);
	date();
	int k;
	printf("\n\n");
	printf("\t\t||================================================================||\n");
	printf("\t\t||                           *ȡ����*                           ||\n");
	printf("\t\t||================================================================||\n");
	printf("\t\t||                                                                ||\n");
	printf("\t\t||                                                                ||\n");
	printf("\t\t||         1��200        2��400        3��600        4��800       ||\n");
	printf("\t\t||                                                                ||\n");
	printf("\t\t||                                                                ||\n");
	printf("\t\t||         5��1000        6��2000        7��4000        8��6000   ||\n");
	printf("\t\t||                                                                ||\n");
	printf("\t\t||         9���������           0���˳����                      ||\n");
	printf("\t\t||================================================================||\n");
	printf("\t\t||================================================================||\n");
	printf("\n\n\t\t\t���������ѡ��");
	scanf("%d", &k);
	while (k != 0) {
		switch (k) {
			case 1: {
				jin = 200;
				if (jin <= user[m].YuE) {
					printf("��ȡ��ǰ���Ϊ��%lf\n", user[m].YuE);
					user[m].YuE -= jin;
					printf("��ȡ������Ϊ��%lf,����ȡ��ɹ���\n", user[m].YuE);
				} else {
					printf("�����˻����㣬�޷�ȡ�\n");

				}
				break;
			}
case2: {
				jin = 400;
				if (jin <= user[m].YuE) {
					printf("��ȡ��ǰ���Ϊ��%lf\n", user[m].YuE);
					user[m].YuE -= jin;
					printf("��ȡ������Ϊ��%lf,����ȡ��ɹ���\n", user[m].YuE);
				} else {
					printf("�����˻����㣬�޷�ȡ�\n");

				}
				break;
			}

			case 3: {
				jin = 600;
				if (jin <= user[m].YuE) {
					printf("��ȡ��ǰ���Ϊ��%lf\n", user[m].YuE);
					user[m].YuE -= jin;
					printf("��ȡ������Ϊ��%lf,����ȡ��ɹ���\n", user[m].YuE);
				} else {
					printf("�����˻����㣬�޷�ȡ�\n");

				}
				break;
			}
			case 4: {
				jin = 800;
				if (jin <= user[m].YuE) {
					printf("��ȡ��ǰ���Ϊ��%lf\n", user[m].YuE);
					user[m].YuE -= jin;
					printf("��ȡ������Ϊ��%lf,����ȡ��ɹ���\n", user[m].YuE);
				} else {
					printf("�����˻����㣬�޷�ȡ�\n");

				}
				break;
			}
			case 5: {
				jin = 1000;
				if (jin <= user[m].YuE) {
					printf("��ȡ��ǰ���Ϊ��%lf\n", user[m].YuE);
					user[m].YuE -= jin;
					printf("��ȡ������Ϊ��%lf,����ȡ��ɹ���\n", user[m].YuE);
				} else {
					printf("�����˻����㣬�޷�ȡ�\n");

				}
				break;
			}
			case 6: {
				jin = 2000;
				if (jin <= user[m].YuE) {
					printf("��ȡ��ǰ���Ϊ��%lf\n", user[m].YuE);
					user[m].YuE -= jin;
					printf("��ȡ������Ϊ��%lf,����ȡ��ɹ���\n", user[m].YuE);
				} else {
					printf("�����˻����㣬�޷�ȡ�\n");

				}
				break;
			}
			case 7: {
				jin = 4000;
				if (jin <= user[m].YuE) {
					printf("��ȡ��ǰ���Ϊ��%lf\n", user[m].YuE);
					user[m].YuE -= jin;
					printf("��ȡ������Ϊ��%lf,����ȡ��ɹ���\n", user[m].YuE);
				} else {
					printf("�����˻����㣬�޷�ȡ�\n");

				}
				break;

			}
			case 8: {
				jin = 6000;
				if (jin <= user[m].YuE) {
					printf("��ȡ��ǰ���Ϊ��%lf\n", user[m].YuE);
					user[m].YuE -= jin;
					printf("��ȡ������Ϊ��%lf,����ȡ��ɹ���\n", user[m].YuE);
				} else {
					printf("�����˻����㣬�޷�ȡ�\n");

				}
				break;
			}
			case 9: {
				printf("����������qu���\n");
				scanf("%d", &jin);
				if (jin <= user[m].YuE) {
					printf("��ȡ��ǰ���Ϊ��%lf\n", user[m].YuE);
					user[m].YuE -= jin;
					printf("��ȡ������Ϊ��%lf,����ȡ��ɹ���\n", user[m].YuE);
				} else {
					printf("�����˻����㣬�޷�ȡ�\n");

				}
				break;
			}

		}
		printf("����0��������ҳ�棬����������ѡ�������ȡ�\n");
		scanf("%d", &k);
	}
}
void display(int m) { //��ѯ
	fflush(stdin);
	date();
	printf("�����˻�Ϊ:%s\n", user[m].idnum);
	printf("�������֤��Ϊ:%s\n", user[m].idnumber);
	printf("�����˻����Ϊ:%lf\n", user[m].YuE);
	printf("����xingmingΪ:%s\n", user[m].name);
	printf("��#������ҳ�棡");
	scanf("%c", &a);
}
void lixi(int m) { //��Ϣ����
	date();
	printf("��#������ҳ�棡");
	scanf("%c", &a);
}
void daikuan(int m) { //����
	date();
	int k;
	printf("\n\n");
	printf("\t\t||================================================================||\n");
	printf("\t\t||                           *������*                           ||\n");
	printf("\t\t||================================================================||\n");
	printf("\t\t||                                                                ||\n");
	printf("\t\t||                                                                ||\n");
	printf("\t\t||         1��200        2��400        3��600        4��800       ||\n");
	printf("\t\t||                                                                ||\n");
	printf("\t\t||                                                                ||\n");
	printf("\t\t||         5��1000        6��2000        7��4000        8��6000   ||\n");
	printf("\t\t||               (���ϴ���������Ϊ0.1/ÿ��                      ||\n");
	printf("\t\t||             ��Ҳ��ѡ�񳬹�6000Ԫ�Ĵ�������Ϊ0.12/ÿ��)         ||\n");
	printf("\t\t||================================================================||\n");
	printf("\t\t||================================================================||\n");
	printf("\n\n\t\t\t��������Ĵ����");
	scanf("%d", &k);
	printf("��ȷ�����Ĵ�����Ϊ%d", k);
	printf("<1>ȷ�� <2>ȡ��");
	int g;
	scanf("%d", &g);
	if (g == 1) {
		printf("���Ѵ���ɹ���");
		printf("����ǰ���Ϊ��%lf", user[m].YuE);
		user[m].YuE += k;
		printf("��ȡ������Ϊ��%lf", user[m].YuE);
	} else {
		printf("���������µĴ�����");
		scanf("%d", &g);
		printf("���Ѵ���ɹ���");
		printf("����ǰ���Ϊ��%lf", user[m].YuE);
		user[m].YuE += k;
		printf("��ȡ������Ϊ��%lf", user[m].YuE);
	}
	printf("��#������ҳ�棡");
	scanf("%c", &a);
}
void date() { //��ʾ��ǰ����
	printf("��ǰ���ڣ�");
	system("date/t");
	printf("��ǰʱ�䣺");
	system("time/t");
}


