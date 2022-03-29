#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#define MAXNAME 254
#define MAXBUF 1024
#define MAXBOOK 100

#define SLIST_NULL ((void *) 0)

struct _DishesInfo {
    int id;
    char name[MAXNAME];
    double price;
    // time_t borrowed_time;
};
typedef struct _DishesInfo DishesInfo;
typedef void *SListValue;

typedef struct _SListEntry SListEntry;
struct _SListEntry {
	SListValue data;
	SListEntry *next;
};

typedef int (*SListCompareFunc)(SListValue value1, SListValue value2);
typedef int (*SListEqualFunc)(SListValue value1, SListValue value2);

struct _User {
    char id[4];
    char name[MAXNAME];
    char username[MAXNAME];
    char passwd[MAXBUF];
    int is_admin;
    SListEntry *ordered_dishes;
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
struct _User *login(SListEntry **list);
int regist(SListEntry **list);
int forget_passwd(SListEntry **list);
int is_admin();


int init_dishes(SListEntry **list);
int insert_dish(SListEntry **list);
int delete_dish(SListEntry **list);
int delete_dish_by_id(SListEntry **list, int id);
int modify_dish(SListEntry **list);
int query_dish(SListEntry **list);
int query_dish_by_id(SListEntry **list, int id);
int callback_check_id(SListValue a, SListValue b);
int callback_check_username(SListValue a, SListValue b);

int checkout(struct _User *user);
int order_dish(struct _User *user, SListEntry *dishes_list);
int return_dish(struct _User *user,SListEntry *dishes_list);
int statistic(SListEntry *dishes_list);

struct _User *ask_user_info(struct _User *p);
int insert_user(SListEntry **list, SListValue *value);
void show_userinfo(struct _User *p);
void show_dishes(SListEntry *dishes_list);

int is_admin(struct _User *current_user)
{
    return current_user->is_admin;
}

void pre_welcome()
{
    puts("-------------------");
    puts("欢迎使用酒店点餐管理系统");
    puts("1:) 登陆");
    puts("2:) 注册");
    puts("-------------------");
    // puts("3:) 忘记密码");
}

int main(int argc, char const* argv[])
{
    int input;
    // 菜品链表，用于存储菜品
    SListEntry *dishes_list = NULL;
    // 用户链表，用于存储用户
    SListEntry *user_list = NULL;
    struct _User *user;
    struct _User *current_user;

start:
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
        }

    }

login_succeed:
    if (!init_dishes(&dishes_list)) {
        puts("菜单数据文件不存在，请手动添加");
    }

    while (1) {
        welcome();
        puts("");
        puts("输入你的选择:");
        scanf("%d", &input);

        switch (input) {
            case 1:
                if (!is_admin(current_user)) {
                    puts("非管理员不能添加菜品");
                    continue;
                }
                // 添加菜品
                insert_dish(&dishes_list);
                break;
            case 2:
                if (!is_admin(current_user)) {
                    puts("非管理员不能删除菜品");
                    continue;
                }
                // 删除菜品
                delete_dish(&dishes_list);
                break;
            case 3:
                if (!is_admin(current_user)) {
                    puts("非管理员不能修改菜品");
                    continue;
                }
                // 修改菜品
                modify_dish(&dishes_list);
                break;
            case 4:
                // 不用检查身份
                // 查询菜品
                query_dish(&dishes_list);
                break;
            case 5:
                // 订餐
                order_dish(current_user, dishes_list);
                break;
            case 6:
                // 取消
                return_dish(current_user, dishes_list);
                break;
            case 7:
                // 显示用户信息
                show_userinfo(current_user);
                break;
            case 8:
                // statistic(dishes_list);
                break;
            case 9:
                show_dishes(dishes_list);
                break;
            case 10:
                checkout(current_user);
                break;
            case 11:
                // exit(EXIT_SUCCESS);
                goto start;
            default:
                puts("[-] 输入错误\n\n");
                break;
        }
    }

    slist_free(dishes_list);
    return 0;
}

