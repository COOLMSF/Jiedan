all: ProcessManagement

clean:
	@rm -rf *.o ProcessManagement

ProcessManagement: main.o common.o
	gcc $^ -o $@

main.o: main.c
	gcc -c $< -o $@

common.o : ProcessManagement.c ProcessManagement.h
	gcc -DBUILD32 -c $< -o $@
