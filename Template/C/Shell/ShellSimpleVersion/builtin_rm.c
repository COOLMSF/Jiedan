#include "headers.h"

int builtin_rm(char *cmd)
{
	char **args = alloc_args();

	get_args(cmd, args);
    // test arguments
    if (args[1] == NULL) {
        fprintf(stderr, "please specify a file\n");
        return -1;
    }
    
    FILE *fin = NULL;

	if (remove(args[1]) < 0) {
		perror("remove");
		exit(EXIT_FAILURE);
	}

	free_args();
}
