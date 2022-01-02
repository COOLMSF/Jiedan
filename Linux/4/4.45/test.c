#include "stdio.h"
#include "unistd.h"

int main(void)
{
	int i = 5;
	
	pid_t pid = vfork();

	if(pid == -1)
	{
		printf("vfork error\n");
		return 0;
	}
	else if(pid == 0)
	{
		printf("in child, pid = %d, father's pid = %d\n", getpid(), getppid());

		i = 10;

		printf("in child, i = %d\n", i);

		_exit(0);
	}
	else
	{		
		printf("in father, pid = %d\n", getpid());

		printf("in father, i = %d\n", i);
	}

	return 0;
}
