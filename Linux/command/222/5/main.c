#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    pid_t pid;
    double float_arr[3] = { 1.234, 2.345, 3.456 };
    int pipe_fd[2];

    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0){
        // child
        close(pipe_fd[0]);
        if (write(pipe_fd[1], float_arr, 3 * sizeof(double)) < 0) {
            perror("write on child");
            exit(EXIT_FAILURE);
        }
    } else {
        // parent
        double avg = 0.0;
        double *float_arr = malloc(sizeof(double) * 3);

        if (float_arr == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        close(pipe_fd[1]);
        if (read(pipe_fd[0], float_arr, sizeof(double) * 3) < 0) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        puts("Data from parent:");
        for (int i = 0; i < 3; i++) {
            avg += float_arr[i];
            printf("%lf\n", float_arr[i]);
        }

        avg /= 3;
        printf("Avg: %lf\n", avg);
    }
}
