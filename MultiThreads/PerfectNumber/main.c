#include <stdio.h>
#include <pthread.h>
#include <math.h>

#define N_MAX_THREAD 1000
#define TRUE 1
#define FALSE 0


int N;
int cnt = 2,sum = 1;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

void* is_factor(void* args){
    while(cnt < sqrt(N)){
        
        pthread_mutex_lock(&mutex);
        
        if(N % cnt == 0){
            sum = sum + cnt + N/cnt;
        }
        cnt++;
        
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t th[N_MAX_THREAD];
    int P;

    printf("Input number and nthreads:");
    scanf("%d%d",&N,&P);
    
    //creat P threads
    for(int i = 1;i <= P;i++){
        pthread_create(&th[i], NULL, is_factor, NULL);
    }
    

    // wait for P threads
    for(int i = 1;i <= P;i++){
        pthread_join(th[i], NULL);
    }
    
    // printf("sum = %d",sum);
    if (sum == N) {
        printf("Perfect number");
    } else {
        printf("Not a Perfec number");
    }
    return 0;
}

