#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 1000
#include <conio.h>
//3.存取贷业务管理：
//存款、取款、贷款、利息计算、账户余额等（参考航空订票和图书管理）
//4.业务查询：根据不同关键字查询业务信息。（参考航班查询）
int jin;
char a;
void chuangjian();

int denglu();   //登录账户
int huyan();   //账户验证
int miyan();  //密码验证
void cunkuan(int);   //存款
void qukuan(int);     //取款
void daikuan(int);    //贷款
void lixi(int);       //利息计算
void display(int);//查询
//
void date();      //显示日期
void flag(int);    //主界面
void flag1();     //初始界面
//
int i;    //控制循环
struct users {
	char idnum[9];   //账户
	char password[7];    //密码
	char name[10]; //姓名
	char idnumber[20];  //身份证号码
	double YuE;     //余额
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
	printf("\n▓                               * 欢迎使用**银行  *                               ▓\n");
	printf("\n#################################################################################\n");
	printf("\n          ◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆       \n");
	printf("          ◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆         \n");
	printf("\n#################################################################################\n");
	printf("\n▓                          ************请先登录*******************                ▓\n");
	printf("\n#################################################################################\n");
}

void flag(int m) {
	int a;//选择功能的变量
	do {
		date();
		printf("\n#################################################################################\n");
		printf("\n▓                               * 欢迎使用  *                                 ▓\n");
		printf("\n#################################################################################\n");
		printf("\n          ◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆\n");
		printf("          |◆|******|◆|        ☆ 存款业务       请按 1        |◆|******|◆|\n");
		printf("          |◆|******|◆|        ☆ 取款业务       请按 2        |◆|******|◆|\n");
		printf("          |◆|******|◆|        ☆ 查询余额       请按 3        |◆|******|◆|\n");
		printf("          |◆|******|◆|        ☆ 贷款业务       请按 4        |◆|******|◆|\n");
		printf("          |◆|******|◆|        ☆ 利息计算       请按 5        |◆|******|◆|\n");
		printf("          |◆|******|◆|        ☆ 退出系统       请按 6        |◆|******|◆|\n");
		printf("          |◆|******|◆|                                        |◆|******|◆|\n");
		printf("          ◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆\n");
		printf("\n#################################################################################\n");
		printf("\n▓                          *******************************                    ▓\n");
		printf("\n#################################################################################\n");
		printf("\n\n\t\t##请输入你的选择：");
		fflush(stdin);
		scanf("%d", &a);
		switch (a) {
			case 1: {
				fflush(stdin);
				cunkuan(m);
				break;//存款

			}
			case 2:  {

				fflush(stdin);
				qukuan(m);
				break;//取款

			}
			case 3: {

				fflush(stdin);
				display(m);
				break;//查询业务
			}
			case 4: {

				fflush(stdin);
				daikuan(m);
				break;//贷款

			}
			case 5: {

				fflush(stdin);
				lixi(m);
				break;//利息

			}
			case 6:
				exit(0);
			default:
				printf("您输入的选择有误，请输入正确的选项：");

		}
	} while (1);
}
//********************************************************************************************************************
//用户功能选择界面

