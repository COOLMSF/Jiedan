#include <stdio.h>
#include "MyMalloc.h"

int allocations = 5;

int main() {
  printf("\n---- Running test2 ---\n");
  
  int *p;
  for (int i = 0; i < 0x1000; i++) {
    p = MyMalloc(sizeof(int));
    *p = i;
    printf("%x", *p);
  }
}
