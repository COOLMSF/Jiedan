#include "headers.h"

int builtin_changedir(char *cmd)
{
	char *args = getargs(cmd);

	if (chdir(args) < 0) {
		perror("chdir");
	}
}
