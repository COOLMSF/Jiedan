#include <stdio.h>
// #include <unistd.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
// #include <stdbool.h>
#include "head_gbk.h"

void RR(Queue *pqueue, PCB pcbs[], int size)
{ 
    int time_backup;
    int start_time, stop_time;
	//这里是时间片的大小
	int q = 0;
    printf("please input q:");
    scanf("%d", &q);
	//这个表示本次时间片q剩下多少
	int lessq = 0;
    int pcbnumber = size;
	//表示本进程还需要的服务时间
	int time = 0;
    int c = 1;
	while (1) {
		//等待进程
        for (int i = 0; i < size; i++) {
            if (pcbs[i].ArrivalTime == time) {
                QueuePush(pqueue, pcbs[i]);
                printf("PCB %c ARRIVAL TIME IS %d\n", pcbs[i].name, time);
                start_time = time;
                pcbnumber--;
                // printf("pcbnumber == %d\n", pcbnumber);
            }
        }
        if (QueueEmpty(pqueue) && pcbnumber == 0) {
			printf("进程执行完毕！\n");
			break;
		}
		// printf("当前时间 %d \n", time);
		//执行进程
        if (lessq == 0) {
            c++;
            if (!QueueEmpty(pqueue) && QueueTop(pqueue)->data.ResidualTime == 0) {
                printf("PCB %c 完成时间是 %d\n", QueueTop(pqueue)->data.name, time);
                QueuePop(pqueue);
                // printf("%d-%d-%d\n", pcbnumber,  time, 1);
                printf("%d-%d-%d\n", pcbnumber,  c, time);
            }
            else {
                if (!QueueEmpty(pqueue) && 
                    (QueueTop(pqueue)->data.ServiceTime != 
                    QueueTop(pqueue)->data.ResidualTime)) {
                    pqueue->rear->next = pqueue->front;
                    pqueue->rear = pqueue->rear->next;
                    pqueue->front = pqueue->front->next;
                    pqueue->rear->next = NULL;
                }
            }
            lessq = q;
		}else {
            if (!QueueEmpty(pqueue) && QueueTop(pqueue)->data.ResidualTime == 0) {
                printf("PCB %c 完成时间是 %d\n", QueueTop(pqueue)->data.name, time);
                QueuePop(pqueue);
                lessq = q;
                printf("%d-%d-%d\n", pcbnumber,  c, time);
            }
        }
        if (!QueueEmpty(pqueue)) {
            QueueTop(pqueue)->data.ResidualTime--;
        }
        lessq--;
		time++;
        //sleep(1);
	}
}
int main()
{
    int processnumber = 0;
	Queue queue;
    linkList linklist;
    printf("输入进程数量: ");
    scanf("%d", &processnumber);
    // 分配内存
    PCB *pcbs = (PCB *) malloc (sizeof(PCB) * processnumber);
    memset(pcbs, 0, sizeof(PCB) * processnumber);
    for (int i = 0; i < processnumber; i++) {
        printf("进程名: ");
        scanf(" %c",&(pcbs[i].name));
        printf("到达时间: ");
        scanf("%d",&(pcbs[i].ArrivalTime));
        printf("服务时间: ");
        scanf("%d",&(pcbs[i].ServiceTime));
        pcbs[i].ResidualTime = pcbs[i].ServiceTime;
        printf("优先级: ");
        scanf("%d",&(pcbs[i].Priority));
    }

	int input = 0;
	QueueInit(&queue);
	RR(&queue, pcbs, processnumber);
	QueueDestroy(&queue);
	return 0;
}
