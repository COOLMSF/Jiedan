#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "slist.h"

#define MAXNAME 254
#define MAXBUF 1024

enum BookType {
    Novel,
};

struct _BookInfo {
    int id;
    int num_total;
    int num_left;
    enum BookType type;
    char name[MAXNAME];
    char author_name[MAXNAME];
};
typedef struct _BookInfo BookInfo;

// 学生教师归为person
struct _Person {
    char id[4];
    char name[MAXNAME];
    int num_borrow;
    time_t time_borrow;
    time_t time_return;
};

void welcome();
int insert_book(SListEntry **list);
int delete_book(SListEntry **list);
int delete_book_by_id(SListEntry **list, int id);
int modify_book(SListEntry **list);
int query_book(SListEntry **list);
int query_book_by_id(SListEntry **list, int id);
int callback_int_equal(SListValue a, SListValue b);
int borrow_book();
int return_book();

int main(int argc, char const* argv[])
{
    int input;
    SListEntry *entry = NULL;

    while (1) {
        welcome();
        puts("");
        puts("输入你的选择:");
        scanf("%d", &input);

        switch (input) {
            case 1:
                insert_book(&entry);
                break;
            case 2:
                delete_book(&entry);
                break;
            case 3:
                modify_book(&entry);
                break;
            case 4:
                query_book(&entry);
                break;
            case 5:
                borrow_book();
                break;
            case 6:
                return_book();
                break;
            case 7:
                exit(EXIT_SUCCESS);
            default:
                puts("输入错误");
                break;
        }
    }

    slist_free(entry);
    return 0;
}

void welcome()
{
    puts("欢迎使用图书管理系统");
    puts("1:) 添加一本图书");
    puts("2:) 删除一本图书");
    puts("3:) 修改一本图书");
    puts("4:) 查询一本图书");
    puts("5:) 借书");
    puts("6:) 还书");
    puts("7:) 退出");
}

int insert_book(SListEntry **list)
{
    BookInfo *book_info;

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
    puts("");

    if (slist_append(list, (SListValue *)book_info) != NULL) {
        puts("插入成功");
        return 1;
    } else {
        puts("插入失败");
        return 0;
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

    p = slist_find_data(*entry, callback_int_equal, (SListValue *)&id);
    if (p == NULL) {
        puts("未查询到数据");
        return -1;
    } else {
        if (slist_remove_entry(entry, p) == 0) {
            puts("删除数据失败");
            return -1;
        } else {
            puts("删除成功");
            return 1;
        }
    }
    puts("");
}

int callback_int_equal(SListValue a, SListValue b)
{
    if (*(int *)a == *(int *)b)
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

    p = slist_find_data(*entry, callback_int_equal, (SListValue *)&id);

    if (p == NULL) {
        puts("未查询到数据");
        return -1;
    } else {
        data = slist_data(p);
        printf("查询结果如下\n");
        // 这里需要强制转换
        printf("id:%d\n", ((struct _BookInfo *)data)->id);
        printf("书名:%s\n", ((struct _BookInfo *)data)->name);
        printf("作者:%s\n", ((struct _BookInfo *)data)->author_name);
        printf("总数量:%d\n", ((struct _BookInfo *)data)->num_total);
        printf("剩余数量:%d\n", ((struct _BookInfo *)data)->num_left);
        puts("");
    }
    return 1;
}

int modify_book(SListEntry **entry)
{
    return 0;
}

int borrow_book()
{
    return 0;
}

int return_book()
{
    return 0;
}
