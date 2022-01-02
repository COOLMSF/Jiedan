#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "slist.h"

#define MAXNAME 254
#define MAXBUF 1024

int main(int argc, char const* argv[])
{
    int input;
    int ch;
    SListEntry *list1 = NULL;
    SListEntry *list2 = NULL;

    puts("请输入第一个链表，以#结束");
    while ((ch = getchar()) != '#') {
        int *num;
        
        num = malloc(sizeof(int));
        if (num == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        *num = ch;
        slist_append(&list1, (SListValue *)num);
    }

    puts("请输入第二个链表，以#结束");
    while ((ch = getchar()) != '#') {
        int *num;

        num = malloc(sizeof(int));
        if (num == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        *num = ch;
        slist_append(&list2, (SListValue *)num);
    }

    SListEntry *tmp1 = list1;
    SListEntry *tmp2 = list2;

    puts("第一个链表:");
    while (tmp1 != NULL) {
        printf("%d ", *(int *)tmp1->data);
        tmp1 = tmp1->next;
    }

    slist_free(list1);
    return 0;
}

