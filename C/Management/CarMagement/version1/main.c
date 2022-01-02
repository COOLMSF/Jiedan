#include <stdio.h>
#include <stdlib.h>

#include "carmanagement.h"

int compare_func_check_id(void *a, void *b)
{
    return ((Car *)a)->id - ((Car *)a)->id;
}

int main(int agrc, char *argv[])
{
    int id;
    int input;
    Car *tmp;
    FILE *fpr, *fpw;
    char filename[MAX_STR];

    ArrayList *list;
    Car *book;

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
                book = new_car();
                if (insert_car(list, book) > 0)
                    puts("插入成功");
                break;
            case 2:
                puts("输入要删除的车辆信息:");
                scanf("%d", &id);
                delete_car(list, (void *) &id, compare_func_check_id);
                puts("删除成功过");
                break;
            case 3:
                puts("输入要读入的文件名:");
                scanf("%s", filename);

                fpr = fopen(filename, "r");
                if (fpr == NULL) {
                    perror("fopen readfile");
                    exit(EXIT_FAILURE);
                }
                if (read_data_from_disk(fpr, list) < 0) {
                    fprintf(stderr, "Failed to read file");
                    break;
                }
                break;
            case 4:
                puts("请输入要写入的文件名");
                scanf("%s", filename);

                fpw = fopen(filename, "w");
                if (fpr == NULL) {
                    perror("fopen writefile");
                    exit(EXIT_FAILURE);
                }
                if (write_data_to_disk(fpw, list) < 0) {
                    fprintf(stderr, "Failed to write file");
                    break;
                }
                break;
            case 5:
                puts("请输入要查询的车辆信息:");
                scanf("%d", &id);
                tmp = query_car(list, &id, compare_func_check_id);
                printf("名字：%s 价格：%lf\n", tmp->owner_name, tmp->pos);
                break;
            case 6:
                show_car(list, sizeof(double) * list->length);
                break;
            case 7: 
                exit(EXIT_FAILURE);

            default:
                puts("输入错误");
                break;
        }
    }
}

