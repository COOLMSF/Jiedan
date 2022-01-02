//2019213020
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 6   

typedef struct
{
    int queue[MAX_SIZE];
    int rear;
    int front;
}QUEUE,*pQUEUE;

void InitQueue(pQUEUE p);
int InQueue(pQUEUE p);
void OutQueue(pQUEUE p);

int main()
{
    QUEUE myQueue;
    int ret;
    //char choose;

    InitQueue(&myQueue);
    do{
         ret = InQueue(&myQueue);
    }while(ret >= 0);

    return 0;
}

void InitQueue(pQUEUE p)
{
    p->front = 0;
    p->rear = 0;
}

int InQueue(pQUEUE p)
{
    if((p->rear+1)%MAX_SIZE == p->front)
    {
        printf("overflow\n");
        OutQueue(p);
    }
    printf("Input x:\n");
    if (scanf("%d",&p->queue[p->rear]) == EOF)
        return -1;
    p->rear = p->rear%MAX_SIZE+1;

    if((p->rear+1)%MAX_SIZE == p->front)   //队满则一次性输出数据，并清空队列
    {
        printf("overflow\n");
        OutQueue(p);
    }
    return 0;
}

void OutQueue(pQUEUE p)
{
    if(p->front == p->rear)                //队空则退出程序
    {
        printf("underflow!\n");
        exit(-1);
    }
    while(p->front != p->rear)
    {
        printf("%d\n",p->queue[p->front]);
        p->front = p->front%MAX_SIZE+1;
    }
    return ;
}
