#include "headers.h"

int builtin_touch(char *cmd)
{
    char **args = alloc_args();
    int arg_num = get_args(cmd, args);

    if (arg_num < 2) {
        fprintf(stderr, "usage: %s file_name\n", args[0]);
        return -1;
    }

    int fd2 = open(args[1], O_RDWR | O_CREAT, 0700);

    if (fd2 < 0) {
        perror("open");
        return -1;
    }
}
