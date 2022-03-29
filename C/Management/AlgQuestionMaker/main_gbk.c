#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


// 最大文件名
#define MAXNAME 254

// 最大缓冲区长度
#define MAXBUF 1024

// NULL
#define SLIST_NULL ((void *) 0)


// 问题的数据结构
struct _QuestionInfo {
    int id;
    char name[MAXNAME];
    char result[MAXNAME];
};

// QuestionInfo类型定义
typedef struct _QuestionInfo QuestionInfo;

// SListValue类型定义
typedef void *SListValue;

// SListEntry类型定义
typedef struct _SListEntry SListEntry;
struct _SListEntry {
	SListValue data;
	SListEntry *next;
};

// 函数指针SListCompareFunc
typedef int (*SListCompareFunc)(SListValue value1, SListValue value2);

// 函数指针SListEqualFunc
typedef int (*SListEqualFunc)(SListValue value1, SListValue value2);


/*
    用户结构体，用于存储id，姓名，
    密码等信息
*/

struct _User {
    char id[4];

    // 真实姓名
    char name[MAXNAME];

    // 登录用户名
    char username[MAXNAME];

    // 密码
    char passwd[MAXBUF];

    int ntotal;

    // 正确数量
    int nright;

    // 错误数量
    int nwrong;

    // 是否是管理员
    int is_admin;
    SListEntry *ordered_questions;
};


// 欢迎函数，答应出选项
void welcome();

// 登录前界面
void pre_welcome();

// 释放链表
void slist_free(SListEntry *list);

// 追加链表
SListEntry *slist_append(SListEntry **list, SListValue data);

// 获取链表数据
SListValue slist_data(SListEntry *listentry);


// 查找链表数据
SListEntry *slist_find_data(SListEntry *list,
                            SListEqualFunc callback,
                            SListValue data);

// user inspection

// login登陆成功，应该返回当前用户指针，否则返回NULL
struct _User *login(SListEntry **list);

// 注册用户函数
int regist(SListEntry **list);

// 判断用户是否为管理员
int is_admin();


// 加法运算
void add_cal(SListEntry *, struct _User *);

// 减法运算
void sub_cal(SListEntry *, struct _User *);

// 乘法是运算
void mul_cal(SListEntry *, struct _User *);

// 除法运算
void div_cal(SListEntry *, struct _User *);

// 混合运算
void mix_cal(SListEntry *, struct _User *);

// 分别从5个文件加载数据
int init_questions(
    SListEntry **add_list, 
    SListEntry **sub_list,
    SListEntry **mul_list, 
    SListEntry **div_list, 
    SListEntry **mix_list
    );



// 检查id的回调函数
int callback_check_id(
    SListValue a, 
    SListValue b
    );

// 检查用户名的回调函数
int callback_check_username(
    SListValue a, 
    SListValue b
    );


// 信息统计
int statistic(
     struct _User *current_user
    );


// 插入用户
int insert_user(SListEntry **list, 
    SListValue *value
    );


// 显示用户
void show_userinfo(
    struct _User *p
    );


// 显示问题
void show_questions(
    SListEntry *question_list
    );


// 是否是管理员
int is_admin(struct _User *current_user)
{
    return current_user->is_admin;
}

void pre_welcome()
{
    puts("-------------------");
    puts("欢迎使用小学数学出题系统");
    puts("1:) 登陆");
    puts("2:) 注册");
    puts("-------------------");
}

void add_cal(SListEntry *add_list, struct _User *user)
{
    // 创建指针p， 指向add_list
    SListEntry *p = add_list;

    puts("---加法特训---");


    // 扫描所有节点1
    while (p)
    {
        user->ntotal++;
        QuestionInfo *q = p->data;
        char result[MAXBUF] = { 0 };

        // 输出数据
        printf("题目: %s\n", q->name);
        printf("请输入你的答案:");

        // 输入答案
        scanf("%s", result);

        // 比较正确答案
        if (strcmp(result, q->result) == 0) {
            printf("回答正确!\n");
            
            // 回答正确，记录下来
            user->nright++;
        } else {
            printf("回答错误!\n");

            // 回答错误，记录下来
            user->nwrong++;
        }

        // 指向下一个节点
        p = p->next;
    }
    
}

// 减法运算
void sub_cal(SListEntry *sub_list, struct _User *user)
{
    SListEntry *p = sub_list;

    puts("---减法特训---");

    // 扫描所有节点1
    while (p)
    {

        user->ntotal++;

        QuestionInfo *q = p->data;
        char result[MAXBUF] = { 0 };

        // 输出数据
        printf("题目: %s\n", q->name);
        printf("请输入你的答案:");
        scanf("%s", result);

        if (strcmp(result, q->result) == 0) {
            printf("回答正确!\n");
            user->nright++;
        } else {
            printf("回答错误!\n");
            user->nwrong++;
        }
        p = p->next;
    }
}

