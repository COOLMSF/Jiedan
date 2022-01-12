#include <stdio.h>

int main()
{
    int n, sum;
    sum = 0;

    printf("input n:");
    scanf("%d", &n);
    int arr[n][n];

    puts("input data:");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &arr[i][j]);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                sum += arr[i][j];
                sum += arr[n-i-1][j];
                // printf("%d %d\n", arr[i][j], arr[n-i-1][j]);
            }
        }
    }

    printf("sum:%d", sum);
}

