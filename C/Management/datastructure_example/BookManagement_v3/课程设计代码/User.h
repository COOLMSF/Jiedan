#include"book.h"

struct node //用户所借书籍
{
	int borrow_amount, max_amount; //所借书籍数量， 最大借书数
	double tax;  //超出时限收费比率
	time_t borrow_time[10], return_time[10];  //借、还时间
	Book borrowBook[10];  //每位最多借10本书籍
};

typedef struct user //用户
{
	char user_name[30];  //用户名
	char password[30];  //密码
	char ID[30]; //有效证件号码
	int admin;  //是否管理员
	struct node user_book;  //用户所借书籍
	struct user* next;  //下一位用户
}User;

Book* book_head;  //图书头指针
int book_amount;  //图书总数量
User* user_head;  //用户头指针
User* g_UserAdmin;  //超级管理员账号
int user_amount;  //用户总数量
void welcomePage();  //欢迎页面
void manual();  //使用手册
void mainMenu();  //主菜单
void userRegister();  //用户注册
void userLogin();  //用户登录
void adminLogin();  //管理员登陆
void userMenu(User*);  //用户菜单
void userChange(User*);  //更改用户信息
int deleteUser(User*);  //删除账号
void borrowBook(User*);  //借阅管理
void returnBook(User*);  //还书管理
void history(User*);  //历史借阅浏览
void adminIniti();  //超级管理员账号初始化/**<  */
User* serchUsername(char*);  //查找用户名
void adminMenu(User*);  //管理员菜单
void queryUser();  //用户信息查询
void adminUser();  //管理用户信息
void allHistory(); //查看用户图书借阅归还情况
User* serchUserByOrder();  //按序号搜索用户
void setAdmin(User*);  //设置管理员
void addBook();  //增加图书信息
void changeBook() ; //修改图书信息
void deleteBook();  //删除图书信息
void browseBook();  //图书浏览
void searchBook();
void searchTitle();   //按书名查找
void searchAuthor();       // 按作者查找
void searchIsbn();         //按书号查找
void searchPublisher();     //按出版社查找
void creatUserList(char*, char*, char*);  //创建用户链表
void creatBookList(char*, char*, char*, char*, int);  //创建图书链表
void userIniti(User*);  //用户图书管理初始化
void load();  //从文件中加载数据
void save();  //保存数据到文件


void welcomePage()  //欢迎页面
{
	load();
	while (1)
	{
	    puts("+---------------------------------------------+");
		puts("|            欢迎使用图书管理系统!            |");
		puts("|---------------------------------------------|");
		puts("|                 [1]进入系统                 |");
		puts("|                 [2]使用手册                 |");
		puts("|                 [0]退出系统                 |");
		puts("+---------------------------------------------+");
        puts("输入数字后回车！");

		int op; scanf("%d", &op); system("cls");
		switch (op)
		{
		case 1: mainMenu(); break; // 进入系统
		case 2: manual(); system("pause"); system("cls"); break; //使用手册
		case 0: return ; //退出系统
		default: puts("指令错误,请重新输入!");
		system("cls"); break;
		}
	}
}
void manual() //使用手册
{
	puts("该系统为图书借阅管理系统");
	puts("[*] 管理员功能");
	puts("[1] 添加,修改删除图书信息");
	puts("[2] 查询图书");
	puts("[3] 管理用户");
	puts("[4] 查询借阅用户借书情况");

	puts("[*] 用户功能");
	puts("[1] 查询图书");
	puts("[2] 借阅图书");
	puts("[3] 归还图书");

}
void mainMenu()  //主菜单
{
	while (1)
	{
        puts("+---------------------------------------------+");
		puts("|                    主菜单                   |");
        puts("|---------------------------------------------|");
		puts("|                [1] 用户注册                 |");
		puts("|                [2] 用户登陆                 |");
		puts("|                [3] 管理员登陆               |");
		puts("|                [0] 返回欢迎页面             |");
        puts("+---------------------------------------------+");
        puts("输入数字后回车！");
		int op; scanf("%d", &op); system("cls");
		switch (op)
		{
        //用户注册
		case 1: userRegister(); break;
		//用户登录
		case 2: userLogin();  break;
		//管理员登录
		case 3: adminLogin();  break;
		//返回到欢迎界面
		case 0: return;
		default: puts("指令错误,请重新输入!");
		system("cls"); break;
		}
	}
}
void userRegister()  //用户注册
{
	char name[30];
	puts("请输入注册的用户名");
	scanf("%s", name);
	User* account;

    //查找用户
	while (account = serchUsername(name), account != NULL)
	{
		puts("该用户名已存在,请重新输入！");
		scanf("%s", name);
	}

	puts("请输入密码(不超过25个字母)");
	char password[30];
	scanf("%s", password);

	puts("请输入证件号码");
	char ID[30];
	scanf("%s", ID);
	//创建用户单链表
	creatUserList(name, password, ID);
	puts("注册成功！");
	//用户数量加1
	++user_amount;
	system("cls");
}

