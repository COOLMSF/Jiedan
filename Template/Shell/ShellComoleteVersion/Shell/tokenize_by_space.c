//
// Created by coolder on 11/17/20.
//

#include "allheaders.h"
#include "shell.h"

/* This function tokenizes the input string based on white-space [" "] */

void
tokenize_by_space(char *str)
{
    int m = 1;

    args[0] = strtok(str, " ");
    while ((args[m] = strtok(NULL," ")) != NULL) m++;
    args[m] = NULL;
}
