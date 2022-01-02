#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "sys/mman.h"

void _start(void)
{
	void *p = malloc(8);
	free(p);
	
	_exit(EXIT_SUCCESS);
}