void userLogin()  //用户登录
{
	char name[30];
	puts("请输入用户名");
	scanf("%s", name);
	User* account;
	//查找用户,返回为空说明用户不存在
	while (account = serchUsername(name), account == NULL)
	{
		system("cls");
		puts("该用户名不存在，请注册或重新登陆账号！\n");
		system("pause");
		return ;

	}

	puts("请输入您的账号密码");
	scanf("%s", name);

	if (strcmp(account->password, name))
	{
		puts("密码错误,请重新登陆！\n");
		return ;
	}
    //登录成功跳转到用户菜单
	puts("登录成功!");
	system("cls");
	userMenu(account);
}



void adminLogin()  //管理员登陆
{
	char name[30];
	puts("请输入管理账号");
	scanf("%s", name);
	User* account;
	while (account = serchUsername(name), account == NULL)
	{
		system("cls");
		puts("该用户名不存在,请重新登陆账号！");
        system("pause");
		return ;

	}
    //判断权限
	if (!account->admin)
	{
		system("cls");
		puts("该账号无管理权限!");
		system("pause");
		return;
	}

	puts("请输入管理账号的密码");
	scanf("%s", name);
	if (strcmp(account->password, name))
	{
		system("cls");
		puts("密码错误,请重新登陆！");
		system("pause");
        return;
	}
	//登录成功跳到管理界面
	puts("登录成功！");
	system("cls");
	adminMenu(account);
}



void creatUserList(char* name, char* password, char* ID)  //创建用户链表
{

	User* np = user_head;

	while (np->next)
        np = np->next;

	User* tp = (User*)malloc(sizeof(User));
	strcpy(tp->user_name, name); // 赋值
	strcpy(tp->password, password);
	strcpy(tp->ID, ID);
	tp->admin = 0;
	tp->next = NULL;

    //初始化用户
	userIniti(tp);

	np->next = tp;

	save(); //保存到文件
}

void creatBookList(char* title, char* isbn, char* author, char* publisher,char* publishtime,int value, int cnt)  //创建图书链表
{
	Book* np =  book_head;
	while (np->next) np = np->next;
	Book* tb = (Book*)malloc(sizeof(Book));
	strcpy(tb->title, title);
	strcpy(tb->isbn, isbn);
	strcpy(tb->author, author);
	strcpy(tb->publisher, publisher);
	strcpy(tb->publishtime, publishtime);
	tb->value = value;
	tb->cnt = cnt;
	tb->next = NULL;
	np->next = tb;
	save();
}
void userIniti(User* account)  //用户图书管理初始化
{
	account->user_book.borrow_amount = 0;
	account->user_book.max_amount = 10;
	account->user_book.tax = 1.0;
	memset(account->user_book.borrow_time, 0, sizeof(account->user_book.borrow_time));
	memset(account->user_book.return_time, 0, sizeof(account->user_book.return_time));
	memset(account->user_book.borrowBook, 0, sizeof(account->user_book.borrowBook));
}

