#include "pc.h"

extern int num;

void *consumer(void *arg)
{
    while(1) {
        int mytime = rand() % 3 + 1;
        sem_wait(&sem);
        srand((unsigned)time(NULL));

        pthread_mutex_lock(&mutex);
        num--;
        printf("[+] consumer consume\n");
        sleep(mytime);
        sem_post(&sem1);
        pthread_mutex_unlock(&mutex);

        printf("[+] consumer over\n");
        printf("left: %d \n",num);
    }
}

void *producer(void *arg)
{
    while(1) {
        int mytime = rand() % 3 + 1;
        sem_wait(&sem1);
        srand((unsigned)time(NULL));

        pthread_mutex_lock(&mutex);
        num++;
        printf("[-] producer produce\n");
        sleep(mytime);
        sem_post(&sem);
        pthread_mutex_unlock(&mutex);

        printf("[-] producer over\n");
        printf("left: %d \n",num);
    }
}

void consumer_init()
{
    // init value for producer
    sem_init(&sem, 0, 6);
    sem_init(&sem1, 0, 10);
}