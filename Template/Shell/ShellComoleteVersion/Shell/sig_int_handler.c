//
// Created by coolder on 11/17/20.
//
#include "allheaders.h"

/* This function handles the interrupt signals */

void
sigintHandler(int sig_num)
{
    signal(SIGINT, sigintHandler);
    fflush(stdout);
}