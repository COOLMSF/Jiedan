#include "appli.h"

/* Function used to print a packet in ASCII */
void print_ascii(const u_char* packet, int length)
{
	int i = 0;
	while (i<length){
		if (i%47==0)
			printf("\n\t\t\t");
		if(isprint(packet[i]))
			printf("%c", packet[i]);
		else
			printf(".");
		i++;
	}
	printf("\n");
}