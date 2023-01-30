#include "main.h"
#include <stdio.h>

int main(int argc, char const* argv[])
{
	int input;

	puts("1): FIFO");
	puts("2): LRU");

	printf("input your choice:");
	scanf("%d", &input);

	if (input == 1)
		fifo();
	if (input == 2)
		lru();

	return 0;
}
