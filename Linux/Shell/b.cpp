#include <stdio.h>

int main() {
    puts("Hello");
    __builtin_trap();
    puts("World.");
}

