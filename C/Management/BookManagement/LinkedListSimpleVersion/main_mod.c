#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "slist.h"

#define MAXNAME 254
#define MAXBUF 1024
#define MAXBOOK 100

struct _BookInfo {
    int id;
    int num_borrowed;
    int num_left;
    enum { Novel, Classic, Tech } type;
    char name[MAXNAME];
    char author_name[MAXNAME];
};
typedef struct _BookInfo BookInfo;

struct _User {
    char id[4];
    char name[MAXNAME];
    int num_borrow;
    // time_t time_borrow;
    // time_t time_return;
    int time_borrow;
    int time_return;
    int max_num_borrow;
    int max_time_borrow;
    SListEntry *borrowed_bookid;
    SListEntry *borrowed_bookname;
    enum { TEACHER, STUDENT } type;
};

void welcome();
int insert_book(SListEntry **list);
int delete_book(SListEntry **list);
int delete_book_by_id(SListEntry **list, int id);
int modify_book(SListEntry **list);
int query_book(SListEntry **list);
int query_book_by_id(SListEntry **list, int id);
int callback_check_id(SListValue a, SListValue b);

// 借书和还书需要修改book_list和p->num_borrow, p->borrow_bookid
int borrow_book(struct _User *p, SListEntry *book_list);
int return_book(struct _User *p, SListEntry *book_list);
int statistic(SListEntry *book_list);

// 初始化学生和教师可以借的书的数量和天数
void init_teacher(struct _User *p);
void init_student(struct _User *p);
struct _User *ask_user_info(struct _User *p);
int insert_user(SListEntry **list, SListValue *value);
int update_user(SListEntry **list, SListValue *value, char *id_str);
void show_userinfo(SListEntry *user_list, struct _User *p);
void show_books(SListEntry *book_list);

