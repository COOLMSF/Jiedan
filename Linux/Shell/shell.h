//
// Created by coolder on 11/17/20.
//
#include "allheaders.h"

#ifndef SHELL_SHELL_H
#define SHELL_SHELL_H

#endif //SHELL_SHELL_H

/********** Declaring Global variables **********/

extern int fd;
extern char *args[512];
extern char prompt[512];
extern char *history_file;
extern char *input_buffer;
extern char *cmd_exec[512];
extern int flag, len;
extern char cwd[1024];
extern int bckgrnd_flag;
extern pid_t pid;
extern int no_of_lines;
extern int environmment_flag;
extern int flag_without_pipe, output_redirection, input_redirection;
extern int status;
extern char *input_redirection_file;
extern char *output_redirection_file;


/********** Declaring Function Prototypes **********/

void clear_variables();
void print_history_list ();
void environmment();
void set_environment_variables();
void change_directory();
char *skipwhite (char* );
void tokenize_by_space (char *);
void tokenize_redirect_input_output(char *);
void tokenize_redirect_input(char *);
void tokenize_redirect_output(char *);
char *skip_double_quote(char* );
int execute_inbuild_commands(char *, int, int, int);
void tokenize_by_pipe ();
int execute_command(int, int, int, char *);
void shell_prompt();
void sigintHandler(int );
void check_for_bckgrnd ();
void grep_file(char *filename, char *str);
