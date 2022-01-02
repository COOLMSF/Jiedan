#include <stdio.h>

int main(int argc, char const* argv[])
{
    int x, y;
    int height = 10;

    puts("input x, y:");
    scanf("%d, %d", &x, &y);

    if (x < -2 || x > 2 || y < -2 || y > 2)
        height = 0;

    printf("height:%d", height);
}
