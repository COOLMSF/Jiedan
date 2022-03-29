#define _GNU_SOURCE

#include<fcntl.h>
#include<assert.h>
#include<dirent.h>
#include<errno.h>
#include<math.h>
#include<memory.h>
#include<pwd.h>
#include<stdint.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<sys/ptrace.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/msg.h>
#include<time.h>
#include<unistd.h>
#include <ftw.h>
#include<getopt.h>
#include<pthread.h>
#include<setjmp.h>
#include<termio.h>
#include<error.h>
#include<err.h>
#include<sys/ioctl.h>
#include <readline/readline.h>
#include <readline/history.h>

// Include book header
// #include "../aupe/apue.3e/include/apue.h"
// #include "../UNP/unpv13e/lib/unp.h"
// Conflict with unp.h
// Include my error hanlder header file
// #include "MyMacro.h"

// #include <glib-2.0/glib.h>
// #include "glib-2.0/glib/glist.h"
