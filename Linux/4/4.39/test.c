#include "stdio.h"
#include "stddef.h"
#include "unistd.h"

int main(void)
{
	char *argv[] = {"../4.8/test", "Hello", "World", NULL};

	char *envp[] = {"a=b", "c=d", NULL};

	execve(argv[0], argv, envp);

	return 0;
}
