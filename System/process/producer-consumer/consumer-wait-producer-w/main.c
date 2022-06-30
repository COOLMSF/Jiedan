#include "pc.h"

int num = 3;
int main()
{
    pthread_t thread, thread1;

    pthread_mutex_init(&mutex, NULL);

    consumer_init();
    // create consumer and producer
    pthread_create(&thread, NULL, consumer, NULL);
    pthread_create(&thread1, NULL, producer, NULL);
    // wait
    pthread_join(thread, NULL);
    pthread_join(thread1, NULL);

    sem_destroy(&sem);
    sem_destroy(&sem1);

    return 0;
}

