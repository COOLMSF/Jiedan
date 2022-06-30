#include "headers.h"


int main(int argc, char const *argv[])
{
    char *input;

    print_banner();

    while ((input = readline(PROMPT)) != NULL) {
        if (strstr(input, "exit") != NULL) {
            puts("Exiting shell");
            exit(EXIT_SUCCESS);
        }
        
        if (strstr(input, "pwd") != NULL) {
            builtin_pwd();
        }

        if (strstr(input, "ls") != NULL) {
            builtin_list(input);
        }

        if (strstr(input, "mkdir") != NULL) {
            builtin_makedir(input);
        }

        if (strstr(input, "rmdir") != NULL) {
            builtin_deldir(input);
        }

        if (strstr(input, "cd") != NULL) {
            builtin_changedir(input);
        }

        if (strstr(input, "cat") != NULL) {
            builtin_cat(input);
        }

        if (strstr(input, "wc") != NULL) {
            builtin_wc(input);
        }

        if (strstr(input, "touch") != NULL) {
            builtin_touch(input);
        }

        if (strstr(input, "cp") != NULL) {
            builtin_cp(input);
        }

		if (strstr(input, "rmall") != NULL) {
			builtin_rm(input);
		}
		if (strstr(input, "echo") != NULL) {
			builtin_echo(input);
		}
    }
}
