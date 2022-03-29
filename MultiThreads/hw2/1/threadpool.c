/**
 * Implementation of thread pool.
 */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include "queue.h"
#include "threadpool.h"

#define QUEUE_SIZE 10
#define NUMBER_OF_THREADS 3

#define TRUE 1

// the work queue
Task worktodo;
TaskPool *task_pool = NULL;

// the worker bee
pthread_t bee;

// insert a task into the queue
// returns 0 if successful or 1 otherwise, 
int enqueue(Task *t) 
{
    if (!queue_push_tail(task_pool->task_queue, t)) {
        // error
        return 1;
    }

    // success
    return 0;
}

// remove a task from the queue
Task dequeue() 
{
    Task worktodo;

    if ((worktodo.data = queue_pop_head(task_pool->task_queue)) == QUEUE_NULL)
    return worktodo;
}

// the worker thread in the thread pool
void *worker(void *param)
{
    // execute the task
    execute(worktodo.function, worktodo.data);

    pthread_exit(0);
}

/**
 * Executes the task provided to the thread pool
 */
void execute(void (*somefunction)(void *p), void *p)
{
    (*somefunction)(p);
}

/**
 * Submits work to the pool.
 */
int pool_submit(void (*somefunction)(void *p), void *p)
{
    worktodo.function = somefunction;
    worktodo.data = p;

    queue_push_tail();

    return 0;
}

// initialize the thread pool
void pool_init(void)
{
    pthread_create(&bee,NULL,worker,NULL);
}

// shutdown the thread pool
void pool_shutdown(void)
{
    pthread_join(bee,NULL);
}
