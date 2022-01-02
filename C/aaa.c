#include <stdio.h>
#include <string.h>
#include <math.h>
// #include "malloc.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#define   MAX_LEN  99                	   /* 字符串最大长度 */
#define   USER_NUM 99                       /* 最多的移动用户人数 */

typedef struct User {
	char Name[MAX_LEN];            						/* 每个用户的姓名 */
	char Sex[MAX_LEN];                     				/* 每个用户的性别 */
	char Age[MAX_LEN];	   							    /* 每个用户的年龄 */
	char CardNumber[MAX_LEN];	                        /* 每个用户的身份证号 */
	char PhoneNumber[MAX_LEN];							/* 每个用户的手机号 */
	char Address[MAX_LEN];								/*每个用户的地址*/
} User ;

struct User Us[MAX_LEN];
int   Menu();
int   Menu1();
int   Menu2();//创建菜单
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
				// system("cls");  //清屏
				break;
			case 2:
				// system("cls");  //清屏
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
				// system("cls");  //清屏
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
						// system("cls");  //清屏
						printf("\n\n\n");
						printf("\t\t\t******************************************************************************\n");
						printf("\t\t\tEnd of program!\n");
						printf("\t\t\t******************************************************************************\n");
						break;
					default:
						// system("cls");  //清屏
						printf("\n\n\n");
						printf("\t\t\t******************************************************************************\n");
						printf("\t\t\t输入错误!\n");
						printf("\t\t\t******************************************************************************\n");
						break;

				}
		}
	}
	return 0;
}

int   Menu() {
	int i;
	// system("title 移动用户管理系统  ");
	printf("\n\n");
	printf("\t\t\t                         移动用户管理系统\n");
	printf("\t\t\t******************************************************************************\n");
	printf("\t\t\t*                移 动 用 户 管 理 系 统                                     *\n");
	printf("\t\t\t*                1.  录入新用户信息                                          *\n");
	printf("\t\t\t*                2.  管理移动用户                                            *\n");
	printf("\t\t\t*                3.  显示数据列表                                            *\n");
	printf("\t\t\t*                0.  退出                                                    *\n");
	printf("\t\t\t******************************************************************************\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\t\t\t*****************请选择:");
	scanf("%d", &i);
	return i;

}

int Menu1() {
	int s;
	printf("\t\t\t******************************************************************************\n");
	printf("\t\t\t*                1.  查找移动用户                                            *\n");
	printf("\t\t\t*                2.  修改移动用户                                            *\n");
	printf("\t\t\t*                3.  删除移动用户                                            *\n");
	printf("\t\t\t******************************************************************************\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\t\t\t*****************请选择:");
	scanf("%d", &s);
	return s;
}

int Menu2() {
	int q;
	printf("\t\t\t******************************************************************************\n");
	printf("\t\t\t*                1.  显示用户数据                                            *\n");
	printf("\t\t\t*                2.  根据用户的年龄进行排序                                  *\n");
	printf("\t\t\t*                3.  根据用户的姓名进行排序                                  *\n");
	printf("\t\t\t*                3.  根据用户的身份证进行排序                                *\n");
	printf("\t\t\t******************************************************************************\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\t\t\t*****************请选择:");
	scanf("%d", &q);
	return q;


}

int search() {
	int n, g, k;
	char a[20] = {};
	printf("输入所查找用户的身份证号：\n");
	scanf("%s", &a[20]);
	g = 0;
	do {
		n = strcmp(a[20], Us[g].CardNumber);
		g++;
	} while (n == 1 || n == -1);
	g = g - 1;
	printf("所查找的用户信息为：/n");
	printf("name %s/n cardnumber %s/n sex %s/n age %d/n phone %s/n ad %s/n", Us[g].Name, Us[g].CardNumber, Us[g].Sex,
	       Us[g].Age, Us[g].PhoneNumber, Us[g].Address);//显示查询到的用户信息
	g = k;
	return k;//返回参数值
}

