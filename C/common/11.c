#include <stdio.h>

int min(int a, int b)
{
    return a < b ? a : b;
}

int main(int argc, char const *argv[])
{
    int a, b, c;

    puts("输入三个数:");
    scanf("%d", &a);
    scanf("%d", &b);
    scanf("%d", &c);

    printf("最小数:%d\n", min(min(a, b), c));
}
