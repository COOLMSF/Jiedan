#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include <sys/time.h>

#define max 100

typedef struct Data{
    int low;
    int high;
}Data;

int arr[max];

double
get_time (void)
{
  struct timeval tv;
  double t;
  if (gettimeofday (&tv, NULL) != 0)
    {
      perror ("gettimeofday");
      abort ();
    }
  t = (double) tv.tv_sec + (double) tv.tv_usec * 1.0e-6;
  return t;
}

void merge(int low, int mid, int high)
{
    int i, j, k;
    int n1 = mid - low + 1;
    int n2 =  high - mid;
    
    int left[n1], right[n2];
    for (i = 0; i < n1; i++)
        left[i] = arr[low + i];
    for (j = 0; j < n2; j++)
        right[j] = arr[mid+ 1+ j];
    
    i = 0;
    j = 0;
    k = low;
    while (i < n1 && j < n2)
    {
        if (left[i] <= right[j])
        {
            arr[k] = left[i];
            i++;
        }
        else
        {
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k] = left[i];
        i++;
        k++;
    }
    
    while (j < n2)
    {
        arr[k] = right[j];
        j++;
        k++;
    }
}
void* mergeSort(void* arg)
{
    Data data = *((Data*)arg);
    int low = data.low;
    int high = data.high;
    
    if (low < high)
    {
        int mid = low+(high-low)/2;
        
        pthread_t thread1;
        Data d1 = {low, mid};
        
        pthread_t thread2;
        Data d2 = {mid+1, high};
        
        pthread_create(&thread1, NULL, mergeSort, &d1);
        pthread_create(&thread2, NULL, mergeSort, &d2);
        
        pthread_join(thread1, NULL);
        pthread_join(thread2, NULL);
        
        merge(low, mid, high);
    }
}

int main(int argc, char *argv[])
{  
	if (argc < 2) {
		printf("%s arrary-size\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	int i, r1;
	r1 = atoi(argv[1]);
	srand(time(NULL));
    printf("Size of array is:\n %d \n",r1);
    for(i=0; i<r1; i++)
		arr[i] = rand() + r1;
    Data data = {0, r1};
    
    pthread_t t;
    
	double start = get_time ();
    pthread_create(&t, NULL, mergeSort, &data);
    pthread_join(t, NULL);
  	double end = get_time ();
    
	printf ("Start = %.2f\nEnd = %.2f\nElapsed = %.2f\n",
	  start, end, end - start);

    printf("Sorted array is: \n");
    for (i=0; i < r1; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}
