#include <stdio.h>

int main()
{
	int i, j;
	printf("\n");
	for (i = 1; i < 11; i++) {
	for (j = 1; j < i; j++)
		printf("%c%c", 64, 64);
	printf("\n");
	}
}

