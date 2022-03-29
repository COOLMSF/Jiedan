//
// Created by coolder on 11/17/20.
//

#include "allheaders.h"

/* This function prints the comand history when "history" command is given */

void
print_history_list()
{
    register HIST_ENTRY **the_list;
    register int i;

    the_list = history_list ();
    if (the_list)
        for (i = 0; the_list[i]; i++)
            printf ("%d: %s\n", i + history_base, the_list[i]->line);
}
