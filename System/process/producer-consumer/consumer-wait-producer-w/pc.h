#ifndef PC_H
#define PC_H

#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/mman.h>
#include <semaphore.h>

sem_t sem, sem1;
pthread_mutex_t mutex;

void *consumer(void *arg);
void *producer(void *arg);
void *filter(void *arg);
void consumer_init();

#endif
