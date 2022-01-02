#include "stdio.h"
#include "stdlib.h"

void f1(void)
{
	printf("in f1()\n");
}

void f2(void)
{
	printf("in f2()\n");
}

void f3(void)
{
	printf("in f3()\n");
}

int main(void)
{
	atexit(f1);
	atexit(f2);
	atexit(f3);

	return 0;
}
