#ifndef QUEUE_H
#define QUEUE_H

#define QUEUE_NULL ((void *) 0)

typedef struct _Queue Queue;
typedef void * QueueValue;
typedef struct _QueueEntry QueueEntry;

struct _QueueEntry {
	QueueValue data;
	QueueEntry *prev;
	QueueEntry *next;
};

struct _Queue {
	QueueEntry *head;
	QueueEntry *tail;
};


Queue *queue_new(void);
void queue_free(Queue *queue);
int queue_push_head(Queue *queue, QueueValue data);
int queue_push_tail(Queue *queue, QueueValue data);
int queue_is_empty(Queue *queue);
QueueValue queue_pop_head(Queue *queue);
QueueValue queue_peek_head(Queue *queue);
QueueValue queue_pop_tail(Queue *queue);
QueueValue queue_peek_tail(Queue *queue);

#endif