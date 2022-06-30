#include "headers.h"

int builtin_makedir(char *cmd)
{
	char **args = alloc_args();

	get_args(cmd, args);

	if (mkdir(args[1], S_IRWXU | S_IRWXG | S_IRWXO) == -1) {
		fprintf(stderr, "Make dir error\n");
		perror("mkdir");
		return -1;
	}
	puts("Make dir succeed");
	free(args);
}
