#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void cat(const char *filename)
{
    char buf[BUFSIZ] = { 0 };

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    while (fgets(buf, sizeof(buf), fp) != NULL) {
        printf("%s", buf);
    }
}

void check_file_type(const char *filename)
{
    int status;
    struct stat fs;
    char tmp_name[BUFSIZ] = { 0 };

    status = stat(filename, &fs);
    if( status == -1 ) {
        fprintf(stderr,"File error\n");
        exit(1);
    }

    if (strcmp(filename,"/dev/stdin") == 0)
        strcpy(tmp_name, "standard input");
    else
        strcpy(tmp_name, filename);

    /* file permissions are kept in the st_mode member */
    /* The S_ISREG() macro tests for regular files */

    /* should be sent to error stream */
    if (S_ISREG(fs.st_mode))
        fprintf(stderr, "%s is a regular file\n", tmp_name);
    else if (S_ISFIFO(fs.st_mode))
        fprintf(stderr, "%s is a pipe\n", tmp_name);
    else if (S_ISCHR(fs.st_mode))
        fprintf(stderr, "%s is a character device\n", tmp_name);
    else
        fprintf(stderr, "is something else");
}

int main(int argc, char *argv[])
{
    const char *filename;

    if (argc < 2) {
        filename = "/dev/stdin";
        check_file_type(filename);
        cat(filename);
    } else if (strcmp(argv[1], "-")) {
        filename = "/dev/stdout";
        check_file_type(filename);
        cat(filename);
    } else {
        for (int i = 1; i < argc; ++i) {
            filename = argv[i];
            check_file_type(filename);
            cat(filename);
        }
    }
    return(0);
}