void load()  //从文件中加载数据
{
    //头结点
	book_head = (Book*)malloc(sizeof(Book));
	book_head->next = NULL;
	book_amount = 0;

	FILE* fp2;
	fp2 = fopen("book.bin", "rb");
	if (fp2 == NULL)
	{

        fp2 = fopen("book.bin", "wb");
		if (fp2 == NULL)
		{
			printf("图书存储失败！\n"); exit(0);
		}
		fclose(fp2);
            return ;
	}
	else
	{
	    //头指针
		Book* bp =  book_head; //bp指向头结点
		Book* tp = (Book*)malloc(sizeof(Book));
		while (fread(tp, sizeof(Book), 1, fp2)) //读取每一本书到tp
		{

		    //头结点指向tp
			bp->next = tp;
			++book_amount; //总量加1
			tp = tp->next;//从文件中读取,next非空
			tp = (Book*)malloc(sizeof(Book));
			bp = bp->next;
		}
		fclose(fp2);
	}

	//头头结点
	user_head = (User*)malloc(sizeof(User));
	user_head->next = NULL;
	user_amount = 0;

	FILE* fp1;
	fp1 = fopen("user.bin", "rb");
	if (fp1 == NULL)
	{
		adminIniti(); return;
	}
	User* np =  user_head;
	User* temp = (User*)malloc(sizeof(User));

	while (fread(temp, sizeof(User), 1, fp1))
	{
		np->next = temp;
		++user_amount;
		temp = temp->next;
		temp = (User*)malloc(sizeof(User));
		np = np->next;
	}
	g_UserAdmin = user_head->next;
	fclose(fp1);
}

void save()  //保存数据到文件
{

	FILE* fp = fopen("user.bin", "wb");
	User* temp = user_head->next;
	while (temp)
	{
		fwrite(temp, sizeof(User), 1, fp);
		temp = temp->next;
	}
	fclose(fp);

	fp = fopen("book.bin", "wb");
	Book* tb = book_head->next;
	while (tb)
	{
		fwrite(tb, sizeof(Book), 1, fp);
		tb = tb->next;
	}
	fclose(fp);
}

void userMenu(User* account)  //用户菜单
{
	while (1)
	{

      printf("        欢迎用户%12s登录!\n", account->user_name);
		puts("+-----------------------------------------------+");
		puts("|                [1] 图书浏览                   |");
		puts("|                [2] 图书查找                   |");
		puts("|                [3] 历史借阅                   |");
		puts("|                [4] 借阅管理                   |");
		puts("|                [5] 还书管理                   |");
		puts("|                [6] 修改账号                   |");
		puts("|                [7] 删除账号                   |");
		puts("|                [0] 退出登陆                   |");
		puts("+-----------------------------------------------+");
		 puts("输入数字后回车！");
		int op; scanf("%d", &op); system("cls");
		switch (op)
		{
		case 1: browseBook(); system("pause"); system("cls"); break;
		case 2: searchBook(); system("pause"); system("cls"); break;
		case 3: history(account); system("pause"); system("cls"); break;
		case 4: borrowBook(account); break;
		case 5: returnBook(account); break;
		case 6: userChange(account);  break;
		case 7: if (deleteUser(account))
		{
			printf("该账号已被删除,请重新登陆！\n");
			system("cls");
			return; //返回到主菜单
		}
		else break;
		case 0: printf("账号登出成功!\n");
		system("cls"); return;
		default: printf("指令错误,请重新输入！\n");
		system("cls"); break;
		}
	}
}

void userChange(User* account)  //更改用户信息
{
	printf("待修改用户：%s\t 您现在可以更改您的个人信息!\n", account->user_name);
	char Name[30];
	printf("请输入新的用户名(不超过25个字母)：\n");
	scanf("%s", Name);
	strcpy(account->user_name, Name);
	printf("请重新输入您的密码(不超过25个字母)：\n");
	char password[30];
	scanf("%s", password);
	strcpy(account->password, password);
	printf("用户%s\t账号密码已修改！\n", account->user_name);
	printf("请重新输入您的有效证件号码(不超过25个字母)：\n");
	char ID[30];
	scanf("%s", ID);
	strcpy(account->ID, ID);
	printf("用户%s\t有效证件号码已修改！\n", account->user_name);
	save();
	printf("用户%s\t个人信息修改成功，正在返回上一界面...\n", account->user_name);
	system("cls");
}

