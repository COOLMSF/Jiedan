CC = gcc

CFLAGS = --std=gnu11 -Wall -Werror -g

all: test2

test2: test2.c MyMalloc.c
	$(CC) $(CFLAGS) -o test2 test2.c MyMalloc.c

clean:
	rm -f *.o test2

