#include <stdio.h>
#include <stdlib.h>
#include "SqList.h"

int compare_int(SqValue a, SqValue b)
{
    if (*(int *)a == *(int *)b)
        return 1;

    return 0;
}

int main(int argc, char const* argv[])
{
    SqEntry *entry;
    int a = 0x11, b = 0x22, c = 0x33;

    if ((entry = sqlist_init(10)) == SQENTRY_NULL) {
        fprintf(stderr, "sqlist_init err");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 3; i++) {
        int *k = malloc(sizeof(int));
        scanf("%d", k);
        if (sqlist_append(entry, (SqValue)k) == -1) {
            puts("append error");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < 3; i++) {
        printf("%d\n", *(int *)entry->value[i]);
    }

    puts("After delete");
    sqlist_delete_by_index(entry, 0);
    for (int i = 0; i < entry->n_used; i++) {
        printf("%d\n", *(int *)entry->value[i]);
    }
}
