#pragma once

typedef struct PCB {
	char name;                 //������
	int ArrivalTime;           //����ʱ��
	int ServiceTime;           //����ʱ��
	int StartTime;             //��ʼʱ��
	int FinishTime;            //���ʱ��
    int ResidualTime;          //ʣ�����ʱ��
	double WholeTime;          //��תʱ��
	double weightWholeTime;    //��Ȩ��תʱ��
    int Priority;              //���ȼ�
}PCB;
typedef PCB DataType;
typedef struct Node {
	DataType data;
	struct Node *next;
}Node;
typedef struct Queue {
	Node *front;
	Node *rear;
	size_t size;			//�������м���Ԫ��
}Queue;


typedef struct linkList {
    Node *head;
    Node *tail;
    size_t size;
}linkList;

void QueueInit(Queue *pqueue) {			//��ʼ��
	assert(pqueue != NULL);
	pqueue->front = NULL;
	pqueue->rear = NULL;
	pqueue->size = 0;
}

void QueueDestroy(Queue *pqueue)
{
	Node *cur = NULL;
	Node *del = NULL;
	assert(pqueue != NULL);
	if (pqueue->front == NULL) {
		return;
	}
	cur = pqueue->front;
	while (cur != NULL) {
		del = cur;
		cur = cur->next;
		free(del);
		del = NULL;
	}
}

Node *CreatNode(DataType data)
{
	Node *ret = (Node *)malloc(sizeof(Node));
	if (ret == NULL) {
		exit(0);
	}
	ret->data = data;
	ret->next = NULL;
	return ret;
}

void QueuePush(Queue *pqueue, DataType data)
{
	assert(pqueue != NULL);
	Node *temp = CreatNode(data);
	if (pqueue->front == NULL) {
		pqueue->front = temp;
		pqueue->rear = temp;
		//pqueue->rear = pqueue->front = temp;
		++pqueue->size;
	}
	else {
		pqueue->rear->next = temp;
		pqueue->rear = pqueue->rear->next;
		//pqueue->rear = temp;
		++pqueue->size;
	}
}

void QueuePop(Queue *pqueue)
{
	assert(pqueue != NULL);
	Node *del = NULL;
	assert(pqueue != NULL);
	if (pqueue->front == NULL) {
		return;
	}
	del = pqueue->front;
	pqueue->front = pqueue->front->next;
	free(del);
	del = NULL;
	++pqueue->size;
    
}

Node *QueueTop(Queue *pqueue)
{
	return pqueue->front;
}


bool QueueEmpty(const Queue *pqueue)
{
	return pqueue->front == NULL;
}

size_t QueueSize(const Queue *pqueue)
{
    return pqueue->size;
}




