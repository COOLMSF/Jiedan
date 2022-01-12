#include "arraylist.h"
#include <stdio.h>

#define MAX_STR 256
#define MAX_BUF 1024
#define MAX_LINE 256

struct _Person {
    int id;
    char name[MAX_BUF];
    // �Ƿ���vip
    int is_vip;
    double left_money;
};
typedef struct _Person Person;

void welcome();
Person *new_person();
/// int show_person(ArrayList *list, size_t size);
int insert_person(ArrayList *list, ArrayListValue value);
int delete_person(ArrayList *list, void *value, ArrayListCompareFunc compare_func);
Person *query_person(ArrayList *list, void *value, ArrayListCompareFunc compare_func);
Person *show_person(ArrayList *list, void *value, ArrayListCompareFunc compare_func);
int modify_person(ArrayList *list, void *value, ArrayListCompareFunc compare_func);
