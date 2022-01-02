all: main

clean:
	@rm -rf *.o main

main: main.o common.o

main.o: main.c 
	gcc -c $< -o $@

common.o: common.c 
	gcc -c $< -o $@
