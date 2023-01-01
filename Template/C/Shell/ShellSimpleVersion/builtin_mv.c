#include "headers.h"
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "stdio.h"
#include "sys/stat.h"
#include "dirent.h"
#include "unistd.h"
#include "string.h"
#include "stdlib.h"

int builtin_mv(char *cmd)
{
    char **args = alloc_args();
    int arg_num = get_args(cmd, args);
	struct stat file_stat;

    if (arg_num != 3) {
        fprintf(stderr, "usage: %s src_file dst_file\n", args[0]);
        return -1;
    }

	char buf[1024] = { 0 };

	sprintf(buf, "mv %s %s", args[1], args[2]);

	system(buf);

	return 1;
}

