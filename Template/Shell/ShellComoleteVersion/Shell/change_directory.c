//
// Created by coolder on 11/17/20.
//

#include "allheaders.h"
#include "shell.h"

/* This function is used to change directory when "cd" command is
   executed */

void change_directory()
{

    char *home_dir = "/home";

    if ((args[1]==NULL) || (!(strcmp(args[1], "~") && strcmp(args[1], "~/"))))
        chdir(home_dir);
    else if (chdir(args[1]) < 0)
        perror("No such file or directory: ");

}