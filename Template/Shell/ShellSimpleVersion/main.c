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

        if (strstr(input, "list") != NULL) {
            builtin_list(input);
        }

        if (strstr(input, "makedir") != NULL) {
            builtin_makedir(input);
        }

        if (strstr(input, "deldir") != NULL) {
            builtin_deldir(input);
        }

        if (strstr(input, "changedir") != NULL) {
            builtin_changedir(input);
        }
    }
}
