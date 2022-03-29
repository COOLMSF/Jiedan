#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#define MAXNAME 254
#define MAXBUF 1024
#define MAXgood 100

struct _TeamInfo {
    int id;
    char name[MAXNAME];
    char sell_date[MAXNAME];
    int ntotal;
    int nsell;
    double price;
};
typedef struct _TeamInfo teamInfo;
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
    SListEntry *buied_goods;
    enum { ADMIN, USER } type;
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

int insert_enroll(SListEntry **list);
int delete_team(SListEntry **list);
int delete_team_by_id(SListEntry **list, int id);
int modify_people(SListEntry **list);
int query_people(SListEntry **list);
int query_people_by_id(SListEntry **list, int id);
int buy_good(struct _Enroll *user, SListEntry *good_list);
int callback_check_id(SListValue a, SListValue b);
int callback_check_username(SListValue a, SListValue b);
int insert_user(SListEntry **list, SListValue *value);
void show_userinfo(struct _Enroll *p);
void show_people(SListEntry *good_list);


void pre_welcome()
{
    puts("1:) 登陆");
    puts("2:) 注册");
    puts("3:) 忘记密码");
}

int main(int argc, char const* argv[])
{
    int input;
    // 商品链表，用于存储商品
    SListEntry *good_list = NULL;
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
            if (input > 2) {
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
                if (current_user->type != ADMIN) {
                    printf("[-] 用户不能添加商品\n\n\n");
                    break;
                }
                // 添加商品
                insert_enroll(&good_list);
                break;
            case 2:
                if (current_user->type != ADMIN) {
                    printf("[-] 用户不能删除商品\n\n\n");
                    break;
                }
                // 删除商品
                delete_team(&good_list);
                break;
            case 3:
                if (current_user->type != ADMIN) {
                    printf("[-] 用户不能修改商品\n\n\n");
                    break;
                }
                // 修改商品
                modify_people(&good_list);
                break;
            case 4:
                // 不用检查身份
                query_people(&good_list);
                break;
            case 5:
                buy_good(current_user, good_list);
                break;
            case 6:
                show_userinfo(current_user);
                break;
            case 7:
                show_people(good_list);
                break;
            case 8:
                exit(EXIT_SUCCESS);
            default:
                puts("[-] 输入错误\n\n");
                break;
        }
    }

    slist_free(good_list);
    return 0;
}

void welcome()
{
    puts("");
    puts("-------------------");
    puts("欢迎使用商品管理系统");
    puts("1:) 添加一种商品");
    puts("2:) 删除一种商品");
    puts("3:) 修改一种商品");
    puts("4:) 查询一种商品");
    puts("5:) 购买商品");
    puts("6:) 查看用户购买还信息");
    puts("7:) 查看剩余商品");
    puts("8:) 退出");
    puts("-------------------");
    puts("");
}

// 登录函数
struct _Enroll *login(SListEntry **entry) 
{
    // 用户结构体，用于存储新的用户数据
    struct _Enroll *new_user;
    SListEntry *p;
    SListValue *data;

    // 分配内存
    new_user = (struct _Enroll *) malloc(sizeof(struct _Enroll));

    // 获取用户信息
    puts("请输入用户名");
    scanf("%s", new_user->username);
    puts("请输入密码:");
    scanf("%s", new_user->passwd);

    // 查找链表里面是否有该用户
    p = slist_find_data(*entry, callback_check_username, (SListValue *)new_user);
    if (p == NULL) {
        puts("[-] 用户未注册");
        return NULL;
    } else {
        data = slist_data(p);
        // 检查用户名
        if (strcmp(((struct _Enroll *)data)->username, new_user->username) == 0 &&
        // 检查用户密码
        strcmp(((struct _Enroll *)data)->passwd, new_user->passwd) == 0) {
            return (struct _Enroll *)p->data;
        }
    }
    puts("[-] 账号或密码错误");
    return NULL;
}

