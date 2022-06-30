#include "MyMalloc.h"

int main()
{
  int *p = (int *)malloc(10);
  *p = 10;
  free(p);
}
