#include "select_sort.h"
#include <stdint.h>

int select_sort(void *arr, size_t nmember, size_t size, CompareFunc compare_func)
{
    int index;
    int typesize = size / nmember;

    for (size_t i = 0; i < nmember; i++) {
        index = get_array_max_index(arr + i * typesize, nmember - i, 
            (nmember - i) * typesize, compare_func);
        swap64(arr + i * typesize, arr + (index + i) * typesize);
    }
}

void swap32(void *a, void *b)
{
    uint32_t tmp;

    tmp = *(uint32_t *)a;
    *(uint32_t *)a = *(uint32_t *)b;
    *(uint32_t *)b = tmp;
}

void swap64(void *a, void *b)
{
    uint64_t tmp;

    tmp = *(uint64_t *)a;
    *(uint64_t *)a = *(uint64_t *)b;
    *(uint64_t *)b = tmp;
}

/*
 * This function will return the address of the max value of the array
 */
int get_array_max_index(void *arr, size_t nmember, size_t size, CompareFunc compare_func)
{
    int max_index = 0;
    int typesize = size / nmember;

    for (size_t i = 0; i < nmember; i++) {
        if (compare_func(arr + i * typesize, arr + max_index * typesize) > 0) {
            // update the max index
            max_index = i;
        }
    }

    return max_index;
}

int compare_func_int(void *a, void *b)
{
    return *(double *)a - *(double *)b;
}

