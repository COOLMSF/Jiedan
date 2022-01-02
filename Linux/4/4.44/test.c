#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "sys/wait.h"
#include "string.h"
#include "errno.h"

int main(void)
{
	pid_t pid = fork();

	if(pid == -1)
	{
		printf("fork error\n");
		return 0;
	}
	else if(pid == 0)
	{
		printf("in child, pid = %d, father's pid = %d\n", getpid(), getppid());

		exit(5);
	}
	else
	{
		int wstatus;
		pid_t child = wait(&wstatus);

		if(child == -1)
		{
			printf("wait error: %s\n", strerror(errno));
			return 0;
		}
		
		printf("in father, child's pid = %d\n", pid);

		printf("in father, return val of wait = %d\n", child);

		if(WIFEXITED(wstatus))
			printf("in father, child's exit code = %d\n", WEXITSTATUS(wstatus));
	}

	return 0;
}