// 注册函数
int regist(SListEntry **entry)
{
    struct _Enroll *new_user;
    SListEntry *p;
    SListValue *data;
    char passwd[MAXBUF], passwd_repeat[MAXBUF];

    // 分配内存
    new_user = (struct _Enroll *)malloc(sizeof(struct _Enroll));

    // 输入用户信息
    puts("请输入id:");
    scanf("%s", new_user->id);
    puts("请输入你的姓名:");
    scanf("%s", new_user->name);
    puts("请输入你的身份 0:管理员, 1:用户:");
    scanf("%d", &new_user->type);
    puts("请输入用户名");
    scanf("%s", new_user->username);

    while (1) 
    {
        puts("请输入密码:");
        scanf("%s", passwd);
        puts("请输再次入密码:");
        scanf("%s", passwd_repeat);

        // 比较两次密码
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

// 插入商品
int insert_enroll(SListEntry **list)
{
    // 商品信息
    teamInfo *good_info;
    SListEntry *p;

    // 分配内存
    good_info = malloc(sizeof (struct _TeamInfo));
    if (good_info == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    puts("输入商品id:");
    scanf("%d", &good_info->id);
    puts("输入商品名字:");
    scanf("%s", good_info->name);
    puts("输入商品价格:");
    scanf("%lf", &good_info->price);
    puts("输入商品数量:");
    scanf("%d", &good_info->ntotal);
    puts("");

    p = slist_find_data(*list, callback_check_id, (SListValue *)&good_info->id);
    if (p == NULL) {
        if (slist_append(list, (SListValue *)good_info) != NULL) {
            puts("[+] 插入成功\n\n");
            return 1;
        } else {
            puts("[-] 插入失败\n\n");
            return 0;
        }
    } else {
        puts("[-] 此商品已存在\n\n");
        return -1;
    }
    return 1;
}

int delete_team(SListEntry **entry)
{
    int id;

    puts("输入要删除商品的id:");
    scanf("%d", &id);
    delete_team_by_id(entry, id);

    return 1;
}

int delete_team_by_id(SListEntry **entry, int id)
{
    SListEntry *p;
    SListValue *value;
    struct _TeamInfo *good_info;

    // 找到节点，并且删除
    p = slist_find_data(*entry, callback_check_id, (SListValue *)&id);
    if (p == NULL) {
        puts("-------------------");
        puts("此商品不存在");
        puts("-------------------");
        return -1;
    } else {
        value = slist_data(p);
        good_info = (struct _TeamInfo *) value;
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

// 检查id的回调函数
int callback_check_id(SListValue a, SListValue b)
{
    if (((struct _TeamInfo *)a)->id == *(int *)b)
        return 1;
    else
        return 0;
}

// 检查用户名的回调函数
int callback_check_username(SListValue a, SListValue b)
{
    if (strcmp(((struct _Enroll *)a)->username, ((struct _Enroll *)b)->username) == 0)
        return 1;
    else
        return 0;
}

// 查询商品
int query_people(SListEntry **entry)
{
    int id;

    puts("请输入要查询的id:");
    scanf("%d", &id);
    query_people_by_id(entry, id);

    return 1;
}

// 根据id查询商品
int query_people_by_id(SListEntry **entry, int id)
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
        printf("id:%d\n", ((struct _TeamInfo *)data)->id);
        printf("商品名:%s\n", ((struct _TeamInfo *)data)->name);
        printf("价格:%lf\n", ((struct _TeamInfo *)data)->price);
        puts("----------------------");
    }
    return 1;
}

int modify_people(SListEntry **entry)
{
    return 0;
}

int buy_good(struct _Enroll *user, SListEntry *good_list)
{
    int id;
    SListEntry *good;

    puts("输入你要购买的商品的id:");
    scanf("%d", &id);

    good = slist_find_data(good_list, callback_check_id, (SListValue *)&id);
    if (good == NULL) {
        puts("[-] 此商品不存在");
        return -1;
    }
    // 商品卖的数量+1
    ((teamInfo *)good->data)->nsell++;

    // 将商品添加至 用户的购买商品链表之中
    if (!slist_append(&user->buied_goods, good->data)) {
        puts("[-] 添加商品至用至用户购买商品链表失败\n\n");
        return -1;
    }

    puts("[+] 购买商品成功\n\n");
    return 1;
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
    // printf("所购买数量:%d\n", t->num_borrow);
    printf("所购买数量:%d\n", p->num_borrow);

    if (!p->buied_goods) {
        puts("用户未购买任何商品");
        return;
    }

    temp = p->buied_goods;
    while (temp) {
        printf("商品名: %s\n", ((struct _TeamInfo *)temp->data)->name);
        temp = temp->next;
    }
}

void show_people(SListEntry *good_list)
{
    SListValue *value;
    SListEntry *p = good_list;

    int n = 0;
    puts("-------------------");
    while (p != NULL) {
        value = p->data;

        if (!value)
            break;

        printf("ID:%d\t", ((struct _TeamInfo *) value)->id);
        printf("商品名:%s\t", ((struct _TeamInfo *) value)->name);
        printf("商品价格:%lf\t", ((struct _TeamInfo *) value)->price);
        printf("商品总数量:%d\t", ((struct _TeamInfo *) value)->ntotal);
        printf("商品销售数量:%d\t", ((struct _TeamInfo *) value)->nsell);
        puts("");

        p = p->next;
        n++;
    }
    puts("-------------------");

    if (n == 0) {
        puts("[-] 未查询到任何数据\n\n");
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

