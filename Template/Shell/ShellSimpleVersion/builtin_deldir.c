#include "headers.h"

int builtin_deldir(char *cmd)
{
	char *args = getargs(cmd);

	if (rmdir(args) < 0) {
		fprintf(stderr, "Remove dir error\n");
		perror("rmdir");
		return -1;
	}
	puts("Remove dir succeed");
}