int main(int argc, char const* argv[])
{
    int input;
    // 图书链表，用于存储图书
    SListEntry *book_list = NULL;
    // 用户链表，用于存储用户
    SListEntry *user_list = NULL;
    struct _User *user;

    while (1) {
        welcome();
        puts("");
        puts("输入你的选择:");
        scanf("%d", &input);

        switch (input) {
            case 1:
                user = ask_user_info(user);
                if (user->type != TEACHER) {
                    puts("-------------------");
                    printf("学生不能添加图书\n");
                    puts("-------------------");
                    break;
                }
                // 添加图书
                insert_book(&book_list);
                break;
            case 2:
                user = ask_user_info(user);
                if (user->type != TEACHER) {
                    puts("-------------------");
                    printf("学生不能删除图书\n");
                    puts("-------------------");
                    break;
                }
                // 删除图书
                delete_book(&book_list);
                break;
            case 3:
                user = ask_user_info(user);
                if (user->type != TEACHER) {
                    puts("-------------------");
                    printf("学生不能修改图书\n");
                    puts("-------------------");
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
                user = ask_user_info(user);
                // 借书
                borrow_book(user, book_list);
                // 更新信息
                update_user(&user_list, (SListValue *) user, user->id);
                break;
            case 6:
                user = ask_user_info(user);
                if (user->type == TEACHER)
                    init_teacher(user);
                else
                    init_student(user);
                // 还书
                return_book(user, book_list);
                update_user(&user_list, (SListValue *) user, user->id);
                break;
            case 7:
                user = ask_user_info(user);
                show_userinfo(user_list, user);
                break;
            case 8:
                statistic(book_list);
                break;
            case 9:
                show_books(book_list);
                break;
            case 10:
                exit(EXIT_SUCCESS);
            default:
                puts("-------------------");
                puts("输入错误");
                puts("-------------------");
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

    // 如果图书馆有此书， 只需将num_left++, 如果没有此书， 则需要添加新节点
    p = slist_find_data(*list, callback_check_id, (SListValue *)&book_info->id);
    if (p == NULL) {
        if (slist_append(list, (SListValue *)book_info) != NULL) {
            book_info->num_left++;
            puts("-------------------");
            puts("插入成功");
            puts("-------------------");
            return 1;
        } else {
            puts("-------------------");
            puts("插入失败");
            puts("-------------------");
            return 0;
        }
    } else {
        SListValue *value;

        value = p->data;
        // 剩余数量加一
        ((struct _BookInfo *)value)->num_left++;
    }
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

        if (book_info->num_left == 1) {
            if (slist_remove_entry(entry, p) == 0) {
                puts("-------------------");
                puts("删除数据失败");
                puts("-------------------");
                return -1;
            } else {
                puts("-------------------");
                puts("删除成功");
                puts("-------------------");
                return 1;
            }
        } else {
            value = slist_data(p);
            book_info = (struct _BookInfo *) value;
            // 剩余数量减一
            book_info->num_left--;
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
        puts("-------------------");
        puts("未查询到数据");
        puts("-------------------");
        return -1;
    } else {
        data = slist_data(p);

        puts("----------------------");
        printf("查询结果如下\n");
        // 这里需要强制转换
        printf("id:%d\n", ((struct _BookInfo *)data)->id);
        printf("书名:%s\n", ((struct _BookInfo *)data)->name);
        printf("作者:%s\n", ((struct _BookInfo *)data)->author_name);
        printf("所借数量:%d\n", ((struct _BookInfo *)data)->num_borrowed);
        printf("剩余数量:%d\n", ((struct _BookInfo *)data)->num_left);
        puts("----------------------");
    }
    return 1;
}

int modify_book(SListEntry **entry)
{
    return 0;
}

int borrow_book(struct _User *p, SListEntry *book_list)
{
    int id;
    SListEntry *entry;

    // 检查身份信息
    if (p->type == TEACHER)
        init_teacher(p);
    else
        init_student(p);

    puts("输入你要借的书的id:");
    scanf("%d", &id);

    entry = slist_find_data(book_list, callback_check_id, (SListValue *)&id);
    if (entry == NULL) {
        puts("----------------------");
        puts("此书不存在");
        puts("----------------------");
        return -1;
    }

    puts("输入借书时间:");
    scanf("%d", &p->time_borrow);

    // 检查最大借书数量
    if (p->num_borrow > p->max_num_borrow) {
        puts("超过最大借书数量");
        return -1;
    }

    // 将书id添加至用户信息
    slist_append(&p->borrowed_bookid, (struct _BookInfo *) &id);

    p->num_borrow++;
    // 余数量减1, 借书量加1
    ((struct _BookInfo *) entry->data)->num_left--;
    ((struct _BookInfo *) entry->data)->num_borrowed++;
}

int return_book(struct _User *p, SListEntry *book_list)
{
    int id;
    SListEntry *entry;

    puts("输入你要还的书的id:");
    scanf("%d", &id);

    // 检查身份信息
    if (p->type == TEACHER)
        init_teacher(p);
    else
        init_student(p);

    entry = slist_find_data(book_list, callback_check_id, (SListValue *)&id);
    if (entry == NULL) {
        puts("----------------------");
        puts("此书不存在");
        puts("----------------------");
        return -1;
    }

    puts("输入时间:");
    scanf("%d", &p->time_return);

    // 检查还书时间
    if (p->time_return - p->time_borrow > p->max_time_borrow) {
        puts("超过最大还书时间");
    }

    // 如果用户只剩下一本书则删除对应链表
    slist_remove_entry(&p->borrowed_bookid, entry);
    // 用户借书数量减1
    p->num_borrow--;
    // 此书剩余数量加1, 借书量减1
    ((struct _BookInfo *) entry->data)->num_left++;
    ((struct _BookInfo *) entry->data)->num_borrowed--;
}

void init_teacher(struct _User *p)
{
    p->max_num_borrow = 15;
    p->max_time_borrow = 180;
}

void init_student(struct _User *p)
{
    p->max_time_borrow = 10;
    p->max_time_borrow = 120;
}

struct _User *ask_user_info(struct _User *p)
{
    struct _User *user;

    user = malloc(sizeof(struct _User));
    if (user == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    p = malloc(sizeof(struct _User));
    if (p == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    // 复制内存
    memcpy(user, p, sizeof(struct _User));

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
        // ((struct _User *) user)->num_borrow++;
        puts("----------------------");
        puts("插入用户成功");
        puts("----------------------");
        return 1;
    } else {
        puts("----------------------");
        puts("插入用户失败");
        puts("----------------------");
        return 0;
    }
}


int update_user(SListEntry **list, SListValue *value, char *id_str)
{
    // 这里有三种情况， 第一 此用户还没有借过书 此时将用户插入用户链表， 第二 用户借过了书 需要将此书名加入用户
    // 所借书的数组中
    SListEntry *p;
    int id;

    id = atoi(id_str);

    // 查看用户是否曾今借过书
    p = slist_find_data(*list, callback_check_id, (SListValue *)&id);
    if (p == NULL) {
        struct _User *p;
        p = (struct _User *) value;
        p->num_borrow++;
        insert_user(list, value);
    } else {
        // (struct _User *)value.
        struct _User *p;
        p = (struct _User *) value;
        p->num_borrow++;
        // 添加id到用户信息
        // p->id.append(id);
        // p->time_borrow = gettime_now();
    }
}

void show_userinfo(SListEntry *user_list, struct _User *p)
{
    SListEntry *entry;

    entry = slist_find_data(user_list, callback_check_id, p->id);
    if (entry != NULL) {
        struct _User *t;

        t = entry->data;
        puts("-------------------");
        printf("用户名:%s\n", t->name);
        printf("所借数量:%d\n", t->num_borrow);

        // 所有借的书
        while (p->borrowed_bookid != NULL) {
            printf("%s\n", (char *)(p->borrowed_bookname->data));
        }
        puts("-------------------");
    } else {
        puts("-------------------");
        puts("未查询到信息");
        puts("-------------------");
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

        printf("ID:%d\t", ((struct _BookInfo *) value)->id);
        printf("书名:%s\t", ((struct _BookInfo *) value)->name);
        printf("作者:%s\t", ((struct _BookInfo *) value)->author_name);
        printf("剩余数量:%d\n", ((struct _BookInfo *) value)->num_left);

        p = p->next;
        n++;
    }
    puts("-------------------");

    if (n == 0) {
        puts("-------------------");
        puts("未查询到任何数据");
        puts("-------------------");
    }
}

int statistic(SListEntry *book_list)
{
    int id;
    int n = 0;
    SListEntry *p;
    int num_borrowed, num_left;

    puts("-------------------");
    puts("图书统计如下:");

    p = book_list;
    while (p != NULL) {
        id = ((struct _BookInfo *)p->data)->id;
        num_left = ((struct _BookInfo *)p->data)->num_left;
        num_borrowed = ((struct _BookInfo *)p->data)->num_borrowed;

        printf("书本id:%d 剩余数量:%d 借书数量:%d 借书率:%lf\n", id, num_left, num_borrowed, (double) num_borrowed/num_left);
        // printf("书本id:%d 借书率:%lf\n", id, ((double) num_left) / num_borrowed);
        n++;
        p = p->next;
    }
    puts("-------------------");

    if (n == 0) {
        puts("没有任何数据");
    }
}
