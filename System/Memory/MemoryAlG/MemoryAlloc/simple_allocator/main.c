#include "allocator.h"

#include <stdio.h>

int main(int argc, char** argv)
{
    const int size = 30 + (3 * sizeof(alloc_header_t));
    char my_heap[size];
    puts("正在初始化...");
    heap_init((void*)my_heap, size);

    puts("正在分配内存...");
    int* a = my_malloc(10);
    int* b = my_malloc(10);
    int* c = my_malloc(10);

    puts("正在存储数据...")
  for (int i = 0; i < 10; i++) {
    a[i] = i;
  }

    puts("输出存储数据...")
  for (int i = 0; i < 10; i++) {
    printf("%d\n", a[i]);
  }

    my_free(a);
    my_free(c);
    my_free(b);

    return 0;
}
