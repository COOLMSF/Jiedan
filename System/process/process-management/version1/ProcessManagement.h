#ifndef ProcessManagement_h
#define ProcessManagement_h

#include <stdio.h>

#define MAX_SIZE 20

struct _Tunnel {
    int id;
    char name[MAX_SIZE];
    char buffer[MAX_SIZE];
};

// tunnel to communicate between process
typedef struct _Tunnel Tunnel;

enum process_type{
    process_type_running = 1000,
    process_type_block = -1000,
    process_type_ready = 500
};

struct _PCB {
    int pid;
    int size;
    int state;
    int priority;
    char data[20];
    // mutex to communicate
    int mutex;
    
    int state_internal;
    struct _PCB *next;
};
typedef struct _PCB PCB;

PCB *find_process(PCB *list, size_t pid);
void create_process(PCB *running_list, PCB *block_list, size_t *size);
void show_running_process(PCB *running_list);
void change_process(PCB *running_list, PCB *block_list, size_t *size);
void kill_process(PCB *running_list, size_t *size);
void wake_up_process(PCB *running_list, PCB *block_list, size_t *size);
int is_process_block(PCB *block_list, size_t pid);
int is_process_running(PCB *running_list, size_t pid);

#endif 
