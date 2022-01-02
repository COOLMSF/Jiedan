#include "headers.h"

int builtin_makedir(char *cmd)
{
	char *args = getargs(cmd);
	if (mkdir(args, S_IRWXU | S_IRWXG | S_IRWXO) == -1) {
		fprintf(stderr, "Make dir error\n");
		perror("mkdir");
		return -1;
	}
	puts("Make dir succeed");
}
