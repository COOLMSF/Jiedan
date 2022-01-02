test : *.c *.h ./sys/*.h
	gcc -ffreestanding -nostartfiles -nostdlib -e _start -o test *.c -g3

clean :
	rm test
