#include <stdio.h>
#include <stdlib.h>
#include "ProcessManagement.h"

void create_process(PCB *process_list_runnning, PCB *process_list_block, size_t *size)
{
    size_t pid;
    printf("input pid:\n");
    scanf("%zu",&pid);
    
    if (*size >= MAX_SIZE) {
        fprintf(stderr, "[-] not enough memory");
        exit(EXIT_FAILURE);
    }
    // alloc memory for process
    PCB *p = (PCB *)malloc(sizeof(PCB));
    if (p == NULL) {
        perror("malloc");
    }
    if (is_process_block(process_list_block, pid)) {
        puts("[+] process is in blocking list\n");
        return;
    }
    if (is_process_running(process_list_runnning, pid)) {
        puts("[+] process is in running list\n");
        return;
    }
    p->pid = pid;

    // get info for process
    printf("input priority:\n");
    scanf("%d",&p->priority);
    printf("process data:\n");
    scanf("%s",p->data);
    printf("input size(running time):\n");
    scanf("%d",&p->size);
    // set process status
    p->state = process_type_running;
    *size = *size + 1;
    // end list
    p->next = NULL;

    PCB *tmp = process_list_runnning;
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = p;
}

void show_running_process(PCB *process_list_runnning)
{
    PCB *s = process_list_runnning->next;

    while (s != NULL) {
        printf("id:%d\n",s->pid);
        printf("priority:%d\n",s->priority);
        printf("size:%d\n",s->size);
        printf("data:%s\n",s->data);
        s = s->next;
    }
}

void change_process(PCB *process_list_runnning, PCB *process_list_block, size_t *size)
{
    size_t pid;

    printf("input id:\n");
    scanf("%zu",&pid);

    if (*size == 0) {
        printf("[-] no process\n");
        return;
    }

    if (is_process_running(process_list_runnning, pid)) {
        PCB *p = process_list_block;
        PCB *s = find_process(process_list_runnning, pid);

        *size -= 1;
        s->next->state = process_type_block;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = s->next;
        s->next = s->next->next;
        p->next->next = NULL;
        printf("[+] succeed\n");
    } else {
        printf("[-] process not found\n");
    }
}

void kill_process(PCB *process_list_runnning, size_t *size)
{
    size_t pid;
    printf("input id:\n");
    scanf("%lu",&pid);

    if (*size == 0) {
        printf("[-] no process found\n");
        return;
    }
    
    if (is_process_running(process_list_runnning, pid)) {
        // minus counter first
        *size = *size - 1;

        PCB *p, *thread;
        p = find_process(process_list_runnning, pid);
        thread = p->next;
        p->next = p->next->next;
        
        free(thread);
        printf("[+] success\n");
    } else {
        printf("[-] not found\n");
    }
}

void wake_up_process(PCB *process_list_runnning, 
            PCB *process_list_block, size_t *size){

    size_t pid;

    printf("input id:\n");
    scanf("%zu",&pid);

    PCB *s = process_list_block;
    if (s->next == NULL) {
        printf("[-] no process found\n");
        return;
    }
    
    if (is_process_block(process_list_block, pid)) {
        PCB *p = process_list_runnning;

        s = find_process(process_list_block, pid);
        s->next->state = process_type_running;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = s->next;
        s->next = s->next->next;
        p->next->next = NULL;
        *size = *size + 1;
        printf("[+] success\n");
    }else{
        printf("[+] process not found\n");
    }
}

int is_process_running(PCB *process_list_runnning, size_t pid)
{
    int flag = 0;
    PCB *tmp = process_list_runnning->next;

    while (tmp != NULL) {
        if (tmp->pid == pid) {
            flag = 1;
            break;
        }
        tmp = tmp->next;
    }
    return flag;
}

int is_process_block(PCB *process_list_block, size_t pid)
{
    int flag = 0;
    PCB *s = process_list_block->next;
    while (s != NULL) {
        if (s->pid == pid) {
            // found
            flag = 1;
            break;
        }
        // point to next node
        s = s->next;
    }
    return flag;
}

PCB *find_process(PCB *list, size_t pid)
{
    PCB *s = list;
    while (s->next != NULL) {
        // found
        if (s->next->pid == pid) {
            return s;
        }
        s = s->next;
    }
    // not found
    return NULL;
}
