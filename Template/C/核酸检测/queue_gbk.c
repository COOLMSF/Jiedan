#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/* �������� */
queue *queue_create()
{
    /* ����һ������ */
    queue *queue = (struct queue*)malloc(sizeof(struct queue));
    
    /* Ϊ�˷������������Ĭ�ϴ���һ�����нڵ� */
    queue_node *node = (struct queue_node*)malloc(sizeof(struct queue_node));
    if(queue==NULL || node==NULL) return NULL;

    node->data = NULL;
    node->next = NULL;
    
    /* ��ʼ������ */
    queue->head = queue->tail = node;
    queue->length = 0;

    return queue;
}

/* ��� */
queue *queue_push_data(queue *queue, void *data)
{
    /* ����һ���ڵ� */
    queue_node *node = (struct queue_node*)malloc(sizeof(struct queue_node));
    if(node==NULL) return NULL;
    node->data = data;

    /* �ڶ�β����Ԫ�� */
    queue->tail->next = node;
    queue->tail = queue->tail->next;

    queue->length++;
    return queue;
}

/* ���� */
void *queue_pull_data(queue *queue)
{
    queue_node *current = queue->head->next;
    
    /* �ж϶������Ƿ������� */
    if(current==NULL) return NULL;

    void *data = current->data;
    
    queue->head->next = current->next;
    
    /* �ж϶����г�ͷ����⣬�Ƿ�ֻ��һ���ڵ㣬����βָ�붪ʧ */
    if(queue->tail==current) {
        queue->tail = queue->head;
    }

    free(current);
    queue->length--;
    return data;
}

/* �ͷŶ��������нڵ㣬�����ͷŶ��б��� */
void queue_empty(queue *queue)
{   
    int length = queue->length;
    queue_node *current, *next;

    /* ע�����ﲻ�ͷ�ͷ�ڵ� */
    current = queue->head->next;
    while (length--)
    {   
        next = current->next;
        free(current);
        current = next;
    }
    
    queue->head->next = NULL;
    queue->head->data = NULL;
    queue->tail = queue->head;
    queue->length = 0;
}

/* �ͷŶ��У����������нڵ� */
void queue_release(queue *queue)
{
    queue_empty(queue);
    /* ע�⣬ͷ�ڵ�ҲҪ�ͷ� */
    free(queue->head);
    free(queue);
}