#ifndef _COMMON_H
#define _COMMON_H
#include <pthread.h>
extern int readers;
extern int writers;
extern int active_writers;
extern int global_data_RW;
extern pthread_mutex_t m;
extern pthread_cond_t readersQ;
extern pthread_cond_t writersQ;


void read_lock();
void read_unlock();
void writer_lock();
void writer_unlock();
void read_sync_function(int thr_no);
void write_sync_function(int increment_val);
void *read_first_procedure(void *a);
void *write_first_procedure(void *a);
#endif
