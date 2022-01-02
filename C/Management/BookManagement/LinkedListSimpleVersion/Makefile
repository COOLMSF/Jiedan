all: main

clean:
	@rm *.o main

main: main.o bookmanagement.o slist.o
	clang -g $^ -o $@

main.o: main.c slist.o bookmanagement.o
	clang -g -c $< -o $@

bookmanagement.o: bookmanagement.c bookmanagement.h
	clang -g -c $< -o $@

slist.o: slist.c slist.h
	clang -g -c $< -o $@
