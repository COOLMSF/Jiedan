#include "headers.h"

int builtin_list(char *cmd) 
{
    DIR *d;
    char *path;
    struct dirent *dir;

	char **args = alloc_args();

	get_args(cmd, args);

    path = args[1];

    if (strlen(path) < 2) {
	    path = ".";
    }
    d = opendir(path);
    char full_path[1000];
    if (d)
    {
	    int counter = 0;
        while ((dir = readdir(d)) != NULL)
        {
                printf("%15s",dir->d_name);
		counter++;

		if (counter % 3 == 0)
			printf("\n");
        }
        closedir(d);
    }

    puts("");

    free_args();
}