int modify() {
	int s, z;
	int o;
	const char *a[MAX_LEN];
	const char *c;
	o = search(Us[MAX_LEN]); //从搜索函数中获取参数
	printf ("选择要修改的信息：");
	do {

		printf("1 CardNumber/n2 Name/n3 Age/n4 Sex/n5 Phonenumber/n6 Address/n7 finish");
		scanf ("%d", &s);
		// system("cls");
		switch (s) {
			case 1:
				printf("请输入新的信息：");
				scanf("%s", &a[MAX_LEN]);
				strcpy (Us[o].CardNumber, a[MAX_LEN]);
				break;
			case 2:
				printf("请输入新的信息：");
				scanf("%s", &a[MAX_LEN]);
				strcpy (Us[o].Name, a[MAX_LEN]);
				break;
			case 3:
				printf("请输入新的信息：");
				scanf("%d", &a[MAX_LEN]);
				strcpy ((char *)Us[o].Age, a[MAX_LEN]);
				break;
			case 4:
				printf("请输入新的信息：");
				scanf("%s", &a[MAX_LEN]);
				strcpy (Us[o].Sex, a[MAX_LEN]);
				break;
			case 5:
				printf("请输入新的信息：");
				scanf("%s", &c);
				strcpy(Us[o].PhoneNumber, c);
				break;
			case 6:
				printf("请输入新的信息：");
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
	printf("\t\t\t请输入需要录入的用户数量\n(一次最多录入99个)");
	scanf("%d/n", &Need) ;
	printf("\t\t\t请输入用户的姓名\n");
	for (m = 0; m < Need; m++) {
		scanf("%s/n", &Us[m].Name); //将用户信息顺序存储到数组中
	}
	printf("\t\t\t请输入用户的性别\n");
	for (m = 0; m < Need; m++) {
		scanf("%s/n", &Us[m].Sex); //将用户信息顺序存储到数组中
	}
	printf("\t\t\t请输入用户的年龄\n");
	for (m = 0; m < Need; m++) {
		scanf("%s/n", &Us[m].Age); //将用户信息顺序存储到数组中
	}
	printf("\t\t\t请输入用户的身份证号码\n");
	for (m = 0; m < Need; m++) {
		scanf("%s/n", &Us[m].CardNumber); //将用户信息顺序存储到数组中
	}
	printf("\t\t\t请输入用户的手机号\n");
	for (m = 0; m < Need; m++) {
		scanf("%s/n", &Us[m].PhoneNumber); //将用户信息顺序存储到数组中
	}
	printf("\t\t\t请输入用户的家庭住址\n");
	for (m = 0; m < Need; m++) {
		scanf("%s/n", &Us[m].Address); //将用户信息顺序存储到数组中
	}
	WritetoF(Us) ;
	// system("cls") ;
	return 0;
}

void WritetoF(User Us[]) {
	FILE *fp;					                     /*定义文件指针*/
	fp = fopen("UserInformation.txt", "w");          /*打开文本文件准备写入数据*/
	if ( fp == 0 ) {                				 /*如果文件打开失败 */
		printf( "source file error\n" );
		exit(1);
	}
	fwrite(Us, sizeof(User), MAX_LEN, fp);
	fclose(fp);
}

//录入新用户信息
int Delete(User Us[], int n) {
	int i, j;
	char a[1];
	printf("请输入所需删除用户的姓名");
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
	FILE *fp;                     					/*定义文件指针*/
	fp = fopen("UserInformation.txt", "r");         /*打开文本文件准备读出数据*/
	if ( fp == 0 ) {                 				/*如果文件打开失败 */
		printf( "source file error\n" );
		exit(1);
	}
	struct stat buf;
	int rows;										/*定义一个文件行数记录变量 */
	stat("UserInformation", &buf);
	rows = buf.st_size / sizeof(User);				/*求文件中的行数*/
	fread((char *)Us, sizeof(User), rows, fp);			/*从文件中读取数据*/
	fclose(fp);                    					/*关闭文件*/
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
