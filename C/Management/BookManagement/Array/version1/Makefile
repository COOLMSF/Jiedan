all: main

clean:
	@rm *.o main

main: main.o bookmanagement.o arraylist.o
	clang -g $^ -o $@

main.o: main.c 
	clang -g -c $< -o $@

bookmanagement.o: bookmanagement.c bookmanagement.h
	clang -g -c $< -o $@

arraylist.o: arraylist.c arraylist.h
	clang -g -c $< -o $@