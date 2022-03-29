#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int grep_file(char *filename, char *str)
{
	char *buf;
	size_t n;
	FILE *fp;


	if ((fp = fopen(filename, "r")) == NULL) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	
	while (getline(&buf, &n, fp) > 0) {
		if (strstr(buf, str))
			printf("%s", buf);
	}
}
