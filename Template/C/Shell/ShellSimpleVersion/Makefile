CC=gcc
CFLAG=-g -o
LIB=-lreadline

all: shell

shell: builtin_cat.c builtin_changedir.c builtin_deldir.c builtin_echo.c builtin_list.c builtin_makedir.c builtin_pwd.c builtin_wc.c common.c getpath.c  main.c print_banner.c 
	$(CC) -g -o $@ $? -lreadline 

clean:
	@rm -f shell
