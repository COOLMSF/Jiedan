#include <stdio.h>

int main(int argc, char const *argv[])
{
    int arr[20];

    puts("输入20个整数元素:");

    for (int i = 0; i < 20; i++) {
        scanf("%d", &arr[i]);
    }

    for (int i = 0; i < 20; i++) {
        printf("%d ", arr[20 - i - 1]);
    }
}
