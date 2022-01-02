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

void __attribute__((naked)) _start()
{
	asm volatile("movq %%rsp, %%rdi\n\t"
				 "callq start_main"
				 :::);
}
