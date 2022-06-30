#include "headers.h"

// args is like, *arr[] = { "ls", "-l", "-a"}
// *arr[] = { "mv", "a", "b" }


// users have responsibility to free args
// return argument number
int get_args(char *cmd, char *args[])
{
    // char *p = cmd;

    // while (*p != ' ') {
    //     if (*p == '\0') {
    //         break;
    //     }
    //     p++;
    // }
    // p++;


    char tmp[MAX_BUF] = { 0 };

    // avoid modification to cmd
    strncpy(tmp, cmd, MAX_BUF);
    char *buf;

    buf = strtok(tmp, " ");
    int c = 0;

    while (buf) {
        if (c > MAX_ARGUMENT) {
            fprintf(stderr, "%s", "too many arguments!\n");
            exit(EXIT_FAILURE);
        }

        args[c] = strdup(buf);
        buf = strtok(NULL, " ");
        c++;
    }

    return c;
}
