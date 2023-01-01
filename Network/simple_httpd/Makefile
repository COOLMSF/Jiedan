all: httpd

func.o: func.c
	gcc -W -Wall -lpthread -c -o func.o func.c

main.o: main.c
	gcc -W -Wall -c -o main.o main.c

httpd: main.o func.o
	gcc -W -Wall -lpthread -o httpd main.o func.o

clean:
	rm httpd *.o

