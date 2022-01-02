#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "sys/mman.h"

int main(int argc, char *argv[]);

void start_main(unsigned long *rsp)
{
	int argc = (int)(*rsp);

	rsp++;
	
	char **argv = (char **)rsp;

	_exit(main(argc, argv));
}

void _start(void)
{
	unsigned long *rsp;
	
	asm volatile("movq %%rsp, %0"
				:"=m"(rsp)::);

	start_main(rsp);
}
