/* Main function begins here */

#include "allheaders.h"
#include "shell.h"

int
main()
{
    int status;
    char new_line = 0;

    system ("clear");
    signal(SIGINT, sigintHandler);
    using_history();

    do {

        clear_variables();
        shell_prompt();
        input_buffer = readline (prompt);

        if(strcmp(input_buffer,"\n"))
            add_history (input_buffer);

        if (!(strcmp(input_buffer, "\n") && strcmp(input_buffer,"")))
            continue;

        if (!(strncmp(input_buffer, "exit", 4) && strncmp(input_buffer, "quit", 4))) {

            flag = 1;
            break;
        }

        tokenize_by_pipe();

        if (bckgrnd_flag == 0)
            waitpid(pid,&status,0);
        else
            status = 0;

    } while(!WIFEXITED(status) || !WIFSIGNALED(status));

    if (flag == 1) {

        printf("\nClosing Shell\n");
        exit(0);
    }

    return 0;
}