int deleteUser(User* account)  //删除账号
{
	if (!strcmp(account->user_name, g_UserAdmin->user_name))
	{
		printf("用户%s拥有最高权限，删除失败\n", g_UserAdmin->user_name);
		system("cls"); return 0;
	}
	printf("是否需要删除账号%s？\n", account->user_name);
	puts("[1] 是");
	puts("[0] 否");
	puts("输入数字后回车！");
	int op;  scanf("%d", &op);
	if (op == 1)
	{
		if (account->user_book.borrow_amount)
		{
			printf("删除失败！该用户有%d本图书未归还！请先归还所借阅图书！\n", account->user_book.borrow_amount);
		}
		else
		{
			User* tp = (User*)malloc(sizeof(User));
			tp = user_head;
			User* np = (User*)malloc(sizeof(User));
			np = user_head->next;
			while (np)
			{
				if (!strcmp(np->user_name, account->user_name))
				{
					tp->next = np->next;
					free(np); --user_amount;
					save();
					printf("账号已删除成功！\n");
					system("pause"); system("cls");
					return 1;
				}
				tp = np;
				np = np->next;
			}
		}
	}
	else if (!op) printf("已取消本次操作！\n");
	else printf("输入选项错误，请重新输入！正在返回上一层...\n");
	system("pause"); system("cls"); return 0;
}

void borrowBook(User* account)  //借阅管理
{
	printf("用户%s:请输入您的有效身份证件号码\n", account->user_name);
	char ID[30]; scanf("%s", ID); system("cls");
	while (strcmp(account->ID, ID))
	{
		system("cls");
		puts("身份证件号码不匹配,请重新输入！");
		scanf("%s", ID);
	}
	while (1)
	{
		int ans = account->user_book.borrow_amount, Max = account->user_book.max_amount;
		if (ans == Max)
		{
			printf("用户%s:借阅图书数量 %d 本，已达上限 %d 本，请先归还部分图书！\n", account->user_name, ans, Max);
			system("pause"); system("cls"); return;
		}
		browseBook();
		puts("请输入借阅的书籍序号(输入 0 退出)");
		int cnt; scanf("%d", &cnt);
		if (cnt == 0)
		{
			puts("退出成功！"); system("pause"); system("cls");
			return;
		}
		else if (cnt > book_amount || cnt < 0)
		{
			puts("输入错误!");
		}
		else
		{
			puts("请输入借阅的时间(借阅时间不能大于等于180)");
			int day; scanf("%d", &day);
			if (day > 180 || day <= 0)
				puts("借阅时间错误!");
			else
			{
				Book* tb = (Book*)malloc(sizeof(Book));
				tb = book_head->next;
				for (int i = 1; i < cnt; ++i)
					tb = tb->next;
				tb->cnt--;
				account->user_book.borrowBook[ans] = *tb;
				account->user_book.borrow_time[ans] = time(NULL);
				account->user_book.return_time[ans] = time(NULL) + day * 3600 * 24;
				++account->user_book.borrow_amount;
				save();
				printf("用户%s:借阅图书《%s》成功！\n", account->user_name, tb->title);
			}
		}
		system("pause"); system("cls");
	}
}

