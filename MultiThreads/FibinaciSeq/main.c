#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

//In order to compile and run the program, please use the following call in the command line:
//gcc -o fib fib.c -lpthread
//This will produce an executable command line program fib that can then be called using:
//	./fib x
//	where x is the specific number you wish to call.


//Initializes the variable that will hold the user input.
long inputNum;
//Initialize the array that will hold the sequence.
long *sequence;
//Initialize the variable that will hold loop through the for loop to print out the values. 
long j;

//Thread calls this function. 
void *runner(void *param);

int main(int argc, char *argv[])
{
	//This is the thread identifier.
	pthread_t tid;

	//This will hold the set of thread attributes.
	pthread_attr_t attr;

	//Checks if the number of arguments is lesser or greater than 2.
	if(argc != 2)
	{
		fprintf(stderr, "usage a.out <integer value>\n");
		return -1;
	}

	//Checks if the value provided is less than 0. 
	if(atoi(argv[1]) < 0)
	{
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
	for(j = 0; j < inputNum; j++)
	{
		printf("%ld                  %ld\n", j, sequence[j]);
	}
	exit(0);
}

/* the thread will begin control in this function */
void *runner(void *param)
{	
	long x;
	//These are the 2 first base cases of the fibonacci sequence. 0th number = 1, 1st number = 1.
	sequence[0] = 1;
	sequence[1] = 1;
	//If the user inputs 0 or 1, either 1 or 1 1 is outputted as these are the first 2 numbers of the fibonacci sequence. If the 
	//user inputs anything else, then the for loop runs for the rest of the fibonacci numbers up to the 92nd fibonacci number as 
	//that is the limit of the long data type used here.  
	for(x = 2; x < inputNum; x++)
	{
		sequence[x] = sequence[x-1]+sequence[x-2];
	}
	pthread_exit(0);
}

