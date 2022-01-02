//
// Created by coolder on 11/17/20.
//
#include "allheaders.h"
#include "shell.h"

/* This function is used to skip the double quote characters (") in the
   input string */

char *
skip_double_quote(char *str)
{
    int i = 0, j = 0;
    char *temp;

    if (NULL == (temp = (char *) malloc(sizeof(str)*sizeof(char)))) {
        perror("Memory Error: ");
        return NULL;
    }

    while(str[i++]) {
        if (str[i-1] != '"')
            temp[j++] = str[i-1];
    }
    temp[j] = '\0';
    return temp;
}
