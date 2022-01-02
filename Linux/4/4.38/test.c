#include "stdio.h"
#include "stddef.h"
#include "unistd.h"

int main(void)
{
	char **envp = environ;
	
	while(*envp != NULL)
	{
		printf("%s\n", *envp);
		envp++;
	}

	return 0;
}
