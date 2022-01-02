#include <stdlib.h>
#include <string.h>

#include "select_sort.h"
#include "arraylist.h"
#include "bookmanagement.h"

void welcome()
{
    puts("1:) 添加图书");
    puts("2:) 删除图书");
    puts("3:) 从硬盘读取数据");
    puts("4:) 写入数据到硬盘");
    puts("5:) 查询图书");
    puts("6:) 显示所有图书信息");
    puts("7:) 退出系统");
}

int append_book(ArrayList *list, ArrayListValue value)
{
    return arraylist_append(list, value);
}

int insert_book(ArrayList *list, ArrayListValue value)
{
    return arraylist_append(list, value);
}

int delete_book(ArrayList *list, void *value, ArrayListCompareFunc compare_func)
{
    int ret = -1;

    for (size_t i = 0; i < list->length; i++)
        if (compare_func(list->data[i], &value) == 0)
        {
            arraylist_remove(list, i);
            ret = 1;
        }
    return ret;
}

int modify_book(ArrayList *list, void *value, ArrayListCompareFunc compare_func)
{
    int ret = -1;

    for (size_t i = 0; i < list->length; i++)
        if (compare_func(list->data[i], &value) == 0)
        {
            arraylist_remove(list, i);
            ret = 1;
        }

    return ret;
}

Book *query_book(ArrayList *list, void *value, ArrayListCompareFunc compare_func)
{
    for (size_t i = 0; i < list->length; i++)
    {
        if (compare_func(list->data[i], &value) == 0)
            return list->data[i];
    }

    return NULL;
}

Book *new_book(void)
{
    Book *book;

    book = malloc(sizeof(struct _Book));
    if (book == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    puts("ID:");
    scanf("%d", &book->id);
    puts("书名:");
    scanf("%s", book->name);
    puts("价格:");
    scanf("%lf", &book->price);

    return book;
}

int compare_func_check_price(void *a, void *b)
{
    Book *book1, *book2;

    book1 = (Book *)a;
    book2 = (Book *)b;

    return book1->price - book2->price;
}

int sort_book(ArrayList *list, size_t nmember, size_t size, CompareFunc compare_func)
{
    // return arraylist_sort((void *)list->data, nmember, size, compare_func);
    arraylist_sort((void *)list->data, compare_func);

    return 1;
}

int show_book(ArrayList *list, size_t size)
{
    /**
     * TODO 0. sort
     * TODO 1. max price
     * TODO 2. average price
    */

    double max_price = 0.0;
    double total_price = 0.0;
    double avg_price = 0.0;

    // if book is empty do nothing
    if (list->length == 0) {
        puts("暂无图书显示");
        return -1;
    }

    // sort_book((void *)list->data, list->length, size, compare_func_check_price);
    arraylist_sort(list, compare_func_check_price);

    puts("价格最高图书:");
    // the last element is the max value, there are one or more max item
    max_price = ((Book *)(list->data[list->length - 1]))->price;
    for (size_t i = list->length - 1; i > 0; i--)
    {
        Book *book = ((Book *)(list->data[i]));
        if (book->price == max_price)
            printf("Max price book: %s\t %f\n", book->name, book->price);
    }
    puts("");

    // calculate the total score
    for (size_t i = 0; i < list->length - 1; i++)
        total_price += ((Book *)(list->data[i]))->price;
    avg_price = total_price / list->length;
    printf("图书平均价格:%lf\n", avg_price);
    puts("");

    puts("所有图书:");
    for (size_t i = 0; i < list->length; i++)
        printf("Bookname:%s\tprice:%lf\n", ((Book *)list->data[i])->name, ((Book *)list->data[i])->price);

    return 1;
}

/**
 * ! The file format should be like this,
 * ! id, price, name, such as,
 * ! 1, thebook1, 99.9
 * ! 2, thebook2, 66.6
*/

int read_data_from_disk(FILE *fpr, ArrayList *list)
{
    char line[MAX_LINE] = {0};

    if (fpr == NULL)
        return -1;

    while (fgets(line, MAX_LINE, fpr) != NULL) {
        // malloc new memory for book
        Book *book = malloc(sizeof(struct _Book));
        if (book == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        // get formatted data from buffer
        sscanf(line, "%d, %lf, %s", &book->id, &book->price, book->name);
        // append data to list
        arraylist_append(list, book);
    }
    
    puts("读入成功");

    return 1;
}

int write_data_to_disk(FILE *fpw, ArrayList *list)
{
    char line[MAX_LINE] = { 0 };
    Book *book = (Book *)list->data;

    if (fpw == NULL)
        return -1;
    
    for (int i = 0; i < list->length; i++) {
        sprintf(line, "%d, %lf, %s\n", ((Book *)list->data[i])->id, ((Book *)list->data[i])->price, 
        ((Book *)list->data[i])->name);
        fwrite(line, strlen(line), 1, fpw);
    }

    puts("写入成功");

    return 1;
}
