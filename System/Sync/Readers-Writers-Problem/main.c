#include "common.h"
// 全局变量
int readers = 0; 
int writers = 0;
int active_writers = 0;
int global_data_RW = 8;
// 初始化
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t readersQ = PTHREAD_COND_INITIALIZER;
pthread_cond_t writersQ = PTHREAD_COND_INITIALIZER; 
int main()
{
    // 线程号
    pthread_t thr[50]; 
    pthread_t writer_T1;
    pthread_t writer_T2;
    
    // 创建线程，参数为i变量
    // 测试读
    for(int i=0;i<50;i++){
        pthread_create(&thr[i],0,read_first_procedure,(void *)(size_t)i);
    }
    
    // 创建线程，参数为常量
    // 测试写
    pthread_create(&writer_T1,0,write_first_procedure,(void *) 4);
    pthread_create(&writer_T2,0,write_first_procedure,(void *) 7);
    
    // 等待读线程
    for(int i=0;i<50;i++){
        pthread_join(thr[i],0);
    }
    
    // 等待写线程
    pthread_join(writer_T1,0);
    pthread_join(writer_T2,0);
    
    return(0);
}
