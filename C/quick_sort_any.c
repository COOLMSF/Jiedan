#include <stdio.h>
#include <stdint.h>

#define MAX_ELEMENT 5

typedef int (*CompareFunc)(void *a, void *b);

void swap(void *a, void *b);
int compare_func_int(void *a, void *b);
int get_array_max_index(void *arr, size_t nmember, size_t size, CompareFunc compare_func);
int quick_sort(void *arr, size_t nmenber, size_t size, CompareFunc compare_func);


int quick_sort(void *arr, size_t nmember, size_t size, CompareFunc compare_func)
{
    int index;
    int typesize = size / nmember;

    for (size_t i = 0; i < nmember; i++) {
        index = get_array_max_index(arr + i * typesize, nmember - i, 
            (nmember - i) * typesize, compare_func);
        swap(arr + i * typesize, arr + (index + i) * typesize);
    }
}

#if __x86_32__
void swap(void *a, void *b)
{
    int tmp;

    tmp = *(u_int32_t *)a;
    *(double *)a = *(double *)b;
    *(double *)b = tmp;
}
#endif

#if __x86_64__
void swap(void *a, void *b)
{
    int tmp;

    tmp = *(u_int64_t *)a;
    *(u_int64_t *)a = *(u_int64_t *)b;
    *(u_int64_t *)b = tmp;
}
#endif

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

int main(int argc, char const* argv[])
{
    double arr[MAX_ELEMENT];

    for (int i = 0; i < MAX_ELEMENT; i++)
        scanf("%lf", arr + i);

    quick_sort(arr, MAX_ELEMENT, sizeof(arr), compare_func_int);

    for (int i = 0; i < MAX_ELEMENT; i++)
       printf("%lf ", arr[i]);
}