void mul_cal(SListEntry *mul_list, struct _User *user)
{
    SListEntry *p = mul_list;

    puts("---乘法特训---");
    while (p)
    {
        user->ntotal++;
        QuestionInfo *q = p->data;
        char result[MAXBUF] = { 0 };

        printf("题目: %s\n", q->name);
        printf("请输入你的答案:");
        scanf("%s", result);

        if (strcmp(result, q->result) == 0) {
            printf("回答正确!\n");
            user->nright++;
        } else {
            printf("回答错误!\n");
            user->nwrong++;
        }
        p = p->next;
    }

}

void div_cal(SListEntry *div_list, struct _User *user)
{
    SListEntry *p = div_list;

    puts("---除法特训---");
    while (p)
    {
        user->ntotal++;
        QuestionInfo *q = p->data;
        char result[MAXBUF] = { 0 };

        printf("题目: %s\n", q->name);
        printf("请输入你的答案:");
        scanf("%s", result);

        if (strcmp(result, q->result) == 0) {
            printf("回答正确!\n");
            user->nright++;
        } else {
            printf("回答错误!\n");
            user->nwrong++;
        }
        p = p->next;
    }

}

void mix_cal(SListEntry *mix_list, struct _User *user)
{
    SListEntry *p = mix_list;

    puts("---混合运算特训---");
    while (p)
    {
        user->ntotal++;
        QuestionInfo *q = p->data;
        char result[MAXBUF] = { 0 };

        printf("题目: %s\n", q->name);
        printf("请输入你的答案:");
        scanf("%s", result);

        if (strcmp(result, q->result) == 0) {
            printf("回答正确!\n");
            user->nright++;
        } else {
            printf("回答错误!\n");
            user->nwrong++;
        }
        p = p->next;
    }

}


// main函数
int main(int argc, char const* argv[])
{
    int input;

    // 题库链表，用于存储题库
    SListEntry *add_list = NULL, *sub_list = NULL, *mul_list = NULL, 

    *div_list = NULL, *mix_list = NULL;

    // 用户链表，用于存储用户
    SListEntry *user_list = NULL;

    // 用户数据结构，用于存储用户信息
    struct _User *user;

    // 指向当前用户
    struct _User *current_user;

start:
    while (1) {
        pre_welcome();
        puts("输入你的选择:");
        scanf("%d", &input);

        switch (input) 
        {
            
            // 用户输入的选项应该小于10
            if (input > 10) {
                break;
            }

            // 用户输入1
            case 1:
                if ((current_user = login(&user_list)) != NULL) {
                    puts("[+] 登陆成功\n\n");
                    goto login_succeed;
                } else {
                    puts("[-] 登陆失败\n\n");
                    break;
                }

            // 用户输入2
            case 2:
                if (regist(&user_list)) {
                    puts("[+] 注册成功]\n\n");
                    break;
                } else {
                    puts("[-] 注册失败\n\n");
                    break;
                }
            case 3:
                ;
        }

    }

login_succeed:
    if (!init_questions(&add_list, &sub_list, &mul_list, &div_list, &mix_list)) {
        puts("数据文件不存在");
        exit(EXIT_FAILURE);
    }

    while (1) {
        welcome();
        puts("");
        puts("输入你的选择:");
        scanf("%d", &input);

        switch (input) {
            case 1:
                // 加法运算
                add_cal(add_list, current_user);
                break;
            case 2:
                // 减法运算
                sub_cal(sub_list, current_user);
                break;
            case 3:
                mul_cal(mul_list, current_user);
                break;
            case 4:
                div_cal(div_list, current_user);
                break;
            case 5:
                mix_cal(mix_list, current_user);
                break;
            case 6:
                statistic(current_user);
                break;
            case 7:
                statistic(current_user);
                exit(EXIT_FAILURE);
            default:
                puts("[-] 输入错误\n\n");
                break;
        }
    }

    return 0;
}

void welcome()
{
    puts("");
    puts("-------------------");
    puts("欢迎使用小学数学出题系统");
    puts("1:) 加法运算");
    puts("2:) 减法运算");
    puts("3:) 乘法运算");
    puts("4:) 除法运算");
    puts("5:) 混合运算");
    puts("6:) 返回上一层");
    puts("7:) 退出系统");
    puts("-------------------");
    puts("");
}


