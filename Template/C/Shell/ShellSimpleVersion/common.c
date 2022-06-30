#include "headers.h"

char **alloc_args()
{
	char **args = (char **)malloc(sizeof(int *) * MAX_ARGUMENT);

    for (int i = 0; i < MAX_ARGUMENT; i++) {
        args[i] = (char *)malloc(sizeof(char) * MAX_BUF);
	    memset(args[i], 0, MAX_BUF);
    }

    return args;
}

int free_args(char **args)
{
    // for (int i = 0; i < MAX_ARGUMENT; i++) {
    //     free(args[i]);
    // }
}