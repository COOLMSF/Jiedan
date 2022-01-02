#include "stdio.h"
#include "unistd.h"
#include "sys/mman.h"

void _start(void)
{
	void *addr = mmap(NULL, 4096, PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if(addr == MAP_FAILED)
	{
		printf("mmap error\n");
		_exit(EXIT_SUCCESS);
	}

	int *p = (int *)addr;
	*p = 1000;

	printf("*p = %d\n", *p);

	if(munmap(addr, 4096) == -1)
		printf("munmap error\n");
	
	_exit(EXIT_SUCCESS);
}
