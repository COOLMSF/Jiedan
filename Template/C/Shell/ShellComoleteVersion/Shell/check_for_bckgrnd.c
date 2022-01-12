//
// Created by coolder on 11/17/20.
//

#include "allheaders.h"
#include "shell.h"

/* This is function is used to check whether the process should be run
   foreground or background */

void check_for_bckgrnd()
{

    int i = 0;
    bckgrnd_flag = 0;

    while (args[i] != NULL) {
        if (!strcmp(args[i], "&")) {
            bckgrnd_flag = 1;
            args[i] = NULL;
            break;
        }
        i++;
    }

}