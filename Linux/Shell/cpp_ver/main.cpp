/* Main function begins here */

#include <fcntl.h>
#include<dirent.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <signal.h>


int fd;
char *args[512];
char prompt[512];
char *history_file;
char *input_buffer;
char *cmd_exec[512];
int flag, len;
char cwd[1024];
int bckgrnd_flag;
pid_t pid;
int no_of_lines;
int environmment_flag;
int status;

char *skipwhite(char* str);
char *strremove(char *str, const char *sub);
void change_directory();
int execute_inbuild_commands(char *cmd_exec, int input, int isfirst, int islast);
void tokenize_by_space(char *str);
void tokenize_by_pipe();
void shell_prompt();
int execute_command(int input, int first, int last, char *cmd_exec);
void clear_variables();
int builtin_kill(int sig);
void check_for_bckgrnd();

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

char *strremove(char *str, const char *sub) {
    size_t len = strlen(sub);
    if (len > 0) {
        char *p = str;
        while ((p = strstr(p, sub)) != NULL) {
            memmove(p, p + len, strlen(p + len) + 1);
        }
    }
    return str;
}
char *skipwhite(char* str)
{
    int i = 0, j = 0;
    char *temp;
    if (NULL == (temp = (char *) malloc(sizeof(str)*sizeof(char)))) {
        perror("Memory Error: ");
        return NULL;
    }

    while(str[i++]) {

        if (str[i-1] != ' ')
            temp[j++] = str[i-1];
    }
    temp[j] = '\0';
    return temp;
}

void change_directory()
{

    char *home_dir = "/home";

    if ((args[1]==NULL) || (!(strcmp(args[1], "~") && strcmp(args[1], "~/"))))
        chdir(home_dir);
    else if (chdir(args[1]) < 0)
        perror("No such file or directory: ");

}

int execute_inbuild_commands(char *cmd_exec, int input, int isfirst, int islast)
{
    char *new_cmd_exec;

    new_cmd_exec = strdup(cmd_exec);

    tokenize_by_space (cmd_exec);
check_for_bckgrnd ();	

    if (args[0] != NULL) {
        if (!(strcmp(args[0], "exit") && strcmp(args[0], "quit")))
            exit(0);
        if (!strcmp("cd", args[0])) {
            change_directory();
            return 1;
        }
	if (!strcmp("kill", args[0])) {
		builtin_kill(atoi(args[1]));
		return 1;
	}
    }
    return (execute_command(input, isfirst, islast, new_cmd_exec));
}



int builtin_kill(int pid)
{
	kill(pid, 9);
}

void tokenize_by_space(char *str)
{
    int m = 1;

    args[0] = strtok(str, " ");
    while ((args[m] = strtok(NULL," ")) != NULL) m++;
    args[m] = NULL;
}


void tokenize_by_pipe()
{
    int i, n = 1, input = 0, first = 1;

    cmd_exec[0] = strtok(input_buffer, "|");
    while ((cmd_exec[n] = strtok(NULL, "|")) != NULL) n++;

    cmd_exec[n] = NULL;

    for (i = 0; i < n-1; i++) {

        input = execute_inbuild_commands(cmd_exec[i], input, first, 0);
        first = 0;
    }

    input = execute_inbuild_commands(cmd_exec[i], input, first, 1);

}
void shell_prompt()
{
    if (getcwd(cwd, sizeof(cwd)) != NULL) {

        strcpy(prompt, "minishell:");
        strcat(prompt, cwd);
        strcat(prompt, "$ ");
    }
    else {

        perror("Error in getting curent working directory: ");
    }
}

/* This function initializes the global variables */
int execute_command(int input, int first, int last, char *cmd_exec)
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

	check_for_bckgrnd ();

        if (execvp(args[0], args) < 0) {
		printf("execvp:%s\n", args[0]);
            fprintf(stderr, "%s: Command not found\n",args[0]);
        }
        exit(0);
    }

    else {
    }

    if (last == 1)
        close(mypipefd[0]);

    if (input != 0)
        close(input);

    close(mypipefd[1]);
    return (mypipefd[0]);
}
void clear_variables()
{
    fd = 0;
    flag = 0;
    len = 0;
    no_of_lines = 0;
    cwd[0] = '\0';
    prompt[0] = '\0';
    pid = 0;
    environmment_flag = 0;
}


int
main()
{
    int status;
    char new_line = 0;

    system ("clear");

    using_history();
    do {

	char buffer[1024] = { 0 };
        clear_variables();
	char *p_input_buffer;
	char *p_temp;
	char *p_ex;
	int index = 0;
        shell_prompt();
        input_buffer = readline (prompt);

	p_ex = strstr(input_buffer, "run");
	p_temp = input_buffer;
	if (p_ex != NULL) {
		strremove(input_buffer, "run");
		strcat(input_buffer, " &");
	}
	

        if (!(strcmp(input_buffer, "\n") && strcmp(input_buffer,"")))
            continue;

        if (!strncmp(input_buffer, "quit", 4)) {

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
