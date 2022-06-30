#include "headers.h"

int builtin_changedir(char *cmd)
{
	char **args = alloc_args();

	get_args(cmd, args);


	if (chdir(args[1]) < 0) {
		perror("chdir");
	}
}
