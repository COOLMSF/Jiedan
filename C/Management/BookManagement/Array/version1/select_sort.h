#include <stdio.h>

typedef int (*CompareFunc)(void *a, void *b);

void swap32(void *a, void *b);
void swap64(void *a, void *b);
#if __x86_32__
#define 
swap(a, b) swap32(a, b);
#endif

#if __x86_64__
#define 
swap(a, b) swap64(a, b);
#endif

int compare_func_int(void *a, void *b);
int get_array_max_index(void *arr, size_t nmember, size_t size, CompareFunc compare_func);
int select_sort(void *arr, size_t nmenber, size_t size, CompareFunc compare_func);

