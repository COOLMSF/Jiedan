#include "common.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
extern int readers;
extern int writers;
extern int active_writers;
extern int global_data_RW;
extern pthread_mutex_t m;
extern pthread_cond_t readersQ;
extern pthread_cond_t writersQ;


void read_lock() {
    // 互斥量
    pthread_mutex_lock(&m); 
    // 条件变量需要加互斥锁，具体为什么请百度一下
    while (!(writers == 0))
        // 需要signal解锁
        pthread_cond_wait(&readersQ, &m);
    readers++;
    // 解锁
    pthread_mutex_unlock(&m); 
}

void read_unlock() {
    pthread_mutex_lock(&m); 
    // readers == 0, 解锁
    if (--readers == 0)
        pthread_cond_signal(&writersQ); 
    pthread_mutex_unlock(&m); 
}

void writer_lock() {
    pthread_mutex_lock(&m); 
    writers++; // 增加写者数量
    // 确保无人读写, 有人则睡眠
    while (!((readers == 0) && (active_writers == 0))) {
        pthread_cond_wait(&writersQ, &m);
    }
    active_writers++;
    pthread_mutex_unlock(&m); 
}

void writer_unlock( ) {
    pthread_mutex_lock(&m); 
    writers--; 
    active_writers--; 
    // 解锁后，唤醒其他写线程
    if (writers > 0)
        pthread_cond_signal(&writersQ); 
    else
        // 唤醒所有读线程
        pthread_cond_broadcast(&readersQ); 
    // 解锁
    pthread_mutex_unlock(&m); // unlock the mutex
}

// 测试
void read_sync_function(int thr_no){
    read_lock();
    printf("thread number %d read the shared value and it was %d.\n",thr_no,global_data_RW);
    read_unlock();
} 

void write_sync_function(int increment_val){
    writer_lock();
    global_data_RW += increment_val;
    printf("The writer thread increments the value by %d and the new global data value is %d.\n",increment_val,global_data_RW);
    writer_unlock();
} 

void *read_first_procedure(void *a){
    int c = (int ) a;
    
    int upper = 180;
    int lower = 120;
    int rand_wait_time = (rand() % (upper - lower + 1)) + lower; 
    
    usleep(rand_wait_time); 
    read_sync_function(c);
    return(0);
}

void *write_first_procedure(void *a){
    int increment_val  = (int ) a;
    write_sync_function(increment_val);
    return(0);
}

