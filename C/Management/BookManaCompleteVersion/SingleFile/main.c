#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#define MAXNAME 254
#define MAXBUF 1024
#define MAXBOOK 100

struct _BookInfo {
    int id;
    char name[MAXNAME];
    char author_name[MAXNAME];
    enum { Novel, Classic, Tech } type;
    int borrow_time;
    int return_time;
    int max_borrow_time;
    // time_t borrowed_time;
};
typedef struct _BookInfo BookInfo;
typedef void *SListValue;

typedef struct _SListEntry SListEntry;
struct _SListEntry {
	SListValue data;
	SListEntry *next;
};


#define SLIST_NULL ((void *) 0)

typedef int (*SListCompareFunc)(SListValue value1, SListValue value2);
typedef int (*SListEqualFunc)(SListValue value1, SListValue value2);



struct _Enroll {
    char id[4];
    int num_borrow;
    char name[MAXNAME];
    char username[MAXNAME];
    char passwd[MAXBUF];
    SListEntry *borrowed_book;
    enum { TEACHER, STUDENT } type;
};

void welcome();
void pre_welcome();
void slist_free(SListEntry *list);

SListEntry *slist_append(SListEntry **list, SListValue data);

SListEntry *slist_next(SListEntry *listentry);

SListValue slist_data(SListEntry *listentry);


int slist_remove_entry(SListEntry **list, SListEntry *entry);
unsigned int slist_remove_data(SListEntry **list,
                               SListEqualFunc callback,
                               SListValue data);

SListEntry *slist_find_data(SListEntry *list,
                            SListEqualFunc callback,
                            SListValue data);



// user inspection

// login登陆成功，应该返回当前用户指针，否则返回NULL
struct _Enroll *login(SListEntry **list);
int regist(SListEntry **list);
int forget_passwd(SListEntry **list);

int insert_book(SListEntry **list);
int delete_book(SListEntry **list);
int delete_book_by_id(SListEntry **list, int id);
int modify_book(SListEntry **list);
int query_book(SListEntry **list);
int query_book_by_id(SListEntry **list, int id);
int callback_check_id(SListValue a, SListValue b);
int callback_check_username(SListValue a, SListValue b);

int borrow_book(struct _Enroll *user, SListEntry *book_list);
int return_book(struct _Enroll *user,SListEntry *book_list);
int statistic(SListEntry *book_list);

// 初始化学生和教师可以借的书的数量和天数
void teacher_borrow(struct _BookInfo *p);
void student_borrow(struct _BookInfo *p);
struct _Enroll *ask_user_info(struct _Enroll *p);
int insert_user(SListEntry **list, SListValue *value);
void show_userinfo(struct _Enroll *p);
void show_books(SListEntry *book_list);

int fix_bug = 0;

void pre_welcome()
{
    puts("1:) 登陆");
    puts("2:) 注册");
    puts("3:) 忘记密码");
    puts("4: Hack me");
    puts("5:) Buy me a ccooffee");
}

int main(int argc, char const* argv[])
{
    int input;
    // 图书链表，用于存储图书
    SListEntry *book_list = NULL;
    // 用户链表，用于存储用户
    SListEntry *user_list = NULL;
    struct _Enroll *user;
    struct _Enroll *current_user;

    while (1) {
        pre_welcome();
        puts("输入你的选择:");
        scanf("%d", &input);

        switch (input) 
        {
            if (input > 10) {
                break;
            }
            case 1:
                if ((current_user = login(&user_list)) != NULL) {
                    puts("[+] 登陆成功\n\n");
                    goto login_succeed;
                } else {
                    puts("[-] 登陆失败\n\n");
                    break;
                }
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
                // if (forget_passwd(&user_list)) {
                //     puts("找回密码成功");
                //     break;
                // } else {
                //     puts("找回密码失败");
                //     break;
                // }
        }

    }

login_succeed:
    while (1) {
        welcome();
        puts("");
        puts("输入你的选择:");
        scanf("%d", &input);

        switch (input) {
            case 1:
                // TODO: should add user registion
                // TODO: should check if user already in user_list
                // TODO: user_list and book_list data should be stored in a file or database, provide read and write function
                // if (!is_in_sll(user, user_list, callback)) {
                //     insert_user()
                // }
                if (current_user->type != TEACHER) {
                    printf("[-] 学生不能添加图书\n\n\n");
                    break;
                }
                // 添加图书
                insert_book(&book_list);
                break;
            case 2:
                if (current_user->type != TEACHER) {
                    printf("[-] 学生不能删除图书\n\n\n");
                    break;
                }
                // 删除图书
                delete_book(&book_list);
                break;
            case 3:
                if (current_user->type != TEACHER) {
                    printf("[-] 学生不能修改图书\n\n\n");
                    break;
                }
                // 修改图书
                modify_book(&book_list);
                break;
            case 4:
                // 不用检查身份
                query_book(&book_list);
                break;
            case 5:
                borrow_book(current_user, book_list);
                break;
            case 6:
                // 还书
                return_book(current_user, book_list);
                break;
            case 7:
                show_userinfo(current_user);
                break;
            case 8:
                // statistic(book_list);
                break;
            case 9:
                show_books(book_list);
                break;
            case 10:
                exit(EXIT_SUCCESS);
            default:
                puts("[-] 输入错误\n\n");
                break;
        }
    }

    slist_free(book_list);
    return 0;
}