void returnBook(User * account)  //还书管理
{

	while (1)
	{
		history(account);
		if (!account->user_book.borrow_amount)
		{
			system("pause"); system("cls"); return;
		}
		printf("请输入您需要归还的书籍序号（输入-1以退出还书系统）！\n");
		int cnt = 0; scanf("%d", &cnt); system("cls");
		if (cnt == -1)
		{
			printf("正在退出还阅系统，请稍后...\n");
			system("pause"); system("cls"); return;
		}
		if (cnt > account->user_book.borrow_amount || cnt < 0)
		{
			printf("请正确输入上述书籍序号！\n");
		}
		else
		{
			int i = 0;
			for (--cnt; i < cnt; ++i);
			Book* tb = (Book*)malloc(sizeof(Book));
				tb = book_head->next;
				for (int i = 1; i < cnt; ++i)
					tb = tb->next;
			tb->cnt++;
			char title[100];
			strcpy(title, account->user_book.borrowBook[i].title);
			time_t t = time(NULL);
			printf("*************************************************\n");
			printf("规定还书时间:%s", ctime(&account->user_book.return_time[i]));
			printf("当前时间:%s", ctime(&t));
			t -= account->user_book.return_time[i];


			if (t > 0)
			{
				double cost = t / 3600.0 / 24 * account->user_book.tax;
				printf("由于您未在指定日期内归还《%s》,您需要支付违约金%.2lf元\n", title, cost);
			}
			else printf("书籍《%s》借阅未超出时间，无需支付违约金！\n", title);


			for (; i < account->user_book.borrow_amount; ++i)
			{
				account->user_book.borrowBook[i] = account->user_book.borrowBook[i + 1];
				account->user_book.borrow_time[i] = account->user_book.borrow_time[i + 1];
				account->user_book.return_time[i] = account->user_book.return_time[i + 1];
			}
			--account->user_book.borrow_amount;
			save();
			printf("书籍《%s》归还成功！\n", title);
		}
		system("pause"); system("cls");
	}
}

void history(User * account)  //历史借阅浏览
{
	int n = account->user_book.borrow_amount;
	puts("############################################################");
	printf("用户%s:\n", account->user_name);
	if (!n)
	{
		puts("暂无书籍在借阅记录！"); return;
	}
	puts("借阅书籍序号");
	for (int i = 0; i < n; ++i)
	{
		struct node t = account->user_book;
		time_t nt = time(NULL) - t.return_time[i];
		double cost = 0.0;
		if (nt > 0) cost = t.tax * (nt / 3600.0 / 24);
		printf("[%d]\n", i + 1);
		printf("书名:《%s》\n", t.borrowBook[i].title);
		printf("借阅日期:%s", ctime(&t.borrow_time[i]));
		printf("规定还书日期:%s", ctime(&t.return_time[i]));
		if (nt > 0) printf("是否超时:是\n");
		else printf("  是否超时:否\n");
		printf("借阅费用:%.2lf\n", cost);
	}
}

void adminIniti()  //超级管理员账号初始化
{
	FILE* fp = fopen("user.bin", "wb");
	if (fp == NULL)
	{
		printf("管理员权限初始化失败！\n"); exit(0);
	}
	g_UserAdmin = (User*)malloc(sizeof(User));
	strcpy(g_UserAdmin->user_name, "admin");
	strcpy(g_UserAdmin->password, "admin");
	strcpy(g_UserAdmin->ID, "1999");
	g_UserAdmin->admin = 1;
	g_UserAdmin->next = NULL;
	userIniti(g_UserAdmin);
	user_head->next = g_UserAdmin;
	user_amount = 1;
	save();
	fclose(fp);
}

User* serchUsername(char* name)  //查找用户名
{
	User* np = user_head->next;
	while (np)
	{
		if (!strcmp(np->user_name, name)) return np;
		np = np->next;
	}
	return NULL;
}

void adminMenu(User * account)  //管理员菜单
{
	while (1)
	{

       printf("        欢迎管理员%12s登录\n", account->user_name);
        puts("+-----------------------------------------------+");
		puts("|                [1] 增加图书                   |");
		puts("|                [2] 修改图书                   |");
		puts("|                [3] 删除图书                   |");
		puts("|                [4] 图书浏览                   |");
		puts("|                [5] 图书查找                   |");
		puts("|                [6] 管理用户                   |");
		puts("|                [0] 退出登陆                   |");
        puts("+-----------------------------------------------+");
        puts("输入数字后回车！");
		int op; scanf("%d", &op); system("cls");
		switch (op)
		{
		case 1: addBook(); break;
		case 2: changeBook(); break;
		case 3: deleteBook(); break;
		case 4: browseBook(); system("pause"); system("cls"); break;
		case 5: searchBook(); break;
		case 6: adminUser(); break;
		case 0: printf("退出成功!\n"); system("pause"); system("cls"); return;
		default: printf("指令错误,请重新输入！\n"); system("pause"); system("cls"); break;
		}
	}
}

