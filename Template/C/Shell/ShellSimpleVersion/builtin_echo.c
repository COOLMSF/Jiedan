#include "headers.h"

int builtin_echo(char *cmd)
{
	char **args = alloc_args();

	get_args(cmd, args);
    printf("%s\n", args[1]);

	free_args();
}
