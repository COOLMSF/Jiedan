#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const* argv[])
{
    int num;
    char buf[10];

    puts("input a number:");
    scanf("%d", &num);

    // convert int to string
    sprintf(buf, "%d", num);

    printf("len:%d\n", strlen(buf));

    puts("output:");
    for (int i = 0; i < strlen(buf); i++) {
        printf("%c", buf[i]);
    }

    puts("");
    puts("reverse output:");
    for (int i = 0; i < strlen(buf) + 1; i++) {
        printf("%c", buf[strlen(buf) - i]);
    }
}