struct _User *login(SListEntry **entry) 
{
    struct _User *new_user;
    SListEntry *p;
    SListValue *data;

    new_user = (struct _User *) malloc(sizeof(struct _User));

    puts("请输入用户名");
    scanf("%s", new_user->username);
    puts("请输入密码:");
    scanf("%s", new_user->passwd);

    p = slist_find_data(*entry, callback_check_username, (SListValue *)new_user);
    if (p == NULL) {
        puts("[-] 用户未注册");
        return NULL;
    } else {
        data = slist_data(p);
        if (strcmp(((struct _User *)data)->username, new_user->username) == 0 &&
        strcmp(((struct _User *)data)->passwd, new_user->passwd) == 0) {
            return (struct _User *)p->data;
        }
    }
    puts("[-] 账号或密码错误");
    return NULL;
}

int regist(SListEntry **entry)
{
    struct _User *new_user;
    SListEntry *p;
    SListValue *data;
    char passwd[MAXBUF], passwd_repeat[MAXBUF];

    new_user = (struct _User *)malloc(sizeof(struct _User));
    puts("请输入id:");
    scanf("%s", new_user->id);
    puts("请输入你的姓名:");
    scanf("%s", new_user->name);
    puts("请输入用户名");
    scanf("%s", new_user->username);
    puts("是否是管理员: 0)否，1)是");
    scanf("%d", &new_user->is_admin);

    while (1) 
    {
        puts("请输入密码:");
        scanf("%s", passwd);
        puts("请输再次入密码:");
        scanf("%s", passwd_repeat);

        if (strcmp(passwd, passwd_repeat) == 0) {
            break;
        } else {
            puts("密码不一致，请重新输入:");
        }
    }

    // 密码设置成功，复制密码
    strcpy(new_user->passwd, passwd);
    // 找到用户名是否存在
    p = slist_find_data(*entry, callback_check_username, (SListValue *)new_user->username);
    if (p == NULL) {
        if (slist_append(entry, (SListValue *)new_user)) {
            puts("[+] 注册成功\n\n");
            return 1;
        }
    } else {
        puts("[-] 用户已注册\n\n");
        return -1;
    }
    puts("[-] 用户注册失败\n\n");
    return -1;
}

