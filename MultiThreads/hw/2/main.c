#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

long inputNum, *sequence, j;

void *runner(void *param) {	
	long x;

	sequence[0] = 1;
	sequence[1] = 1;

	for(x = 2; x < inputNum; x++)
	{
		sequence[x] = sequence[x-1]+sequence[x-2];
	}
	pthread_exit(0);
}

int main(int argc, char *argv[]) {
	//This is the thread identifier.
	pthread_t tid;

	//This will hold the set of thread attributes.
	pthread_attr_t attr;

	//Checks if the number of arguments is lesser or greater than 2.
	if(argc != 2) {
		fprintf(stderr, "usage a.out num\n");
		return -1;
	}

	//Checks if the value provided is less than 0. 
	if(atoi(argv[1]) < 0) {
		fprintf(stderr, "%d must be >= 0\n", atoi(argv[1]));
		return -1;
	}
	//Stores the user input if the number of arguments is 2 and if the second argument is greater than 0.
	inputNum = atoi(argv[1]);

	//Creates an array of the user input size. 
	sequence = (long *)malloc(sizeof(long)*inputNum);
	
	/* get the default attributes */
	pthread_attr_init(&attr);

	/* create the thread */
	pthread_create(&tid, &attr, runner, NULL);

	/* wait for the thread to exit */
	pthread_join(tid, NULL);

	printf("Fibonacci number:\n");
	//For loop that iterates through the entire array from 0 to the user input. 
	for(j = 0; j < inputNum; j++) {
		printf("%ld                  %ld\n", j, sequence[j]);
	}
	exit(0);
}
