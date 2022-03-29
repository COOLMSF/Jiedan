#include <stdio.h>
#include <stdlib.h>

#include "gymmanagement_gbk.h"

int compare_func_check_id(void *a, void *b)
{
    return ((Person *)a)->id - ((Person *)a)->id;
}

int main(int agrc, char *argv[])
{
    int id = 0;
    int input = 0;
    Person *tmp = NULL;
    FILE *fpr = NULL, *fpw = NULL;

    ArrayList *list = NULL;
    Person *person = NULL;

    list = arraylist_new(16);
    if (list == NULL) {
        perror("arraylist_new");
        exit(EXIT_FAILURE);
    }

    while (1) {
        welcome();
        scanf("%d", &input);

        switch (input) {
            case 1:
                person = new_person();
                if (insert_person(list, person) > 0)
                    puts("插入成功");
                break;
            case 2:
                puts("输入要删除的id:");
                scanf("%d", &id);
                delete_person(list, (void *) &id, compare_func_check_id);
            case 3:
                puts("请输入要查询的id:");
                scanf("%d", &id);
                tmp = query_person(list, &id, compare_func_check_id);
                printf("名字：%s 价格：%lf\n", tmp->name, tmp->left_money);
                break;
            case 4:
                puts("请输入要修改的id:");
                scanf("%d", &id);
                tmp = modify_person(list, &id, compare_func_check_id);
                puts("修改成功");
                break;
            case 5:
                // show_person(list, sizeof(double) * list->length);
                show_person(list, &id, compare_func_check_id);
                break;
            case 6: 
                exit(EXIT_FAILURE);

            default:
                puts("输入错误");
                break;
        }
    }
}

