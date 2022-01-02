#include <stdio.h>
#include <stdlib.h>

struct _Book {
    int id;
    double price;
    char name[100];
};

int main(int argc, char const *argv[])
{
    FILE *fpr;
    struct _Book book;
    char line[100];

    fpr = fopen(argv[1], "r");
    if (fpr == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    while (fgets(line, 100, fpr) != NULL)
        sscanf(line, "%d, %lf, %s", &book.id, &book.price, book.name);

    printf("ID:%d\tPrice:%lf\tName:%s\n", book.id, book.price, book.name);
}
