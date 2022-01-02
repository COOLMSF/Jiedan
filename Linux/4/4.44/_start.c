#include "stdlib.h"

char **environ;

int main(int argc, char *argv[], char *envp[]);

void start_main(unsigned long *rsp)
{
	int argc = (int)(*rsp);

	rsp++;
	
	char **argv = (char **)rsp;

	environ = (char **)(rsp + argc + 1);

	exit(main(argc, argv, environ));
}

void __attribute__((naked)) _start()
{
	asm volatile("movq %%rsp, %%rdi\n\t"
				 "callq start_main"
				 :::);
}
