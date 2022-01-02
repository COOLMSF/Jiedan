#include <stdio.h>
#include <stdlib.h>

#include "bookmanagement.h"

int compare_func_check_id(void *a, void *b)
{
    return ((Book *)a)->id - ((Book *)a)->id;
}

int main(int agrc, char *argv[])
{
    int id;
    int input;
    Book *tmp;
    FILE *fpr, *fpw;
    char filename[MAX_STR];

    ArrayList *list;
    Book *book;

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
                book = new_book();
                if (insert_book(list, book) > 0)
                    puts("插入成功");
                break;
            case 2:
                puts("输入要删除的id:");
                scanf("%d", &id);
                delete_book(list, (void *) &id, compare_func_check_id);
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
                puts("请输入要查询的id:");
                scanf("%d", &id);
                tmp = query_book(list, &id, compare_func_check_id);
                printf("名字：%s 价格：%lf\n", tmp->name, tmp->price);
                break;
            case 6:
                show_book(list, sizeof(double) * list->length);
                break;
            case 7: 
                exit(EXIT_FAILURE);

            default:
                puts("输入错误");
                break;
        }
    }
}

