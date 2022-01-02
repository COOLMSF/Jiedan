#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "head.h"

int main()
{
    PCB *pcbs; 
	Queue queue;
    linkList linklist;
    int process_number = 0;

    printf("please input process number: ");
    scanf("%d", &process_number);

    pcbs = (PCB *)malloc(sizeof(struct _PCB) * process_number);
    if (pcbs == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    memset(pcbs, 0, sizeof(PCB) * process_number);
    for (int i = 0; i < process_number; i++) {
        printf("name: ");
        scanf(" %c",&(pcbs[i].name));
        printf("arrive: ");
        scanf("%d",&(pcbs[i].arrive_time));
        printf("process->serve_time: ");
        scanf("%d",&(pcbs[i].serve_time));
        pcbs[i].left_time = pcbs[i].serve_time;
        printf("priority: ");
        scanf("%d",&(pcbs[i].Priority));
    }
	init_queue(&queue);
    ll_init(&linklist);
    PSA(&linklist, pcbs, process_number);
    ll_destroy(&linklist);
	remove_queue(&queue);
	return 0;
}