#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "bookmanagement.h"

int main(int argc, char const* argv[])
{
    int input;
    // 图书链表，用于存储图书
    char filename[MAXNAME];
    SListEntry *book_list = NULL;
    FILE *fpr, *fpw;

    while (1) {
        welcome();
        puts("");
        puts("输入你的选择:");
        scanf("%d", &input);

        switch (input) {
            case 1:
                insert_book(&book_list);
                break;
            case 2:
                delete_book(&book_list);
                break;
            case 3:
                modify_book(&book_list);
                break;
            case 4:
                query_book(&book_list);
                break;
            case 5:
                puts("请输入要读入的文件名:");
                scanf("%s", filename);

                fpr = fopen(filename, "r");
                if (fpr == NULL) {
                    perror("fopen");
                    exit(EXIT_FAILURE);
                }
                read_data_from_disk(fpr, book_list);
                fclose(fpr);
                break;
            case 6:
                puts("请输入要写入的文件名:");
                scanf("%s", filename);

                fpw = fopen(filename, "w");
                write_data_to_disk(fpw, book_list);
                fclose(fpw);
                break;
            case 7:
                show_books(book_list);
                break;
            case 8:
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
