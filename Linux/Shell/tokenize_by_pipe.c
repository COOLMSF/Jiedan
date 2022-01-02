//
// Created by coolder on 11/17/20.
//

#include "allheaders.h"
#include "shell.h"

/* This function tokenizes the input string based on pipe ["|"] */

void
tokenize_by_pipe()
{
    int i, n = 1, input = 0, first = 1;

    cmd_exec[0] = strtok(input_buffer, "|");
    while ((cmd_exec[n] = strtok(NULL, "|")) != NULL) n++;

    cmd_exec[n] = NULL;

    for (i = 0; i < n-1; i++) {

        input = execute_inbuild_commands(cmd_exec[i], input, first, 0);
        first = 0;
    }

    input = execute_inbuild_commands(cmd_exec[i], input, first, 1);

}