//***************************************************************************
void chuangjian() { //创建用户实验
	fflush(stdin);
	date();
	printf("请输入创建用户数量：");
	int n;
	scanf("%d", &n);
	for (i = 1; i <= n; i++) {
		printf("请输入您的名字\n");
		scanf("%s", user[i].name);
		printf("请输入您的身份证号\n");
		scanf("%s", user[i].idnumber);
		printf("请输入您的账户\n");
		scanf("%s", user[i].idnum);
		printf("请输入您六位数密码\n");
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
	printf("请输入您的账户登录：\n");
	scanf("%s", id);
	while (huyan(id) == 0) {
		printf("请输入正确已在本行开户的的账户：\n");
		scanf("%s", id);
	}
	int k = huyan(id);
	printf("请输入您的六位密码：\n");
	for (i = 0; i < 6; i++) {
		password[i] = getch();
		printf("*");
	}
	while (miyan(password, k) != 1) {
		printf("您密码输入错误\n");
		printf("请输入正确六位密码：\n");
		for (i = 0; i < 6; i++) {
			password[i] = getch();
			printf("*");
		}
	}
	if (miyan(password, k) == 1) {
		printf("您已成功登录\n");
		return k;
	} else
		return -1;
}
void cunkuan(int m) { //存款
	fflush(stdin);
	int k;
	printf("\n\n");
	printf("\t\t||================================================================||\n");
	printf("\t\t||                           *存款金额*                           ||\n");
	printf("\t\t||================================================================||\n");
	printf("\t\t||                                                                ||\n");
	printf("\t\t||                                                                ||\n");
	printf("\t\t||         1、200        2、400        3、600        4、800       ||\n");
	printf("\t\t||                                                                ||\n");
	printf("\t\t||                                                                ||\n");
	printf("\t\t||         5、1000        6、2000        7、4000        8、6000   ||\n");
	printf("\t\t||                                                                ||\n");
	printf("\t\t||         9、其他金额           0、退出存款                      ||\n");
	printf("\t\t||================================================================||\n");
	printf("\t\t||================================================================||\n");
	printf("\n\n\t\t\t请输入你的选择：");
	scanf("%d", &k);
	while (k != 0) {
		switch (k) {
			case 1: {
				jin = 200;
				printf("您存款前余额为：%lf\n", user[m].YuE);
				user[m].YuE += jin;
				printf("您存后的余额为：%lf,您已存款成功！\n", user[m].YuE);
				break;
			}
			case 2: {
				jin = 400;
				printf("您存款前余额为：%lf\n", user[m].YuE);
				user[m].YuE += jin;
				printf("您存后的余额为：%lf,您已存款成功！\n", user[m].YuE);
				break;
			}
			case 3: {
				jin = 600;
				printf("您存款前余额为：%lf\n", user[m].YuE);
				user[m].YuE += jin;
				printf("您存后的余额为：%lf,您已存款成功！\n", user[m].YuE);
				break;
			}
			case 4: {
				jin = 800;
				printf("您存款前余额为：%lf\n", user[m].YuE);
				user[m].YuE += jin;
				printf("您存后的余额为：%lf,您已存款成功！\n", user[m].YuE);
				break;
			}
			case 5: {
				jin = 1000;
				printf("您存款前余额为：%lf\n", user[m].YuE);
				user[m].YuE += jin;
				printf("您存后的余额为：%lf,您已存款成功！\n", user[m].YuE);
				break;
			}
			case 6: {
				jin = 2000;
				printf("您存款前余额为：%lf\n", user[m].YuE);
				user[m].YuE += jin;
				printf("您存后的余额为：%lf,您已存款成功！\n", user[m].YuE);
				break;

			}
			case 7: {
				jin = 4000;
				printf("您存款前余额为：%lf\n", user[m].YuE);
				user[m].YuE += jin;
				printf("您存后的余额为：%lf,您已存款成功！\n", user[m].YuE);
				break;
			}
			case 8: {
				jin = 8000;
				printf("您存款前余额为：%lf\n", user[m].YuE);
				user[m].YuE += jin;
				printf("您存后的余额为：%lf,您已存款成功！\n", user[m].YuE);
				break;
			}
			case 9: {
				printf("请输入您的存款余额：%d\n", &jin);
				printf("您存款前余额为：%lf\n", user[m].YuE);
				user[m].YuE += jin;
				printf("您存后的余额为：%lf,您已存款成功！\n", user[m].YuE);

				break;
			}
		}
		printf("输入0返回主页面，或者输入其他选择金额继续存款.\n");
		scanf("%d", &k);
	}
}
void qukuan(int m) { //取款
	fflush(stdin);
	date();
	int k;
	printf("\n\n");
	printf("\t\t||================================================================||\n");
	printf("\t\t||                           *取款金额*                           ||\n");
	printf("\t\t||================================================================||\n");
	printf("\t\t||                                                                ||\n");
	printf("\t\t||                                                                ||\n");
	printf("\t\t||         1、200        2、400        3、600        4、800       ||\n");
	printf("\t\t||                                                                ||\n");
	printf("\t\t||                                                                ||\n");
	printf("\t\t||         5、1000        6、2000        7、4000        8、6000   ||\n");
	printf("\t\t||                                                                ||\n");
	printf("\t\t||         9、其他金额           0、退出存款                      ||\n");
	printf("\t\t||================================================================||\n");
	printf("\t\t||================================================================||\n");
	printf("\n\n\t\t\t请输入你的选择：");
	scanf("%d", &k);
	while (k != 0) {
		switch (k) {
			case 1: {
				jin = 200;
				if (jin <= user[m].YuE) {
					printf("您取款前余额为：%lf\n", user[m].YuE);
					user[m].YuE -= jin;
					printf("您取后的余额为：%lf,您已取款成功！\n", user[m].YuE);
				} else {
					printf("您的账户余额不足，无法取款！\n");

				}
				break;
			}
case2: {
				jin = 400;
				if (jin <= user[m].YuE) {
					printf("您取款前余额为：%lf\n", user[m].YuE);
					user[m].YuE -= jin;
					printf("您取后的余额为：%lf,您已取款成功！\n", user[m].YuE);
				} else {
					printf("您的账户余额不足，无法取款！\n");

				}
				break;
			}

			case 3: {
				jin = 600;
				if (jin <= user[m].YuE) {
					printf("您取款前余额为：%lf\n", user[m].YuE);
					user[m].YuE -= jin;
					printf("您取后的余额为：%lf,您已取款成功！\n", user[m].YuE);
				} else {
					printf("您的账户余额不足，无法取款！\n");

				}
				break;
			}
			case 4: {
				jin = 800;
				if (jin <= user[m].YuE) {
					printf("您取款前余额为：%lf\n", user[m].YuE);
					user[m].YuE -= jin;
					printf("您取后的余额为：%lf,您已取款成功！\n", user[m].YuE);
				} else {
					printf("您的账户余额不足，无法取款！\n");

				}
				break;
			}
			case 5: {
				jin = 1000;
				if (jin <= user[m].YuE) {
					printf("您取款前余额为：%lf\n", user[m].YuE);
					user[m].YuE -= jin;
					printf("您取后的余额为：%lf,您已取款成功！\n", user[m].YuE);
				} else {
					printf("您的账户余额不足，无法取款！\n");

				}
				break;
			}
			case 6: {
				jin = 2000;
				if (jin <= user[m].YuE) {
					printf("您取款前余额为：%lf\n", user[m].YuE);
					user[m].YuE -= jin;
					printf("您取后的余额为：%lf,您已取款成功！\n", user[m].YuE);
				} else {
					printf("您的账户余额不足，无法取款！\n");

				}
				break;
			}
			case 7: {
				jin = 4000;
				if (jin <= user[m].YuE) {
					printf("您取款前余额为：%lf\n", user[m].YuE);
					user[m].YuE -= jin;
					printf("您取后的余额为：%lf,您已取款成功！\n", user[m].YuE);
				} else {
					printf("您的账户余额不足，无法取款！\n");

				}
				break;

			}
			case 8: {
				jin = 6000;
				if (jin <= user[m].YuE) {
					printf("您取款前余额为：%lf\n", user[m].YuE);
					user[m].YuE -= jin;
					printf("您取后的余额为：%lf,您已取款成功！\n", user[m].YuE);
				} else {
					printf("您的账户余额不足，无法取款！\n");

				}
				break;
			}
			case 9: {
				printf("请输入您的qu款金额：\n");
				scanf("%d", &jin);
				if (jin <= user[m].YuE) {
					printf("您取款前余额为：%lf\n", user[m].YuE);
					user[m].YuE -= jin;
					printf("您取后的余额为：%lf,您已取款成功！\n", user[m].YuE);
				} else {
					printf("您的账户余额不足，无法取款！\n");

				}
				break;
			}

		}
		printf("输入0，返回主页面，或者您可以选择金额继续取款。\n");
		scanf("%d", &k);
	}
}
void display(int m) { //查询
	fflush(stdin);
	date();
	printf("您的账户为:%s\n", user[m].idnum);
	printf("您的身份证号为:%s\n", user[m].idnumber);
	printf("您的账户余额为:%lf\n", user[m].YuE);
	printf("您的xingming为:%s\n", user[m].name);
	printf("按#返回主页面！");
	scanf("%c", &a);
}
void lixi(int m) { //利息计算
	date();
	printf("按#返回主页面！");
	scanf("%c", &a);
}
void daikuan(int m) { //贷款
	date();
	int k;
	printf("\n\n");
	printf("\t\t||================================================================||\n");
	printf("\t\t||                           *贷款金额*                           ||\n");
	printf("\t\t||================================================================||\n");
	printf("\t\t||                                                                ||\n");
	printf("\t\t||                                                                ||\n");
	printf("\t\t||         1、200        2、400        3、600        4、800       ||\n");
	printf("\t\t||                                                                ||\n");
	printf("\t\t||                                                                ||\n");
	printf("\t\t||         5、1000        6、2000        7、4000        8、6000   ||\n");
	printf("\t\t||               (以上贷款金额利率为0.1/每年                      ||\n");
	printf("\t\t||             您也可选择超过6000元的贷款利率为0.12/每年)         ||\n");
	printf("\t\t||================================================================||\n");
	printf("\t\t||================================================================||\n");
	printf("\n\n\t\t\t请输入你的贷款金额：");
	scanf("%d", &k);
	printf("请确定您的贷款金额为%d", k);
	printf("<1>确认 <2>取消");
	int g;
	scanf("%d", &g);
	if (g == 1) {
		printf("您已贷款成功！");
		printf("您款前余额为：%lf", user[m].YuE);
		user[m].YuE += k;
		printf("您取后的余额为：%lf", user[m].YuE);
	} else {
		printf("请您输入新的贷款金额");
		scanf("%d", &g);
		printf("您已贷款成功！");
		printf("您款前余额为：%lf", user[m].YuE);
		user[m].YuE += k;
		printf("您取后的余额为：%lf", user[m].YuE);
	}
	printf("按#返回主页面！");
	scanf("%c", &a);
}
void date() { //显示当前日期
	printf("当前日期：");
	system("date/t");
	printf("当前时间：");
	system("time/t");
}


