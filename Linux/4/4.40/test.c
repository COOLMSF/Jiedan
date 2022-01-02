#include "stdio.h"
#include "stddef.h"
#include "unistd.h"

int main(void)
{
	char *argv[] = {"../4.8/test", "Hello", "World", NULL};

	execv(argv[0], argv);

	return 0;
}
