#include <stdlib.h>
#include <string.h>

#include "gymmanagement_gbk.h"

void welcome()
{
    puts("1:) ��ӿͻ�");
    puts("2:) ɾ���ͻ�");
    puts("3:) ��ѯ�ͻ�");
    puts("4:) �޸Ŀͻ�");
    puts("5:) ��ʾ���пͻ���Ϣ");
    puts("6:) �˳�ϵͳ");
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
    puts("����:");
    scanf("%s", person->name);
    puts("�Ƿ��Ա 0:)�� 1:)��:");
    scanf("%d", &person->is_vip);
    puts("�ͻ����:");
    scanf("%lf", &person->left_money);

    return person;
}

Person *show_person(ArrayList *list, void *value, ArrayListCompareFunc compare_func)
{
    for (size_t i = 0; i < list->length; i++)
    {
        printf("ID:%d\n", ((Person *)list->data[i])->id);
        printf("����:%s\n", ((Person *)list->data[i])->name);
        printf("�Ƿ��Ա:%d\n", ((Person *)list->data[i])->is_vip);
        printf("���:%lf\n", ((Person *)list->data[i])->left_money);
    }
}