void queryUser()  //用户信息查询
{
	int cnt = 1;
	User* np = (User*)malloc(sizeof(User));
	np = user_head->next;
	printf("|序号\t\t|账号\t\t       |密码\t\t      |证件号码\t\t\t |是否管理员|\n");
	puts("|---------------------------------------------------------------------------------------------------|");
	while (np)
	{
		printf("|%d\t\t|%-22s|%-22s|%-26s|", cnt, np->user_name, np->password, np->ID);
		if (np->admin) puts(" 是       |");
		else puts(" 否       |");
		np = np->next;
		++cnt;

	}
	puts("+---------------------------------------------------------------------------------------------------+");
}

void adminUser()  //管理用户信息
{
	while (1)
	{
		puts("+-----------------------------------------------+");
		puts("|                  管理界面                     |");
		puts("|-----------------------------------------------|");
		puts("|            [1] 查看用户个人信息               |");
		puts("|            [2] 修改用户个人信息               |");
		puts("|            [3] 删除用户账号                   |");
		puts("|            [4] 查看用户图书借阅归还情况       |");
		puts("|            [5] 设置管理员权限                 |");
		puts("|            [0] 返回总管理界面                 |");
		puts("+-----------------------------------------------+");
		User* np = (User*)malloc(sizeof(User));
		int op; scanf("%d", &op); system("cls");
		switch (op)
		{
		case 1: queryUser(); system("pause"); system("cls"); break;
		case 2: if (np = serchUserByOrder(), np != NULL) userChange(np);
				else
		{
			system("cls");
		}
				break;
		case 3:if (np = serchUserByOrder(), np != NULL)
		{
			int admin = np->admin;
			if (deleteUser(np) && admin)
				puts("该账号已被删除,请重新登陆!");
			system("pause"); system("cls");
			return;
		}
			   else
		{
			system("pause"); system("cls");
		}
			   break;
		case 4: allHistory(); break;
		case 5: if (np = serchUserByOrder(), np != NULL) setAdmin(np);
				else
		{
			system("cls");
		}
				break;
		case 0: puts("退出成功!"); system("pause"); system("cls"); return;
		default: puts("指令错误，请重新输入！"); system("pause"); system("cls"); break;
		}
	}
}

void allHistory() //查看用户图书借阅归还情况
{
	while (1)
	{
	    puts("+---------------------------------------------------------------------------------------------------+");
        puts("|                                      图书借阅归还查询系统                                         |");
		puts("+---------------------------------------------------------------------------------------------------+");
		User* account  = serchUserByOrder();
		if (account)
		{
			history(account);
			puts("查阅成功!");
			system("pause"); system("cls"); return;
		}
		system("cls");
	}
}




User* serchUserByOrder()  //按序号搜索用户
{
	queryUser();
	puts("请输入待操作的用户序号");
	int cnt; scanf("%d", &cnt); system("cls");
	if (cnt > user_amount || cnt <= 0)
		puts("输入错误!");
	else
	{
		User* tb =  user_head->next;
		for (int i = 1; i < cnt; ++i)
			tb = tb->next;
		return tb;
	}
	return NULL;
}

void setAdmin(User * account)  //设置管理员
{

	if (!strcmp(account->user_name, g_UserAdmin->user_name))
	{
		printf("用户%s拥有最高管理权限,修改失败!", g_UserAdmin->user_name);
		system("cls"); return;
	}
	printf("是否确认将用户%s设置为管理员？\n", account->user_name);

	puts("[0] 取消管理员权限");
	puts("[1] 设置为管理员");
    puts("输入数字后回车！");

	int op; scanf("%d", &op);
	if (op == 1)
	{
		account->admin = op;
		printf("用户%s\t管理员权限设置成功！\n", account->user_name);
	}
	else if (op == 0)
	{
		account->admin = op;
		printf("用户%s\t管理员权限已被取消！\n", account->user_name);
	}
	else
	{
		puts("操作失败,请按要求输入");
	}

	save();
	system("cls");
}