void welcome()
{
    puts("");
    puts("-------------------");
    puts("欢迎使用酒店点餐管理系统");
    puts("1:) 添加菜品");
    puts("2:) 删除菜品");
    puts("3:) 修改菜品");
    puts("4:) 查询菜品");
    puts("5:) 订餐");
    puts("6:) 退单");
    puts("7:) 查看用户信息");
    puts("8:) 统计");
    puts("9:) 查看菜品");
    puts("10:) 结账");
    puts("11:) 返回上一层");
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

int init_dishes(SListEntry **list)
{
    DishesInfo *dish_info;
    SListEntry *p;
    FILE *fp;
    char filename[100] = "dishes.txt";
    char data[100] = { 0 };

    // printf("请输入数据文件名:");
    // scanf("%s", filename);

    fp = fopen(filename, "r");
    if (!fp) {
        return -1;
    }

    while (fgets(data, 100, fp)) {
        dish_info = malloc(sizeof (struct _DishesInfo));
        if (dish_info == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        sscanf(data, "%d %s %lf", &dish_info->id, dish_info->name, &dish_info->price);

        p = slist_find_data(*list, callback_check_id, (SListValue *)&dish_info->id);
        if (p == NULL) {
            if (slist_append(list, (SListValue *)dish_info) != NULL) {
                puts("[+] 插入成功\n\n");
            } else {
                puts("[-] 插入失败\n\n");
            }
        } else {
            puts("[-] 菜品已存在\n\n");
        }
    }

    return 1;
}

int insert_dish(SListEntry **list)
{
    DishesInfo *dish_info;
    SListEntry *p;

    dish_info = malloc(sizeof (struct _DishesInfo));
    if (dish_info == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    puts("输入菜品id:");
    scanf("%d", &dish_info->id);
    puts("输入菜品名字:");
    scanf("%s", dish_info->name);
    puts("输入菜品价格:");
    scanf("%lf", &dish_info->price);
    puts("");

    p = slist_find_data(*list, callback_check_id, (SListValue *)&dish_info->id);
    if (p == NULL) {
        if (slist_append(list, (SListValue *)dish_info) != NULL) {
            puts("[+] 插入成功\n\n");
            return 1;
        } else {
            puts("[-] 插入失败\n\n");
            return 0;
        }
    } else {
        puts("[-] 菜品已存在\n\n");
        return -1;
    }
    return 1;
}

int delete_dish(SListEntry **entry)
{
    int id;

    puts("输入要删除菜品的id:");
    scanf("%d", &id);
    delete_dish_by_id(entry, id);

    return 1;
}

int delete_dish_by_id(SListEntry **entry, int id)
{
    SListEntry *p;
    SListValue *value;
    struct _DishesInfo *dish_info;

    p = slist_find_data(*entry, callback_check_id, (SListValue *)&id);
    if (p == NULL) {
        puts("-------------------");
        puts("此菜品不存在");
        puts("-------------------");
        return -1;
    } else {
        value = slist_data(p);
        dish_info = (struct _DishesInfo *) value;
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
    if (((struct _DishesInfo *)a)->id == *(int *)b)
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

int query_dish(SListEntry **entry)
{
    int id;

    puts("请输入要查询的id:");
    scanf("%d", &id);
    query_dish_by_id(entry, id);

    return 1;
}

int query_dish_by_id(SListEntry **entry, int id)
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
        printf("id:%d\n", ((struct _DishesInfo *)data)->id);
        printf("菜品名:%s\n", ((struct _DishesInfo *)data)->name);
        printf("价格:%lf\n", ((struct _DishesInfo *)data)->price);
        puts("----------------------");
    }
    return 1;
}

int modify_dish(SListEntry **entry)
{
    return 0;
}


int checkout(struct _User *user)
{
    double total_price = 0;
    SListEntry *entry;
    struct _DishesInfo *dishes_info;

    if (user->ordered_dishes == NULL) {
        puts("该用户未点餐");
        return -1;
    }
    entry = user->ordered_dishes;
    dishes_info = (struct _DishesInfo *)entry->data;


    while (entry != NULL)
    {
        total_price += dishes_info->price;
        entry = entry->next;
    }
    
    printf("总价:%lf，微信还是支付宝^_^？", total_price);
    return 1;
}

int order_dish(struct _User *user, SListEntry *dishes_list)
{
    int id;
    SListEntry *dish;

    puts("输入你要订菜的id:");
    scanf("%d", &id);

    dish = slist_find_data(dishes_list, callback_check_id, (SListValue *)&id);
    if (dish == NULL) {
        puts("[-] 菜品不存在");
        return -1;
    }


    // 将菜品添加至 用户的点餐链表之中
    if (!slist_append(&user->ordered_dishes, dish->data)) {
        puts("[-] 添加菜品失败\n\n");
        return -1;
    }

    // 将原有的链表删掉数据
    if (!slist_remove_entry(&dishes_list, dish)) {
        puts("[-] 删除菜品失败");
        return -1;
    }

    puts("[+] 订餐成功\n\n");
    return 1;
}

int return_dish(struct _User *user, SListEntry *dishes_list)
{
    int id;
    SListEntry *entry;

    puts("输入你要还的菜品的id:");
    scanf("%d", &id);

    // 在用户链表中找到菜品
    entry = slist_find_data(user->ordered_dishes, callback_check_id, (SListValue *)&id);
    if (entry == NULL) {
        puts("[-] 用户未定该菜品\n\n");
        return -1;
    }

    // 从用户菜品链表中删除
    if (!slist_remove_entry(&user->ordered_dishes, entry)) {
        puts("[-] 从用户菜品链表中删除出错\n\n");
        return -1;
    }

    if (!slist_append(&dishes_list, entry)) {
        puts("[-] 退单时出错\n\n\n");
        return -1;
    }

    puts("[+] 退单成功\n\n");
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

void show_userinfo(struct _User *p)
{
    SListEntry *temp;

    puts("-------------------");
    printf("用户名:%s\n", p->name);

    if (!p->ordered_dishes) {
        puts("用户未任何点餐记录");
        return;
    }

    temp = p->ordered_dishes;
    while (temp) {
        printf("菜品名称: %s\n", ((struct _DishesInfo *)temp->data)->name);
        printf("菜品价格: %lf\n", ((struct _DishesInfo *)temp->data)->price);
        puts("");
        temp = temp->next;
    }
}

void show_dishes(SListEntry *dishes_list)
{
    SListValue *value;
    SListEntry *p = dishes_list;

    int n = 0;
    puts("-------------------");
    while (p != NULL) {
        value = p->data;

        if (!value)
            break;

        printf("ID:%d\t", ((struct _DishesInfo *) value)->id);
        printf("菜品名称:%s\t", ((struct _DishesInfo *) value)->name);
        printf("菜品价格:%lf\t", ((struct _DishesInfo *) value)->price);
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

