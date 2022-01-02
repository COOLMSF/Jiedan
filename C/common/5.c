#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmpstr(const void* a, const void* b) {
    const char* aa = (const char*)a;
    const char* bb = (const char*)b;
    return strcmp(aa, bb);
}

int main(int argc, char const *argv[])
{
    int num;
    char num_str[5] = { 0 };

    scanf("%d", &num);
    sprintf(num_str, "%d", num);
    qsort(num_str, 5, sizeof(char), cmpstr);

    for (int i = 0; i < 5; i++) {
        printf("%c", num_str[i]);
    }
}
