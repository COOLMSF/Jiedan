#include "arraylist.h"
#include <stdio.h>

#define MAX_STR 256
#define MAX_BUF 1024
#define MAX_LINE 256

struct _Book {
    int id;
    double price;
    char name[MAX_STR];
};
typedef struct _Book Book;

void welcome();
Book *new_book();
int show_book(ArrayList *list, size_t size);
int insert_book(ArrayList *list, ArrayListValue value);
// These functions can handle any kind of value
int delete_book(ArrayList *list, void *value, ArrayListCompareFunc compare_func);
Book *query_book(ArrayList *list, void *value, ArrayListCompareFunc compare_func);
int modify_book(ArrayList *list, void *value, ArrayListCompareFunc compare_func);

int read_data_from_disk(FILE *fpr, ArrayList *list);
int write_data_to_disk(FILE *fpw, ArrayList *list);
