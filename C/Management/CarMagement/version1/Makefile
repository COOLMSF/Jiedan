all: main

clean:
	@rm *.o main

main: main.o carmanagement.o arraylist.o
	clang -g $^ -o $@

main.o: main.c 
	clang -g -c $< -o $@

carmanagement.o: carmanagement.h
arraylist.o: arraylist.h