void welcome()
{
    puts("");
    puts("-------------------");
    puts("欢迎使用图书管理系统");
    puts("1:) 添加一本图书");
    puts("2:) 删除一本图书");
    puts("3:) 修改一本图书");
    puts("4:) 查询一本图书");
    puts("5:) 借书");
    puts("6:) 还书");
    puts("7:) 查看用户借还信息");
    puts("8:) 统计");
    puts("9:) 查看剩余图书");
    puts("10:) 退出");
    puts("-------------------");
    puts("");
}


struct _Enroll *login(SListEntry **entry) 
{
    struct _Enroll *new_user;
    SListEntry *p;
    SListValue *data;

    new_user = (struct _Enroll *) malloc(sizeof(struct _Enroll));

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
        if (strcmp(((struct _Enroll *)data)->username, new_user->username) == 0 &&
        strcmp(((struct _Enroll *)data)->passwd, new_user->passwd) == 0) {
            return (struct _Enroll *)p->data;
        }
    }
    puts("[-] 账号或密码错误");
    return NULL;
}

int regist(SListEntry **entry)
{
    struct _Enroll *new_user;
    SListEntry *p;
    SListValue *data;
    char passwd[MAXBUF], passwd_repeat[MAXBUF];

    new_user = (struct _Enroll *)malloc(sizeof(struct _Enroll));
    puts("请输入id:");
    scanf("%s", new_user->id);
    puts("请输入你的姓名:");
    scanf("%s", new_user->name);
    puts("请输入你的职位 0:老师, 1学生:");
    scanf("%d", &new_user->type);
    puts("请输入用户名");
    scanf("%s", new_user->username);

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

// int query_book_by_id(SListEntry **entry, int id)
// {
//     SListEntry *p;
// 	SListEntry *rover;
//     SListValue *data;
// 
//     p = slist_find_data(*entry, callback_check_id, (SListValue *)&id);
//     if (p == NULL) {
//         puts("-------------------");
//         puts("未查询到数据");
//         puts("-------------------");
//         return -1;
//     } else {
//         data = slist_data(p);
// 
//         puts("----------------------");
//         printf("查询结果如下\n");
//         // 这里需要强制转换
//         printf("id:%d\n", ((struct _BookInfo *)data)->id);
//         printf("书名:%s\n", ((struct _BookInfo *)data)->name);
//         printf("作者:%s\n", ((struct _BookInfo *)data)->author_name);
//         puts("----------------------");
//     }
//     return 1;
// }

int insert_book(SListEntry **list)
{
    BookInfo *book_info;
    SListEntry *p;

    book_info = malloc(sizeof (struct _BookInfo));
    if (book_info == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    puts("输入书本id:");
    scanf("%d", &book_info->id);
    puts("输入书本名字:");
    scanf("%s", book_info->name);
    puts("输入书本作者:");
    scanf("%s", book_info->author_name);
    puts("请输入书的种类: 1)Novel 2)Classic 3)Tech");
    scanf("%d", &book_info->type);
    puts("");

    p = slist_find_data(*list, callback_check_id, (SListValue *)&book_info->id);
    if (p == NULL) {
        if (slist_append(list, (SListValue *)book_info) != NULL) {
            puts("[+] 插入成功\n\n");
            return 1;
        } else {
            puts("[-] 插入失败\n\n");
            return 0;
        }
    } else {
        puts("[-] 此书已存在\n\n");
        return -1;
    }
    return 1;
}

int delete_book(SListEntry **entry)
{
    int id;

    puts("输入要删除书本的id:");
    scanf("%d", &id);
    delete_book_by_id(entry, id);

    return 1;
}

int delete_book_by_id(SListEntry **entry, int id)
{
    SListEntry *p;
    SListValue *value;
    struct _BookInfo *book_info;

    // 删书有三种情况, 第一 图书馆没有此书, 第二 图书馆有多本此书(只需num_left--)，
    // 第三 图书馆只有一本书(需要删除节点)
    p = slist_find_data(*entry, callback_check_id, (SListValue *)&id);
    if (p == NULL) {
        puts("-------------------");
        puts("此书不存在");
        puts("-------------------");
        return -1;
    } else {
        value = slist_data(p);
        book_info = (struct _BookInfo *) value;
        if (slist_remove_entry(entry, p) == 0) {
            puts("[-] 删除数据失败\n\n");
            return -1;
        } else {
            puts("[+] 删除成功\n\n");
            return 1;
        }
    }
    puts("");
}

int callback_check_id(SListValue a, SListValue b)
{
    if (((struct _BookInfo *)a)->id == *(int *)b)
        return 1;
    else
        return 0;
}

int callback_check_username(SListValue a, SListValue b)
{
    if (strcmp(((struct _Enroll *)a)->username, ((struct _Enroll *)b)->username) == 0)
        return 1;
    else
        return 0;
}

int query_book(SListEntry **entry)
{
    int id;

    puts("请输入要查询的id:");
    scanf("%d", &id);
    query_book_by_id(entry, id);

    return 1;
}

int query_book_by_id(SListEntry **entry, int id)
{
    SListEntry *p;
	SListEntry *rover;
    SListValue *data;

    p = slist_find_data(*entry, callback_check_id, (SListValue *)&id);
    if (p == NULL) {
        puts("[-] 未查询到数据\n\n");
        return -1;
    } else {
        data = slist_data(p);

        puts("----------------------");
        printf("查询结果如下\n");
        // 这里需要强制转换
        printf("id:%d\n", ((struct _BookInfo *)data)->id);
        printf("书名:%s\n", ((struct _BookInfo *)data)->name);
        printf("作者:%s\n", ((struct _BookInfo *)data)->author_name);
        puts("----------------------");
    }
    return 1;
}

int modify_book(SListEntry **entry)
{
    return 0;
}

int borrow_book(struct _Enroll *user, SListEntry *book_list)
{
    int id;
    SListEntry *book;

    puts("输入你要借的书的id:");
    scanf("%d", &id);

    book = slist_find_data(book_list, callback_check_id, (SListValue *)&id);
    if (book == NULL) {
        puts("[-] 此书不存在");
        return -1;
    }

    // puts("输入借书时间:");
    // scanf("%d", &p->time_borrow);
    // // 检查最大借书数量
    // if (p->num_borrow > p->max_num_borrow) {
    //     puts("超过最大借书数量");
    //     return -1;
    // }

    // 将书添加至 用户的借书链表之中
    if (!slist_append(&user->borrowed_book, book->data)) {
        puts("[-] 添加图书至用至用户借书链表失败\n\n");
        return -1;
    }
    user->num_borrow++;

    // 将原有的图书链表删掉数据
    if (!slist_remove_entry(&book_list, book)) {
        puts("[-] 删除图书失败");
        return -1;
    }

    puts("[+] 借书成功\n\n");
    return 1;
}

int return_book(struct _Enroll *user, SListEntry *book_list)
{
    int id;
    SListEntry *entry;

    puts("输入你要还的书的id:");
    scanf("%d", &id);

    // 在用户链表中找到此书
    entry = slist_find_data(user->borrowed_book, callback_check_id, (SListValue *)&id);
    if (entry == NULL) {
        puts("[-] 用户未借此书\n\n");
        return -1;
    }

    // 从用户借书链表中删除
    if (!slist_remove_entry(&user->borrowed_book, entry)) {
        puts("[-] 从用户借书链表中删除出错\n\n");
        return -1;
    }

    user->num_borrow--;

    if (!slist_append(&book_list, entry)) {
        puts("[-] 将用户书归还时出错\n\n\n");
        return -1;
    }

    puts("[+] 还书成功\n\n");
    return 1;
}

// 初始化学生和老师的限制量
void teacher_borrow(struct _BookInfo *p)
{
    // p->max_num_borrow = 15;
    // p->max_time_borrow = 180;
}

void student_borrow(struct _BookInfo *p)
{
    // p->max_time_borrow = 10;
    // p->max_time_borrow = 120;
}

struct _Enroll *ask_user_info(struct _Enroll *p)
{
    struct _Enroll *user;

    user = malloc(sizeof(struct _Enroll));
    if (user == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    p = malloc(sizeof(struct _Enroll));
    if (p == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    // 复制内存
    memcpy(user, p, sizeof(struct _Enroll));

    puts("您的名字是:");
    scanf("%s", user->name);
    puts("您的学号是:");
    scanf("%s", user->id);
    puts("您的身份是 0:)老师, 1:)学生:");
    scanf("%d", &user->type);

    return user;
}

int insert_user(SListEntry **list, SListValue *user)
{
    SListEntry *p;

    if (slist_append(list, (SListValue *)user) != NULL) {
        puts("[+] 插入用户成功\n\n");
        return 1;
    } else {
        puts("[-] 插入用户失败\n\n");
        return 0;
    }
}

void show_userinfo(struct _Enroll *p)
{
    SListEntry *temp;

    puts("-------------------");
    printf("用户名:%s\n", p->name);
    // printf("所借数量:%d\n", t->num_borrow);
    printf("所借数量:%d\n", p->num_borrow);

    if (!p->borrowed_book) {
        puts("用户未借任何书籍");
        return;
    }

    temp = p->borrowed_book;
    while (temp) {
        printf("书名: %s\n", ((struct _BookInfo *)temp->data)->name);
        temp = temp->next;
    }
}

void show_books(SListEntry *book_list)
{
    SListValue *value;
    SListEntry *p = book_list;

    int n = 0;
    puts("-------------------");
    while (p != NULL) {
        value = p->data;

        if (!value)
            break;

        printf("ID:%d\t", ((struct _BookInfo *) value)->id);
        printf("书名:%s\t", ((struct _BookInfo *) value)->name);
        printf("作者:%s\t", ((struct _BookInfo *) value)->author_name);
        puts("");

        p = p->next;
        n++;
    }
    puts("-------------------");

    if (n == 0) {
        puts("[-] 未查询到任何数据\n\n");
    }
}

// int statistic(SListEntry *book_list)
// {
//     int id;
//     int n = 0;
//     SListEntry *p;
//     int num_borrowed, num_left;
// 
//     puts("-------------------");
//     puts("图书统计如下:");
// 
//     p = book_list;
//     while (p != NULL) {
//         id = ((struct _BookInfo *)p->data)->id;
//         num_left = ((struct _BookInfo *)p->data)->num_left;
//         num_borrowed = ((struct _BookInfo *)p->data)->num_borrowed;
// 
//         printf("书本id:%d 剩余数量:%d 借书数量:%d\n", id, num_left, num_borrowed);
//         // printf("书本id:%d 借书率:%lf\n", id, ((double) num_left) / num_borrowed);
//         n++;
//         p = p->next;
//     }
//     puts("-------------------");
// 
//     if (n == 0) {
//         puts("没有任何数据");
//     }
// }
// 
//
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


SListEntry *slist_next(SListEntry *listentry)
{
	return listentry->next;
}

int slist_remove_entry(SListEntry **list, SListEntry *entry)
{
	SListEntry *rover;

	/* If the list is empty, or entry is NULL, always fail */

	if (*list == NULL || entry == NULL) {
		return 0;
	}

	/* Action to take is different if the entry is the first in the list */

	if (*list == entry) {

		/* Unlink the first entry and update the starting pointer */

		*list = entry->next;

	} else {


		rover = *list;

		while (rover != NULL && rover->next != entry) {
			rover = rover->next;
		}

		if (rover == NULL) {


			return 0;

		} else {


			rover->next = entry->next;
		}
	}

	/* Free the list entry */

	free(entry);

	/* Operation successful */

	return 1;
}



SListEntry *slist_find_data(SListEntry *list,
                            SListEqualFunc callback,
                            SListValue data)
{
	SListEntry *rover;

	/* Iterate over entries in the list until the data is found */

	for (rover=list; rover != NULL; rover=rover->next) {
		if (callback(rover->data, data) != 0) {
			return rover;
		}
	}

	/* Not found */

	return NULL;
}

