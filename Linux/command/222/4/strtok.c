#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) 
{
    char string[1024];
    FILE *fp;
    char *buf;

    fp = fopen("a.txt", "r");
    if (fp == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    while (fgets(string, 1024, fp) > 0) {
        buf = strtok(string, " ");
        while (buf) {
            puts(buf);
            buf = strtok(NULL, " ");
        }
    }

}
