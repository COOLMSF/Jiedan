#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include "queue.h"
// this represents work that has to be 
// completed by a thread in the pool
typedef struct 
{
    void (*function)(void *p);
    // arguments
    void *data;
} Task;

typedef struct {
    int n_tasks;
    Queue *task_queue;
} TaskPool;

// function prototypes
void execute(void (*somefunction)(void *p), void *p);
int pool_submit(void (*somefunction)(void *p), void *p);
void *worker(void *param);
void pool_init(void);
void pool_shutdown(void);

#endif