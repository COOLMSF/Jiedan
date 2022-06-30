all: main

process.o: process.c 
	gcc -g -c $^ -o $@

main.o: main.c

main: main.o process.o
	gcc -g $^ -o $@

clean:
	rm *.o main
