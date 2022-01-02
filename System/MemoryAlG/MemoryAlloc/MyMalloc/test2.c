#include <stdio.h>
#include "MyMalloc.h"

int allocations = 5;

int main() {
  printf("\n---- Running test2 ---\n");
  
  // test performs a few large allocations, beyond 2MB.
  // this means more chunks must be requested from the OS.
  // int i;
  // for ( i = 0; i < allocations; i++ ) {
  //   char * p1 = (char *) MyMalloc(1500000);
  //   *p1 = 100;
  //   print_list();
  // }
  int *p;
  for (int i = 0; i < 0x1000; i++) {
    p = MyMalloc(sizeof(int));
    *p = i;
    printf("%x", *p);
  }
}
