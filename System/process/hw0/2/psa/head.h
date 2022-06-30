#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

struct _PCB {
	char name;                 
	int arrive_time;           
	int serve_time;           
	int start_time;             
	int finish_time;            
    int left_time;       
	double total_time;         
    int Priority;          
};

typedef struct _Node Node;
struct _Queue {
	Node *front;
	Node *rear;
	size_t size;
};
typedef struct _PCB DataType;

struct _Node {
    DataType data;
    struct _Node *next;
};

struct _linkList {
    Node *head;
    Node *tail;
    size_t size;
};

typedef struct _PCB PCB;
typedef struct _Queue Queue;
typedef struct _linkList linkList;


void PSA(linkList *plinklist, PCB pcbs[], int size);
void init_queue(Queue *pqueue);
void remove_queue(Queue *pqueue);
Node *new_node(DataType data);
void ll_push_back(linkList *plinklist, DataType data);
bool ll_is_empty(const linkList *plinkList);
size_t ll_get_size(const linkList *plinklist);
void ll_remove(linkList *plinklist, Node *pnode);
void ll_init(linkList *plinklist);
void ll_destroy(linkList *plinklist);