/**
 * Implementation of thread pool.
 */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <semaphore.h>
#include "threadpool.h"

#define QUEUE_SIZE 10
#define NUMBER_OF_THREADS 3

#define TRUE 1

// the work queue
Task worktodo;
TaskPool *task_pool = NULL;
sem_t sem;

// the worker bee
pthread_t bee;

// insert a task into the queue
// returns 1 if successful or -1 otherwise, 
int enqueue(Task *t) 
{
    if (!queue_push_tail(task_pool->task_queue, t)) {
        // error
        return -1;
    }

    task_pool->n_tasks++;
    // success
    return 1;
}

// remove a task from the queue
Task *dequeue() 
{
    Task *temp_task = NULL;
    // take a task from task_pool
    if (temp_task = queue_pop_head(task_pool->task_queue)) {

        worktodo.function = temp_task->function;
        worktodo.data = temp_task->data;

        task_pool->n_tasks--;

        return temp_task;
    }
    // failed
    return NULL;
}

// the worker thread in the thread pool
void *worker(void *param)
{
    // kill(0, SIGSTOP);
    // always check if work avaliable
    // while (1) {

        // try lock
        sem_wait(sem);
        if (dequeue()) {
        // execute the task
            execute(worktodo.function, worktodo.data);

            // run finished dequeue
            dequeue();
            pthread_exit(0);
        } else {
			// no task left
		}

        sem_post(sem);
        // try unlock
    // }
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
    // alloc memeory for new task
    Task *new_task = malloc(sizeof(Task));
    if(!new_task) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    // worktodo.function = somefunction;
    // worktodo.data = p;

    new_task->function = somefunction;
    new_task->data = p;

    // enqueue
    if (task_pool->n_tasks < QUEUE_SIZE) {
        if (!enqueue(new_task)) {
            puts("pool_summit fail");
            return -1;
        } else {
            puts("pool submit succeed");
        }
    } else {
        puts("Queue is full");
        return -1;
    }
    return 1;
}

// initialize the thread pool
void pool_init(void)
{
    // init task_pool
    task_pool = malloc(sizeof(TaskPool));
    if (!task_pool) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    task_pool->task_queue = queue_new();
    // fail to new queue
    if (!task_pool->task_queue) {
        perror("fail to new queue");
        exit(EXIT_FAILURE);
    }

    task_pool->n_tasks = 0;
    // task_pool->task_queue = NULL;

    // init sem
    sem_init(&sem, 0, 0);

    // create worker to handler 
    pthread_create(&bee,NULL,worker,NULL);

}

// shutdown the thread pool
void pool_shutdown(void)
{
    pthread_join(bee,NULL);
}
