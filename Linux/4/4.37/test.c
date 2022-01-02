#include "stdio.h"
#include "stddef.h"

int main(int argc, char *argv[], char *envp[])
{
	printf("argc = %d\n", argc);

	for(int i = 0; i < argc; i++)
		printf("argv[%d] = %s\n", i, argv[i]);

	while(*envp != NULL)
	{
		printf("%s\n", *envp);
		envp++;
	}

	return 0;
}
