#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_t tid[2];

void* doSomeThing(void *data)
{
	*(int *)data = 0x11;
}

int main(void)
{
    int i = 0;
	int data = 0x22;
    int err;

	printf("Original data is: %x\n", data);

    while(i < 2)
    {
        err = pthread_create(&(tid[i]), NULL, &doSomeThing, &data);
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));
        else
            printf("\n Thread created successfully\n");

        i++;
    }
	printf("Thread modified data, the data is:%x\n", data);

    sleep(5);
    return 0;
}
