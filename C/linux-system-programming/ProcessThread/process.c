#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char const* argv[])
{
    pid_t pid;

    int data = 0x11;

    printf("Original data is %x\n", data);

    pid = fork();
    // this child
    if (pid == 0) {
        // modify data from child
        data = 0x22;
    } else if (pid > 0) {
        printf("The data from parent is:%x\n", data);
    } else {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    // wait for child
    wait(NULL);
}
