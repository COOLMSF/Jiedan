#include "headers.h"

int builtin_cat(char *cmd)
{
	char **args = alloc_args();

	get_args(cmd, args);
    // test arguments
    if (args[1] == NULL) {
        fprintf(stderr, "please specify a file\n");
        return -1;
    }
    
    FILE *fin = NULL;

    fin = fopen(args[1], "r");
    if (!fin) {
        perror("fopen");
        return -1;
    }

    char buf[MAX_BUF] = { 0 };

    while (fgets(buf, MAX_BUF, fin) > 0) {
        fputs(buf, stdout);
    }

	free_args();
}
