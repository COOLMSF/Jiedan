#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#define BILLION 1E9
#define NUM_THREADS 10
#define ITERATIONS  1000000000

void *piCal(void *threadid)
{
  
   long id;
   id = (long)threadid;
   int tid = (int)id;
   int r = time(NULL) * (tid + 1);
   long int in_count = 0;
  
   long int tot_iterations= ITERATIONS/NUM_THREADS;
   
   int counter=0;
   
   //calculation
   for(counter=0;counter<tot_iterations;counter++){
     float x = (float)rand_r(&r)/(float)RAND_MAX;
     float y = (float)rand_r(&r)/(float)RAND_MAX;
     x = x * 2 - 1;
     y = y * 2 - 1;
     float result = x*x + y*y;
      if(result<=1){
         in_count = in_count + 1;         //check if the generated value is inside a unit circle  
	}
      
   }
   
   //get the remaining iterations calculated by thread 0
   if(tid==0){
      long remainder = ITERATIONS%NUM_THREADS;
      for(counter=0;counter<remainder;counter++){
	float x = (float)rand_r(&r)/(float)RAND_MAX;
     	float y = (float)rand_r(&r)/(float)RAND_MAX;
     	x = x *2 -1;
     	y = y * 2 -1;  
	
 
      float result = x*x + y*y;
      
      if(result<1){
         in_count = in_count + 1;         //check if the generated value is inside a unit circle
      }
      
   }
   }
   // printf("%d teee \n",in_count);
    pthread_exit((void*)in_count); 

}

int main(int argc, char** argv)
{
  
   pthread_t threads[NUM_THREADS];
   struct timespec start, end;
   int thread;
   
   long t;
   long int threads_in =0;
//Create
   for (t =0;t<NUM_THREADS;t++){
	thread = pthread_create(&threads[t],NULL,piCal,(void *)t);
      if (thread){
       printf("ERROR; return code from pthread_create() is %d\n", thread);
       exit(-1);
       }
     }
//Start time
   clock_gettime(CLOCK_MONOTONIC, &start);
   //JOIN
   for(t=0;t<NUM_THREADS;t++){
      void *status;
      pthread_join(threads[t], &status);
                  //keep track of the total in count
     // printf("%d test \n",(int)status);
      long int x = (long int)status;
      threads_in = threads_in + x;
    }
//END TIME
   clock_gettime(CLOCK_MONOTONIC, &end);
   printf("Pi is %lf \n", 4*((float)threads_in/(float)ITERATIONS));
   double diff = ( end.tv_sec - start.tv_sec )+ ( end.tv_nsec - start.tv_nsec)/ BILLION;
   printf("Time in secs : %lf\n",diff);
   
  
   
 
   pthread_exit(NULL);
   
}
