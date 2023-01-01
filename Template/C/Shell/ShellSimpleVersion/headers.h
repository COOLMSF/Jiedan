#ifndef __HEADERS_H
#define __HEADERS_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

#define PROMPT "simple_shell@ "
// #define PATH_MAX 255

#ifndef PATH_MAX
#define PATH_MAX 1024
#endif

#ifndef MAX_BUF 
#define MAX_BUF 1024
#endif

#define MAX_ARGUMENT 10

int get_args(char *cmd, char *args[]);
void print_banner();
int builtin_pwd();
int builtin_list(char *cmd);
int builtin_changedir(char *cmd);
int builtin_makedir(char *cmd);
int builtin_deldir(char *cmd);
int builtin_cat(char *cmd);
int builtin_echo(char *cmd);
int builtin_wc(char *cmd);
int builtin_cp(char *cmd);
int builtin_touch(char *cmd);
int builtin_rm(char *cmd);
int builtin_mv(char *cmd);

char **alloc_args();
int free_args();

#endif
