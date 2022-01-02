//
// Created by coolder on 11/17/20.
//
#include "shell.h"

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
int flag_without_pipe,  output_redirection, input_redirection;
int status;
char *input_redirection_file;
char *output_redirection_file;

/* This function initializes the global variables */

void clear_variables()
{
    fd = 0;
    flag = 0;
    len = 0;
    no_of_lines = 0;
    flag_without_pipe = 0;
    output_redirection = 0;
    input_redirection = 0;
    cwd[0] = '\0';
    prompt[0] = '\0';
    pid = 0;
    environmment_flag = 0;
}