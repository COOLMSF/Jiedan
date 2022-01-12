//
// Created by coolder on 11/17/20.
//

#include "allheaders.h"
#include "shell.h"

/* This function is used to create the Shell Prompt */

void
shell_prompt()
{
    if (getcwd(cwd, sizeof(cwd)) != NULL) {

        strcpy(prompt, "cjliaoOSshell");
        // strcat(prompt, cwd);
        strcat(prompt, ">");
    }
    else {

        perror("Error in getting curent working directory: ");
    }
}
