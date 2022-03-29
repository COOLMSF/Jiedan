#include "allheaders.h"
#include "shell.h"

/* This function is used to create pipe and execute the non-inbuild
   commands using execvp */

int
execute_command(int input, int first, int last, char *cmd_exec)
{
    int mypipefd[2], ret, input_fd, output_fd;

    if (-1 == (ret = pipe(mypipefd))) {
        perror("pipe error: ");
        return 1;
    }

    pid = fork();

    if (pid == 0) {
        // coolder: input should be input_fd;
        if (first == 1 && last == 0 && input == 0) {
            dup2 (mypipefd[1], 1);
        }
        else if (first == 0 && last == 0 && input != 0) {
            dup2 (input, 0);
            dup2 (mypipefd[1], 1);
        }
        else {
            dup2 (input, 0);
        }

        if (strchr(cmd_exec, '<') && strchr(cmd_exec, '>')) {
            input_redirection = 1;
            output_redirection = 1;
            tokenize_redirect_input_output (cmd_exec);
        }
        else if (strchr(cmd_exec, '<')) {
            input_redirection = 1;
            tokenize_redirect_input (cmd_exec);
        }
        else if (strchr(cmd_exec, '>')) {
            output_redirection = 1;
            tokenize_redirect_output (cmd_exec);
        }

        if (output_redirection) {
            if ((output_fd = creat(output_redirection_file, 0644)) < 0) {
                fprintf(stderr, "Failed to open %s for writing\n", output_redirection_file);
                return (EXIT_FAILURE);
            }
            dup2 (output_fd, 1);
            close (output_fd);
            output_redirection = 0;
        }

        if (input_redirection) {

            if ((input_fd = open(input_redirection_file, O_RDONLY, 0)) < 0) {

                fprintf(stderr, "Failed to open %s for reading\n", input_redirection_file);
                return (EXIT_FAILURE);
            }
            dup2 (input_fd, 0);
            close (input_fd);
            input_redirection = 0;
        }

        check_for_bckgrnd ();

        if (!strcmp (args[0], "echo")) {
            //echo_calling(cmd_exec);
        }
        else if (execvp(args[0], args) < 0) {
		printf("execvp:%s\n", args[0]);
            fprintf(stderr, "%s: Command not found\n",args[0]);
        }
        exit(0);
    }

    else {

        if (bckgrnd_flag == 0)
            waitpid(pid,0,0);
    }

    if (last == 1)
        close(mypipefd[0]);

    if (input != 0)
        close(input);

    close(mypipefd[1]);
    return (mypipefd[0]);
}
