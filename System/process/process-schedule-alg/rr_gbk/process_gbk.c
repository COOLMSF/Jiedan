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
	//������ʱ��Ƭ�Ĵ�С
	int q = 0;
    printf("please input q:");
    scanf("%d", &q);
	//�����ʾ����ʱ��Ƭqʣ�¶���
	int lessq = 0;
    int pcbnumber = size;
	//��ʾ�����̻���Ҫ�ķ���ʱ��
	int time = 0;
    int c = 1;
	while (1) {
		//�ȴ�����
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
			printf("����ִ����ϣ�\n");
			break;
		}
		// printf("��ǰʱ�� %d \n", time);
		//ִ�н���
        if (lessq == 0) {
            c++;
            if (!QueueEmpty(pqueue) && QueueTop(pqueue)->data.ResidualTime == 0) {
                printf("PCB %c ���ʱ���� %d\n", QueueTop(pqueue)->data.name, time);
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
                printf("PCB %c ���ʱ���� %d\n", QueueTop(pqueue)->data.name, time);
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
    printf("�����������: ");
    scanf("%d", &processnumber);
    // �����ڴ�
    PCB *pcbs = (PCB *) malloc (sizeof(PCB) * processnumber);
    memset(pcbs, 0, sizeof(PCB) * processnumber);
    for (int i = 0; i < processnumber; i++) {
        printf("������: ");
        scanf(" %c",&(pcbs[i].name));
        printf("����ʱ��: ");
        scanf("%d",&(pcbs[i].ArrivalTime));
        printf("����ʱ��: ");
        scanf("%d",&(pcbs[i].ServiceTime));
        pcbs[i].ResidualTime = pcbs[i].ServiceTime;
        printf("���ȼ�: ");
        scanf("%d",&(pcbs[i].Priority));
    }

	int input = 0;
	QueueInit(&queue);
	RR(&queue, pcbs, processnumber);
	QueueDestroy(&queue);
	return 0;
}
