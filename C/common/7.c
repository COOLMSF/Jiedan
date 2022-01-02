#include <stdio.h>
#include <string.h>
#include <math.h>

int main(int argc, char const *argv[])
{
    double x;
    char input[10];

    puts("请输入函数名字:");
    scanf("%s", input);

    if (strcmp(input, "sin") == 0) {
        puts("请输入度数:");
        scanf("%lf", &x);
        printf("结果:%lf\n", sin(x));
    } else if (strcmp(input, "cos") == 0) {
        puts("请输入度数:");
        scanf("%lf", &x);
        printf("结果:%lf\n", cos(x));
    } else if (strcmp(input, "tan") == 0) {
        puts("请输入度数:");
        scanf("%lf", &x);
        printf("结果:%lf\n", tan(x));
    } else {
        puts("输入有误");
    }
}
