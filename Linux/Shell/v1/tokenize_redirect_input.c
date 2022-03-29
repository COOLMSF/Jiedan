//
// Created by coolder on 11/17/20.
//
#include "allheaders.h"
#include "shell.h"

/* This function is used to parse the input when only input redirection
   ["<"] is present */

void
tokenize_redirect_input(char *cmd_exec)
{
    char *val[128];
    char *new_cmd_exec, *s1;
    new_cmd_exec = strdup(cmd_exec);

    int m = 1;
    val[0] = strtok(new_cmd_exec, "<");
    while ((val[m] = strtok(NULL,"<")) != NULL) m++;

    s1 = strdup(val[1]);
    input_redirection_file = skipwhite(s1);

    tokenize_by_space (val[0]);
    return;
}