void addBook()  //增加图书信息
{
	char title[100], isbn[100], author[100], publisher[100], publishtime[100];
	int value,cnt;
	puts("请输入需要添加的书籍名称");
	scanf("%s", title);
	puts("请输入需要添加的书籍书号");
	scanf("%s", isbn);
	puts("请输入需要添加的书籍作者");
	scanf("%s", author);
	puts("请输入需要添加的书出版社");
	scanf("%s", publisher);
	puts("请输入需要添加的书出版日期");
	scanf("%s", publishtime);
	puts("请输入需要添加的图书单价");
	scanf("%d", &value);
	puts("请输入需要添加的书籍数量");
	scanf("%d", &cnt);
	++book_amount;
	creatBookList(title, isbn, author, publisher, publishtime, value, cnt);
	printf("添加书籍《%s》成功", title);
	system("pause"); system("cls");
}
void changeBook()  //修改图书信息
{
	while(1)
	{
		browseBook();
		puts("请输入待修改的书籍序号(输入0退出)");
		int cnt; scanf("%d", &cnt);
		if (cnt == 0)
		{
			puts("退出成功！"); system("pause"); system("cls");
			return;
		}
		else if (cnt > book_amount || cnt < 0)
		{
			puts("输入错误!");
		}
		else
		{
			Book* tb = (Book*)malloc(sizeof(Book));
			tb = book_head->next;
			int dd=1;
			while (tb)
			{
				if(dd==cnt)
				{
					char title[100], isbn[100], author[100], publisher[100],publishtime[100];
					int value,cnt;
					puts("请输入修改后的书籍名称");
					scanf("%s", title);
					puts("请输入修改后的籍书号");
					scanf("%s", isbn);
					puts("请输入修改后的书籍作者");
					scanf("%s", author);
					puts("请输入修改后的出版社");
					scanf("%s", publisher);
					puts("请输入修改后的出版日期");
					scanf("%s", publishtime);
					puts("请输入修改后的图书单价");
					scanf("%d", &value);
					puts("请输入修改后的书籍数量");
					scanf("%d", &cnt);
					strcpy(tb->title,title);
					strcpy(tb->isbn,isbn);
					strcpy(tb->author,author);
					strcpy(tb->publisher,publisher);
					strcpy(tb->publishtime,publishtime);
					tb->value=value;
					tb->cnt=cnt;
					break;
				}
				tb = tb->next; ++dd;
			}
		}
		system("pause"); system("cls");
	}
}
void deleteBook()  //删除图书信息
{
	while (1)
	{
		browseBook();
		printf("请输入待删除的书籍序号(输入0退出)\n");
		int cnt; scanf("%d", &cnt);
		if (cnt == 0)
		{
			puts("退出成功!"); system("pause"); system("cls");
			return;
		}
		else if (cnt > book_amount || cnt < 0)
		{
			puts("输入错误!");
		}
		else
		{
			Book* tb = book_head;
			Book* np =  book_head->next;
			for (int i = 1; i < cnt; ++i)
			{
				np = tb;
				tb = tb->next;
			}
			np->next = tb->next;
			free(tb);
			--book_amount; //数量减1
			save();
			puts("删除成功！");
		}
		system("pause"); system("cls");
	}
}

