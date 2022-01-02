#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int ctoi(char c) 
{
    if (c >= 0x30 && c <= 0x39) {
        return c - 0x30;
    }

    return -1;
}

char itoc(int i)
{
    if (i >= 0 && i <= 9) {
        return i + 0x30;
    }
}

int main(int argc, char const *argv[])
{
    int num;
    int ge, shi, bai, qian;
    char buf[5];

    printf("输入一个四位数:");
    scanf("%d", &num);
    sprintf(buf, "%d", num);

    for (int i = 0; i < 4; i++) {
        buf[i] = itoc((ctoi((buf[i] + 5))));
    }

    for (int i = 0; i < 4; i++) {
        printf("%c", buf[i]);
    }
}
