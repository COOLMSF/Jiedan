#include <stdio.h>

int main(int argc, char const *argv[])
{
    int input;
    double sum = 0.0;

    puts("请输入一个数:");
    scanf("%d", &input);

    if (input % 2 == 0) {
        for (int i = 2; i <= input; i+=2) {
            sum += 1.0/i;
        }
    } else {
        for (int i = 1; i <= input; i+=2) {
            sum += 1.0/i;
        }
    }

    printf("结果:%lf\n", sum);
}