void browseBook()  //图书浏览
{
	int cnt = 1;
	if (!book_amount)
	{
		printf("暂无图书资料!\n");
		return;
	}
	Book* tb = book_head->next;
	puts("图书详情如下");
 	puts("+--------------------------------------------------------------------------------+");
    puts("|序号|    书名    |    书号    |    作者    |   出版社   |   出版日期  |单价|数量|");
    puts("+--------------------------------------------------------------------------------+");
	while (tb)
	{
		printf("|%4d|%12s|%12s|%12s|%12s|%12s|%4d|%4d|\n", cnt, tb->title, tb->isbn,
			tb->author, tb->publisher,tb->publishtime,tb->value, tb->cnt);
		tb = tb->next; ++cnt;
	}
}
void searchBook()//图书查找
{   while(1)
	{
        puts("+-------------------------------------+");
        puts("|               查找图书              |");
        puts("|-------------------------------------|");
		puts("|          [1] 按书名查找             |");
		puts("|          [2] 按作者查找             |");
		puts("|          [3] 按书号查找             |");
		puts("|          [4] 按出版社查找           |");
		puts("|          [0] 返回欢迎页面           |");
		puts("+-------------------------------------+");
        puts("输入数字后回车！");
		int op; scanf("%d", &op); system("cls");
		switch (op)
		{
			case 1: searchTitle(); system("pause"); system("cls"); break;
			case 2: searchAuthor(); system("pause"); system("cls"); break;
			case 3: searchIsbn();  system("pause"); system("cls"); break;
			case 4: searchPublisher(); system("pause"); system("cls"); break;
			case 0: system("pause"); system("cls"); return ;
			default: printf("错误的指令，请重新输入！\n");
			system("cls"); break;
		}
	}
}
void searchTitle()   //按书名查找
{

	Book* tb = book_head->next;
	puts("请输入查找书名");
	char name[100];
	scanf("%s",name);
    puts("+--------------------------------------------------------------------------+");
    puts("|    书名    |    书号    |    作者    |   出版社   |  出版日期  |单价|数量|");
    puts("+--------------------------------------------------------------------------+");
	while (tb)
	{
		if(strcmp(tb->title,name)==0)
		{
			printf("|%12s|%12s|%12s|%12s|%12s|%4d|%4d|\n", tb->title, tb->isbn,
			tb->author, tb->publisher,tb->publishtime,tb->value, tb->cnt);
		}

		tb = tb->next;
	}
}
void searchAuthor()       // 按作者查找
{
	Book* tb = book_head->next;
	puts("请输入图书作者");
	char name[100];
	scanf("%s",name);
    puts("+--------------------------------------------------------------------------+");
    puts("|    书名    |    书号    |    作者    |   出版社   |  出版日期  |单价|数量|");
    puts("+--------------------------------------------------------------------------+");
	while (tb)
	{
		if(strcmp(tb->author,name)==0)
		{
			printf("|%12s|%12s|%12s|%12s|%12s|%4d|%4d|\n", tb->title, tb->isbn,
			tb->author, tb->publisher,tb->publishtime,tb->value, tb->cnt);
		}
		tb = tb->next;
	}

}
void searchIsbn()         //按书号查找
{
	Book* tb = book_head->next;
	puts("请输入查找书号");
	char name[100];
	scanf("%s",name);
    puts("+--------------------------------------------------------------------------+");
    puts("|    书名    |    书号    |    作者    |   出版社   |  出版日期  |单价|数量|");
    puts("+--------------------------------------------------------------------------+");
	while (tb)
	{
		if(strcmp(tb->isbn,name)==0)
		{
			printf("|%12s|%12s|%12s|%12s|%12s|%4d|%4d|\n", tb->title, tb->isbn,
			tb->author, tb->publisher,tb->publishtime,tb->value, tb->cnt);
		}
		tb = tb->next;
	}
}
void searchPublisher()     //按出版社查找
{
	Book* tb =  book_head->next; //首元结点
	puts("请输入出版社名称");
	char name[100];
	scanf("%s",name);
	puts("+--------------------------------------------------------------------------+");
    puts("|    书名    |    书号    |    作者    |   出版社   |  出版日期  |单价|数量|");
    puts("+--------------------------------------------------------------------------+");


	while (tb)
	{
		if(strcmp(tb->publisher,name)==0) //比较出版社
		{
			printf("|%12s|%12s|%12s|%12s|%12s|%4d|%4d|\n", tb->title, tb->isbn,
			tb->author, tb->publisher,tb->publishtime,tb->value, tb->cnt);
		}

		tb = tb->next;
	}
}

