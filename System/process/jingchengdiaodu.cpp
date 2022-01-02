#include <stdio.h>
#include <stdlib.h>
#define getpch(type) (type *)malloc(sizeof(type))

struct pcb {
    char name[10];
    char state;
    int super;
    int ntime;
    int rtime;
    struct pcb *link;
} *ready = NULL, *p;

typedef struct pcb PCB;

void sort()
{
    PCB *first, *second;
    int insert = 0;

    if ((ready == NULL) || ((p->super) > (ready->super))) {
        p->link = ready;
        ready = p;
    } else {
        first = ready;
        second = first->link;

        while (second != NULL) {
            if ((p->super) > (second->super)) {
                p->link = second;
                first->link = p;
                second = NULL;
                insert = 1;
            } else {
                first = first->link;
                second = second->link;
            }
        }
        if (insert == 0)
            first->link = p;
    }
}

void input()
{
    int i, num;
    
    printf("\n请输入进程号?");
    scanf("%d", &num);

    for (i = 0; i < num; i++) {
        printf("\n进程号No.%d:\n", i);
        p = getpch(PCB);
        printf("\n输入进程名:");
        scanf("%s", p->name);
        printf("\n输入进程优先级:");
        scanf("%d", &p->super);
        printf("\n输入进程运行时间:");
        scanf("%d", &p->ntime);
        printf("\n");

        p->rtime = 0;
        p->state = 'w';
        p->link = NULL;

        sort();
    }
}

int space()
{
    int l = 0;
    PCB *pr = ready;

    while (pr != NULL) {
        l++;
        pr = pr->link;
    }
    return l;
}

void disp(PCB *pr)
{
    printf("\n qname\tstate\tsuper\tndtime\truntime\n");
    printf("|%s\t", pr->name);
    printf("|%c\t", pr->state);
    printf("|%d\t", pr->super);
    printf("|%d\t", pr->ntime);
    printf("|%d\t", pr->rtime);
    printf("\n");
}

void check()
{
    PCB *pr;

    printf("\n **** 当前正在运行的进程是:%s", p->name);
    disp(p);
    pr = ready;
    printf("\n **** 当前就绪队列状态为:\n");

    while (pr != NULL) {
        disp(pr);
        pr = pr->link;
    }
}

void destory()
{
    printf("\n 进程 [%s] 已完成\n", p->name);
    free(p);
}

void running()
{
    (p->rtime)++;
    if (p->rtime == p->ntime) {
        destory();
    } else {
        (p->super)--;
        p->state = 'w';
        sort();
    }
}

int main(int argc, char const* argv[])
{
    int len, h = 0;
    char ch;

    input();
    len = space();

    while (len != 0 && ready != NULL) {
        ch = getchar();
        h++;
        printf("\n The execute number:%d\n", h);
        p = ready;
        ready = p->link;
        p->link = NULL;
        p->state = 'R';
        check();
        running();
        printf("\n 按任意键继续");
        ch = getchar();
    }

    printf("\n\n进程已完成");
}
