#include "headers.h"

char *getargs(char *cmd)
{
    char *p = cmd;

    while (*p != ' ') {
        if (*p == '\0') {
            break;
        }
        p++;
    }
    p++;

    return p;
}

