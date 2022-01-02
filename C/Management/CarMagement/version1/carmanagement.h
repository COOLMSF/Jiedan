#include "arraylist.h"
#include <stdio.h>

#define MAX_STR 256
#define MAX_BUF 1024
#define MAX_LINE 256

struct _Car {
    int id;
    double pos;
    char owner_name[MAX_STR];
};
typedef struct _Car Car;

void welcome();
Car *new_car();
typedef int (*CompareFunc)(void *a, void *b);
int compare_func_int(void *a, void *b);
int show_car(ArrayList *list, size_t size);
int insert_car(ArrayList *list, ArrayListValue value);
// These functions can handle any kind of value
int delete_car(ArrayList *list, void *value, ArrayListCompareFunc compare_func);
Car *query_car(ArrayList *list, void *value, ArrayListCompareFunc compare_func);
int modify_car(ArrayList *list, void *value, ArrayListCompareFunc compare_func);

int read_data_from_disk(FILE *fpr, ArrayList *list);
int write_data_to_disk(FILE *fpw, ArrayList *list);
