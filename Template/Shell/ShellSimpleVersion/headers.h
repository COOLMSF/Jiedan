#ifndef __HEADERS_H
#define __HEADERS_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <readline/readline.h>
#include <readline/history.h>

#define PROMPT "wuchunyou@"
// #define PATH_MAX 255

char *getargs(char *cmd);
void print_banner();
int builtin_pwd();
int builtin_list(char *cmd);
int builtin_changedir(char *cmd);
int builtin_makedir(char *cmd);
int builtin_deldir(char *cmd);

#endif
