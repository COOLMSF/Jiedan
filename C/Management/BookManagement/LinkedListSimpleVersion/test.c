#include <stdlib.h>
#include <stdio.h>
struct _AA {
    int a;
    int b;
    char c;
};

int main(int argc, char const* argv[])
{
    struct _AA *p;

    p = malloc(sizeof(struct _AA));

    printf("%d", p->a);
    printf("%d", p->b);
    printf("%c", p->c);
}
