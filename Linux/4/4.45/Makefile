CC = gcc

CFLAGS = -Wall -g

FREESTANDING_FLAGS = -ffreestanding -nostartfiles -nostdlib

test : _exit.o _start.o close.o creat.o errno.o execve.o exit.o itoa.o lseek.o malloc.o mmap.o munmap.o open.o printf.o read.o strchr.o strerror.o strlen.o strncpy.o test.o write.o clone.o fork.o getpid.o clock_nanosleep.o nanosleep.o sleep.o wait4.o waitpid.o wait.o sigaction.o signal.o rt_sigaction.o pwrite.o pread.o pwrite64.o pread64.o vfork.o
	$(CC)  $(FREESTANDING_FLAGS) -o $@ $^ $(CFLAGS)

_exit.o: _exit.c unistd.h stddef.h syscall.h errno.h
	$(CC) $(FREESTANDING_FLAGS) -c -o $@ $< $(CFLAGS)

_start.o: _start.c stdlib.h stddef.h
	$(CC) $(FREESTANDING_FLAGS) -c -o $@ $< $(CFLAGS)

close.o: close.c unistd.h stddef.h syscall.h errno.h
	$(CC) $(FREESTANDING_FLAGS) -c -o $@ $< $(CFLAGS)

creat.o: creat.c fcntl.h syscall.h errno.h
	$(CC) $(FREESTANDING_FLAGS) -c -o $@ $< $(CFLAGS)

errno.o: errno.c errno.h
	$(CC) $(FREESTANDING_FLAGS) -c -o $@ $< $(CFLAGS)

execve.o: execve.c unistd.h stddef.h syscall.h errno.h
	$(CC) $(FREESTANDING_FLAGS) -c -o $@ $< $(CFLAGS)

exit.o: exit.c stdlib.h stddef.h unistd.h
	$(CC) $(FREESTANDING_FLAGS) -c -o $@ $< $(CFLAGS)

itoa.o: itoa.c stdlib.h stddef.h
	$(CC) $(FREESTANDING_FLAGS) -c -o $@ $< $(CFLAGS)

lseek.o: lseek.c unistd.h stddef.h syscall.h errno.h
	$(CC) $(FREESTANDING_FLAGS) -c -o $@ $< $(CFLAGS)

malloc.o: malloc.c stdlib.h stddef.h sys/mman.h
	$(CC) $(FREESTANDING_FLAGS) -c -o $@ $< $(CFLAGS)

mmap.o: mmap.c syscall.h errno.h stddef.h
	$(CC) $(FREESTANDING_FLAGS) -c -o $@ $< $(CFLAGS)
	
munmap.o: munmap.c syscall.h errno.h stddef.h
	$(CC) $(FREESTANDING_FLAGS) -c -o $@ $< $(CFLAGS)

open.o: open.c fcntl.h syscall.h errno.h
	$(CC) $(FREESTANDING_FLAGS) -c -o $@ $< $(CFLAGS)
	
printf.o: printf.c stdio.h unistd.h stddef.h string.h stdlib.h
	$(CC) $(FREESTANDING_FLAGS) -c -o $@ $< $(CFLAGS)

read.o: read.c unistd.h stddef.h syscall.h errno.h
	$(CC) $(FREESTANDING_FLAGS) -c -o $@ $< $(CFLAGS)

strchr.o: strchr.c string.h stddef.h
	$(CC) $(FREESTANDING_FLAGS) -c -o $@ $< $(CFLAGS)
	
strerror.o: strerror.c string.h stddef.h errno.h
	$(CC) $(FREESTANDING_FLAGS) -c -o $@ $< $(CFLAGS)

strlen.o: strlen.c string.h stddef.h
	$(CC) $(FREESTANDING_FLAGS) -c -o $@ $< $(CFLAGS)

strncpy.o: strncpy.c string.h stddef.h
	$(CC) $(FREESTANDING_FLAGS) -c -o $@ $< $(CFLAGS)
	
test.o: test.c stdio.h stdlib.h stddef.h
	$(CC) $(FREESTANDING_FLAGS) -c -o $@ $< $(CFLAGS)
	
write.o: write.c unistd.h stddef.h syscall.h errno.h
	$(CC) $(FREESTANDING_FLAGS) -c -o $@ $< $(CFLAGS)

clone.o: clone.c syscall.h errno.h clone.h
	$(CC) $(FREESTANDING_FLAGS) -c -o $@ $< $(CFLAGS)

fork.o: fork.c unistd.h stddef.h sys/types.h clone.h signal.h
	$(CC) $(FREESTANDING_FLAGS) -c -o $@ $< $(CFLAGS)

getpid.o: getpid.c syscall.h errno.h unistd.h stddef.h sys/types.h
	$(CC) $(FREESTANDING_FLAGS) -c -o $@ $< $(CFLAGS)

clock_nanosleep.o: clock_nanosleep.c time.h syscall.h errno.h
	$(CC) $(FREESTANDING_FLAGS) -c -o $@ $< $(CFLAGS)

nanosleep.o: nanosleep.c time.h
	$(CC) $(FREESTANDING_FLAGS) -c -o $@ $< $(CFLAGS)

sleep.o: sleep.c unistd.h stddef.h sys/types.h time.h
	$(CC) $(FREESTANDING_FLAGS) -c -o $@ $< $(CFLAGS)

wait4.o: wait4.c sys/wait.h sys/types.h syscall.h errno.h
	$(CC) $(FREESTANDING_FLAGS) -c -o $@ $< $(CFLAGS)

waitpid.o: waitpid.c sys/wait.h sys/types.h
	$(CC) $(FREESTANDING_FLAGS) -c -o $@ $< $(CFLAGS)

wait.o: wait.c sys/wait.h sys/types.h
	$(CC) $(FREESTANDING_FLAGS) -c -o $@ $< $(CFLAGS)

signal.o: signal.c signal.h errno.h
	$(CC) $(FREESTANDING_FLAGS) -c -o $@ $< $(CFLAGS)

sigaction.o: sigaction.c signal.h syscall.h errno.h
	$(CC) $(FREESTANDING_FLAGS) -c -o $@ $< $(CFLAGS)

rt_sigaction.o: rt_sigaction.c signal.h stddef.h syscall.h errno.h
	$(CC) $(FREESTANDING_FLAGS) -c -o $@ $< $(CFLAGS)

pread64.o: pread64.c unistd.h stddef.h sys/types.h syscall.h errno.h
	$(CC) $(FREESTANDING_FLAGS) -c -o $@ $< $(CFLAGS)

pread.o: pread.c unistd.h stddef.h sys/types.h
	$(CC) $(FREESTANDING_FLAGS) -c -o $@ $< $(CFLAGS)

pwrite64.o: pwrite64.c unistd.h stddef.h sys/types.h syscall.h errno.h
	$(CC) $(FREESTANDING_FLAGS) -c -o $@ $< $(CFLAGS)

pwrite.o: pwrite.c unistd.h stddef.h sys/types.h
	$(CC) $(FREESTANDING_FLAGS) -c -o $@ $< $(CFLAGS)

vfork.o: vfork.c unistd.h stddef.h sys/types.h
	$(CC) $(FREESTANDING_FLAGS) -c -o $@ $< $(CFLAGS)
	
clean :
	rm *.o
