CC=gcc
CFLAG=-g -o
LIB=-lreadline

all: shell

shell: *.c
	$(CC) -g -o $@ $? -lreadline 

clean:
	@rm -f shell
