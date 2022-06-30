#include "headers.h"

int builtin_deldir(char *cmd)
{
	char **args = alloc_args();

	get_args(cmd, args);
	if (rmdir(args[1]) < 0) {
		fprintf(stderr, "Remove dir error\n");
		perror("rmdir");
		return -1;
	}
	puts("Remove dir succeed");

	free_args();
}
