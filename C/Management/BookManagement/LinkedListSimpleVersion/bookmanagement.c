#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bookmanagement.h"

void welcome()
{
    puts("");
    puts("-------------------");
    puts("欢迎使用图书管理系统");
    puts("1:) 添加一本图书");
    puts("2:) 删除一本图书");
    puts("3:) 修改一本图书");
    puts("4:) 查询一本图书");
    puts("5:) 从文件读取数据");
    puts("6:) 写入数据到文件");
    puts("7:) 显示图书");
    puts("8:) 退出");
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
    puts("输入书本价格:");
    scanf("%lf", &book_info->price);
    puts("");

    p = slist_find_data(*list, callback_check_id, (SListValue *)&book_info->id);
    if (p == NULL) {
        if (slist_append(list, (SListValue *)book_info) != NULL) {
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
        puts("此书已存在");
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
        slist_remove_entry(entry, p);
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
        printf("书名:%lf\n", ((struct _BookInfo *)data)->price);
        puts("----------------------");
    }
    return 1;
}

int modify_book(SListEntry **entry)
{
    return 0;
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
        printf("价格:%lf\t", ((struct _BookInfo *) value)->price);

        p = p->next;
        n++;
        puts("");
    }
    puts("-------------------");

    if (n == 0) {
        puts("-------------------");
        puts("未查询到任何数据");
        puts("-------------------");
    }
}

int read_data_from_disk(FILE *fpr, SListEntry *list)
{
    char line[MAXBUF];

    if (fpr == NULL)
        return -1;

    while (fgets(line, MAXLINE, fpr) != NULL) {
        // malloc new memory for book
        BookInfo *book = malloc(sizeof(struct _BookInfo));
        if (book == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        // get formatted data from buffer
        sscanf(line, "%d, %lf, %s", &book->id, &book->price, book->name);
        // append data to list
        slist_append(&list, book);
    }

    puts("读入成功");

    return 1;
}

int write_data_to_disk(FILE *fpw, SListEntry *list)
{
    char line[MAXLINE] = { 0 };
    SListEntry *p = list;

    if (fpw == NULL)
        return -1;

    // for (int i = 0; i < list->length; i++) {
    //     sprintf(line, "%d, %lf, %s\n", ((Book *)list->data[i])->id, ((Book *)list->data[i])->price,
    //     ((Book *)list->data[i])->name);
    //     fwrite(line, strlen(line), 1, fpw);
    // }
    while (p != NULL) {
        BookInfo *book = (BookInfo *)p->data;

        sprintf(line, "%d, %lf, %s\n", book->id, book->price, book->name);
        fwrite(line, strlen(line), 1, fpw);
        p = p->next;
    }

    puts("写入成功");

    return 1;
}
