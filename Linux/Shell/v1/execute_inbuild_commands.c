#include "allheaders.h"
#include "shell.h"
#include <string.h>

int
execute_inbuild_commands(char *cmd_exec, int input, int isfirst, int islast)
{
    char *new_cmd_exec;

    new_cmd_exec = strdup(cmd_exec);
//     char *p = new_cmd_exec;

    tokenize_by_space (cmd_exec);
    check_for_bckgrnd ();

    if (args[0] != NULL) {
    	// if (!strcmp(args[0], "ex")) {
	// 	// strip string
	// 	while (*new_cmd_exec != 'x') {
	// 		new_cmd_exec++;
	// 	}
	// 	new_cmd_exec++;
	// 	strcpy(args[0], "");
	// 	strcpy(args[0], args[1]);
	// 	printf("CMD : %s\n", new_cmd_exec);
	// 	return (execute_command(input, isfirst, islast, new_cmd_exec));
	// 	// return (execute_command(input, isfirst, islast, new_cmd_exec));
	// 	// return 1;
	// }


        if (!(strcmp(args[0], "exit") && strcmp(args[0], "quit")))
            exit(0);

        /*
         * Add by coolder, echo built in command seems not working
         */
        if (!strcmp(args[0], "echo")) {
            cmd_exec = skip_double_quote(new_cmd_exec);
            tokenize_by_space(cmd_exec);

            char **args_ptr = &args[1];

            while(*args_ptr)
                puts(*args_ptr++);
        }

        if (!strcmp("cd", args[0])) {
            change_directory();
            return 1;
        }
	if (!strcmp("mygrep", args[0])) {
		grep_file(args[1], args[2]);
		return 1;
	}

	if (!strcmp("info", args[0])) {
		return 1;
	}

        if (!strcmp(args[0], "history")) {
            print_history_list();
            return 1;
        }
	if (!strcmp(args[0], "ex")) {
		// char **p = args;
		// while (*p != NULL) {
		// 	printf("%s \n", *p);
		// 	p++;
		// }
		// printf("args[0]:%s, args[1]:%s\n", args[0], args[1]);
		pid_t pid;

		pid = fork();
		// child
		if (pid == 0) {
	 	if (execv(args[1], &args[1]) == -1) {
			puts("ERROR");
			perror("execv");
			return 1;
		}
		}
		return 1;	
	}
    }
    return (execute_command(input, isfirst, islast, new_cmd_exec));
}