int init_questions(SListEntry **add_list, SListEntry **sub_list,
            SListEntry **mul_list, SListEntry **div_list, SListEntry **mix_list)
{
    // 加减乘除，混合运算链表
    QuestionInfo *addition_info = NULL, *subtraction_info = NULL, 
    *multiplication_info = NULL, *division_info = NULL, *mix_operations_info = NULL;
    SListEntry *p = NULL;
    FILE *fp_add = NULL;
    FILE *fp_sub = NULL;
    FILE *fp_mul = NULL;
    FILE *fp_div = NULL;
    FILE *fp_mix = NULL;

    char add_filename[100] = "add.txt";
    char sub_filename[100] = "sub.txt";
    char mul_filename[100] = "mul.txt";
    char div_filename[100] = "div.txt";
    char mix_filename[100] = "mix.txt";
    char data[100] = { 0 };

    // printf("请输入数据文件名:");
    // scanf("%s", filename);

    fp_add = fopen(add_filename, "r");
    if (!fp_add) {
        return -1;
    }
    fp_sub = fopen(sub_filename, "r");
    if (!fp_sub) {
        return -1;
    }
    fp_mul = fopen(mul_filename, "r");
    if (!fp_mul) {
        return -1;
    }
    fp_div = fopen(div_filename, "r");
    if (!fp_div) {
        return -1;
    }

    fp_mix = fopen(mix_filename, "r");
    if (!fp_mix) {
        return -1;
    }

    while (fgets(data, 100, fp_add)) {
        addition_info = malloc(sizeof (struct _QuestionInfo));
        if (addition_info == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        sscanf(data, "%s %s",addition_info->name, addition_info->result);

        if (slist_append(add_list, (SListValue *)addition_info) != NULL) {
            puts("[+] 插入成功\n\n");
        } else {
            puts("[-] 插入失败\n\n");
        }

        // p = slist_find_data(*add_list, callback_check_id, (SListValue *)&addition_info->id);
        // if (p == NULL) {
        //     if (slist_append(add_list, (SListValue *)addition_info) != NULL) {
        //         puts("[+] 插入成功\n\n");
        //     } else {
        //         puts("[-] 插入失败\n\n");
        //     }
        // } else {
        //     puts("[-] 已存在\n\n");
        // }
    }
    puts("读取加法数据成功");

    while (fgets(data, 100, fp_sub)) {
        subtraction_info = malloc(sizeof (struct _QuestionInfo));
        // memset(subtraction_info, 0, sizeof(subtraction_info));
        if (subtraction_info == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        sscanf(data, "%s %s\n",subtraction_info->name, subtraction_info->result);

        if (slist_append(sub_list, (SListValue *)subtraction_info) != NULL) {
            puts("[+] 插入成功\n\n");
        } else {
            puts("[-] 插入失败\n\n");
        }
    }
    puts("读取减法成功");


    while (fgets(data, 100, fp_mul)) {

        // 分配内存
        multiplication_info = malloc(sizeof (struct _QuestionInfo));

        // 判断malloc是否出错
        if (multiplication_info == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        // 从data数组获取数据
        sscanf(data, "%s %s",multiplication_info->name, multiplication_info->result);

        // 看一下添加链表是否出错
        if (slist_append(mul_list, (SListValue *)multiplication_info) != NULL) {
            puts("[+] 插入成功\n\n");
        } else {
            puts("[-] 插入失败\n\n");
        }

    }
    puts("乘法加载成功");

    // 从文件读取内容
    while (fgets(data, 100, fp_div)) {

        // 分配内存
        division_info = malloc(sizeof (struct _QuestionInfo));
        if (division_info == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        // 从数组读取数据
        sscanf(data, "%s %s", division_info->name, division_info->result);


        // 追加链表
        if (slist_append(div_list, (SListValue *)division_info) != NULL) {
            puts("[+] 插入成功\n\n");
        } else {
            puts("[-] 插入失败\n\n");
        }

    }

    // 同上
    while (fgets(data, 100, fp_mix)) {
        mix_operations_info = malloc(sizeof (struct _QuestionInfo));
        if (mix_operations_info == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        sscanf(data, "%s %s", mix_operations_info->name, mix_operations_info->result);

        if (slist_append(mix_list, (SListValue *)mix_operations_info) != NULL) {
            puts("[+] 插入成功\n\n");
        } else {
            puts("[-] 插入失败\n\n");
        }

    }
    puts("除法加载成功");

    fclose(fp_add);
    fclose(fp_sub);
    fclose(fp_mul);
    fclose(fp_div);

    return 1;
}


int callback_check_id(SListValue a, SListValue b)
{
    if (((struct _QuestionInfo *)a)->id == *(int *)b)
        return 1;
    else
        return 0;
}

int callback_check_username(SListValue a, SListValue b)
{
    if (strcmp(((struct _User *)a)->username, ((struct _User *)b)->username) == 0)
        return 1;
    else
        return 0;
}


int insert_user(SListEntry **list, SListValue *user)
{
    SListEntry *p;

    if (slist_append(list, (SListValue *)user) != NULL) {
        puts("[+] 插入用户成功\n\n");
        return 1;
    } else { puts("[-] 插入用户失败\n\n");
        return 0;
    }
}

void slist_free(SListEntry *list)
{
	SListEntry *entry;

	/* Iterate over each entry, freeing each list entry, until the
	 * end is reached */

	entry = list;

	while (entry != NULL) {
		SListEntry *next;

		next = entry->next;

		free(entry);

		entry = next;
	}
}


SListEntry *slist_append(SListEntry **list, SListValue data)
{
	SListEntry *rover;
	SListEntry *newentry;

	/* Create new list entry */

	newentry = malloc(sizeof(SListEntry));

	if (newentry == NULL) {
		return NULL;
	}

	newentry->data = data;
	newentry->next = NULL;


	if (*list == NULL) {


		*list = newentry;

	} else {

		/* Find the end of list */

		for (rover=*list; rover->next != NULL; rover = rover->next);

		/* Add to the end of list */

		rover->next = newentry;
	}

	return newentry;
}

SListValue slist_data(SListEntry *listentry)
{
	return listentry->data;
}




SListEntry *slist_find_data(SListEntry *list,
                            SListEqualFunc callback,
                            SListValue data)
{
	SListEntry *rover;

	/* 
    Iterate over entries in the list until the data is found 
    */

	for (rover=list; rover != NULL; rover=rover->next) {
		if (callback(rover->data, data) != 0) {
			return rover;
		}
	}

	/* Not found */

	return NULL;
}


int statistic(struct _User *current_user)
{
    printf("ID: %d\n", current_user->id);
    printf("姓名: %s\n", current_user->name);
    printf("正确数量: %d\n", current_user->nright);
    printf("错误数量: %d\n", current_user->nwrong);
    printf("正确率: %lf\%\n", (double)current_user->nright / current_user->ntotal);
}