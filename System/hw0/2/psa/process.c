#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "head.h"

void PSA(linkList *plinklist, PCB pcbs[], int size)
{

	int time = 0;
	int pcbid = 0;
    int pcbnumber = size;
    Node *curnode = NULL;
    Node *minnode = NULL;

    while (1) {
        //等待进程
        for (int i = 0; i < size; i++) {
            if (pcbs[i].arrive_time == time) {
                ll_push_back(plinklist, pcbs[i]);
                //       printf("queue_get_top(pqueue)->next == %p\n", queue_get_top(pqueue)->next);
                printf("PCB %c ARRIVAL TIME IS %d\n", pcbs[i].name, time);
                pcbnumber--;
                //	    printf("pcbnumber == %d\n", pcbnumber);
            }
        }

        if (ll_is_empty(plinklist) && pcbnumber == 0) {
			printf("进程执行完毕！\n");
			break;
		}
//		printf("time is %d \n", time);
        //
		//执行进程
        //
        if (minnode != NULL && (minnode->data).left_time == 0) {
            printf("PCB %c FINISH TIME IS %d\n", (minnode->data).name, time);
            ll_remove(plinklist, minnode);
            minnode = NULL;
        }
        
        if (!ll_is_empty(plinklist) && minnode == NULL) {
            minnode = NULL;
            curnode = plinklist->head;
            while(curnode != NULL) {
                if (minnode == NULL || curnode->data.Priority < minnode->data.Priority) {
                    minnode = curnode;
                }
                curnode = curnode->next;
            }
        }        


        if (minnode != NULL) {
            --(minnode->data).left_time;
        }
        
		time++;
       // sleep(1);
    }
}

void init_queue(Queue *pqueue) {
	pqueue->front = NULL;
	pqueue->rear = NULL;
	pqueue->size = 0;
}

void remove_queue(Queue *pqueue)
{
	Node *current_node = NULL;
	Node *p = NULL;
	assert(pqueue != NULL);
	if (pqueue->front == NULL) {
		return;
	}
	current_node = pqueue->front;
	while (current_node != NULL) {
		p = current_node;
		current_node = current_node->next;
		free(p);
		p = NULL;
	}
}

Node *new_node(DataType data)
{
	Node *ret = (Node *)malloc(sizeof(Node));
	if (ret == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	ret->data = data;
	ret->next = NULL;
	return ret;
}

void queue_enqueue(Queue *pqueue, DataType data)
{
	Node *temp = new_node(data);
	if (pqueue->front == NULL) {
		pqueue->front = temp;
		pqueue->rear = temp;
		++pqueue->size;
	}
	else {
		pqueue->rear->next = temp;
		pqueue->rear = pqueue->rear->next;
		++pqueue->size;
	}
}

void queue_dequeue(Queue *pqueue)
{
	Node *p = NULL;
	assert(pqueue != NULL);
	if (pqueue->front == NULL) {
		return;
	}
	p = pqueue->front;
	pqueue->front = pqueue->front->next;
	free(p);
	p = NULL;
	++pqueue->size;
}

Node *queue_get_top(Queue *pqueue)
{
	return pqueue->front;
}


bool queue_is_empty(const Queue *pqueue)
{
	return pqueue->front == NULL;
}

size_t queue_get_size(const Queue *pqueue)
{
    return pqueue->size;
}

// linked list init
void ll_init(linkList *plinklist)
{
    plinklist->head = NULL;
    plinklist->tail = NULL;
    plinklist->size = 0;    

}

void ll_destroy(linkList *plinklist)
{
	Node *current_node = NULL;
	Node *p = NULL;

	if (plinklist->head == NULL) {
		return;
	}

	current_node = plinklist->head;
	while (current_node != NULL) {
		p = current_node;
		current_node = current_node->next;
		free(p);
		p = NULL;
	}
}

void ll_push_back(linkList *plinklist, DataType data)
{
	Node *temp = new_node(data);
	if (plinklist->head == NULL) {
		// push
		++plinklist->size;
		plinklist->head = temp;
		plinklist->tail = temp;
	}
	else {
		++plinklist->size;
		plinklist->tail->next = temp;
		plinklist->tail = plinklist->tail->next;
	}
}

bool ll_is_empty(const linkList *plinkList)
{
	return plinkList->head == NULL;
}

size_t ll_get_size(const linkList *plinklist)
{
    return plinklist->size;
}

void ll_remove(linkList *plinklist, Node *pnode)
{
    Node *cur = NULL;
    assert(plinklist != NULL);
    cur = plinklist->head;
    if ((plinklist->head) == NULL) {
        return;
    }
    if ((plinklist->head) == pnode) {
        plinklist->head = pnode->next;
        free(pnode);
        pnode = NULL;
        --(plinklist->size);
        return;
    }
    while(cur != NULL) {
        if (cur->next == pnode) {
            cur->next = pnode->next;
            free(pnode);
            pnode = NULL;
            --(plinklist->size);
            break;
        }
        cur = cur->next;
    }
}


