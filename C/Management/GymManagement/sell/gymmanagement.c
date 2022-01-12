#include <stdlib.h>
#include <string.h>

#include "gymmanagement.h"

void welcome()
{
    puts("1:) 添加客户");
    puts("2:) 删除客户");
    puts("3:) 查询客户");
    puts("4:) 修改客户");
    puts("5:) 显示所有客户信息");
    puts("6:) 退出系统");
}

int append_person(ArrayList *list, ArrayListValue value)
{
    return arraylist_append(list, value);
}

int insert_person(ArrayList *list, ArrayListValue value)
{
    return arraylist_append(list, value);
}

int delete_person(ArrayList *list, void *value, ArrayListCompareFunc compare_func)
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

int modify_person(ArrayList *list, void *value, ArrayListCompareFunc compare_func)
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

Person *query_person(ArrayList *list, void *value, ArrayListCompareFunc compare_func)
{
    for (size_t i = 0; i < list->length; i++)
    {
        if (compare_func(list->data[i], &value) == 0)
            return list->data[i];
    }

    return NULL;
}

Person *new_person(void)
{
    Person *person;

    person = malloc(sizeof(struct _Person));
    if (person == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    puts("ID:");
    scanf("%d", &person->id);
    puts("姓名:");
    scanf("%s", person->name);
    puts("是否会员 0:)否 1:)是:");
    scanf("%d", &person->is_vip);
    puts("客户余额:");
    scanf("%lf", &person->left_money);

    return person;
}

Person *show_person(ArrayList *list, void *value, ArrayListCompareFunc compare_func)
{
    for (size_t i = 0; i < list->length; i++)
    {
        printf("ID:%d\n", ((Person *)list->data[i])->id);
        printf("名字:%s\n", ((Person *)list->data[i])->name);
        printf("是否会员:%d\n", ((Person *)list->data[i])->is_vip);
        printf("余额:%lf\n", ((Person *)list->data[i])->left_money);
    }
}