#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#define MAX_SIZE 30
typedef int ReturnStatus;
#define getpch(type) (type *)malloc(sizeof(type))

typedef struct PCB_Type{
    int pid;
    int priority;
    int cnt;
    char content[20];
    int state;
    //下一个要执行的进程
    struct PCB_Type *next;
} PCB;

enum ProcessTypeValue{
    RUNNING_STATE = 1000,
    BLOCKING_STATE = -1000,
    READYING_STATE = 500
};
PCB *FindProcess(PCB *list,int pid);
ReturnStatus MakeProcess(PCB *LinkedListRunningList,
PCB *LinkedListBlockingList,int *cnt);
ReturnStatus ListRunProcess(PCB *LinkedListRunningList);
ReturnStatus SwapOutProcess(PCB *LinkedListRunningList,
PCB *LinkedListBlockingList,int *cnt);
ReturnStatus KillProcess(PCB *LinkedListRunningList,int *cnt);
ReturnStatus WakeUpProcess(PCB *LinkedListRunningList,
PCB *LinkedListBlockingList,int *cnt);
ReturnStatus IsProcessRunning(PCB *LinkedListRunningList,int pid);
ReturnStatus IsProcessBlock(PCB *LinkedListBlockingList,int pid);

void sort()
{
    // PCB *first, *second;
    // int insert = 0;
}

PCB *FindProcess(PCB *list,int pid)
{
    PCB *s = list;
    
    while (s->next) 
    {
        if (s->next->pid == pid) {
            return s;
        }
        s = s->next;
    }
    return NULL;
}

ReturnStatus MakeProcess(PCB *LinkedListRunningList,
PCB *LinkedListBlockingList,int *cnt)
{
    PCB *s = LinkedListRunningList;
    if (*cnt >= MAX_SIZE) 
    {
        printf("内存不足\n");
        return -1;
    }
    PCB *p = (PCB *)malloc(sizeof(PCB));
    assert(p != NULL);
    
    int pid;
    printf("pid:\n");
    scanf("%d",&pid);
    
    if (IsProcessRunning(LinkedListRunningList, pid)) 
    {
        printf("该值已存在\n");
        return -1;
    }
    if (IsProcessBlock(LinkedListBlockingList, pid)) 
    {
        printf("该值已存在!\n");
        return -1;
    }
    //没重复，保存
    p->pid = pid;
    
    printf("优先级:\n");
    scanf("%d",&p->priority);
    printf("大小:\n");
    scanf("%d",&p->cnt);
    printf("内容:\n");
    scanf("%s",p->content);
    p->state = RUNNING_STATE;
    p->next = NULL;
    
    while (s->next != NULL) 
    {
        s = s->next;
    }
    s->next = p;
    *cnt = *cnt + 1;
}

ReturnStatus ListRunProcess(PCB *LinkedListRunningList)
{
    PCB *s = LinkedListRunningList->next;
    if (s == NULL) 
    {
        printf("没有正在运行的进程\n");
        return -1;
    }
    
    while (s != NULL) 
    {
        printf("进程id:%d\n",s->pid);
        printf("进程优先级:%d\n",s->priority);
        printf("进程大小:%d\n",s->cnt);
        printf("进程内容:%s\n",s->content);
        s = s->next;
    }
}

//换出某个进程
ReturnStatus SwapOutProcess(PCB *LinkedListRunningList,
PCB *LinkedListBlockingList,int *cnt)
{
    if (*cnt == 0) {
        printf("无可换出的进程\n");
        return -1;
    }
    
    int pid;
    printf("请输入需要换出进程的id:\n");
    scanf("%d",&pid);
    if (IsProcessRunning(LinkedListRunningList, pid)) {
        PCB *s = FindProcess(LinkedListRunningList, pid);
        s->next->state = BLOCKING_STATE;
        //将该线程存入阻塞队列中
        PCB *p = LinkedListBlockingList;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = s->next;
        s->next = s->next->next;
        p->next->next = NULL;
        
        *cnt = *cnt - 1;
        printf("交换成功\n");
    }else{
        printf("处于阻塞状态\n");
    }
}

ReturnStatus KillProcess(PCB *LinkedListRunningList,int *cnt)
{
    if (*cnt == 0) {
        printf("无可杀死的进程\n");
        return -1;
    }
    
    int pid;
    printf("输入要杀死的进程id:\n");
    scanf("%d",&pid);
    if (IsProcessRunning(LinkedListRunningList, pid)) {
        PCB *s = FindProcess(LinkedListRunningList, pid);
        PCB *thisThread = s->next;
        *cnt = *cnt - 1;
        s->next = s->next->next;
        free(thisThread);
        printf("成功杀死\n");
    }
    else
    {
        printf("该线程不存在或已处于阻塞状态\n");
    }
}

ReturnStatus WakeUpProcess(PCB *LinkedListRunningList,
PCB *LinkedListBlockingList,int *cnt)
{
    PCB *s = LinkedListBlockingList;
    int pid;
    printf("请输入要唤醒的进程id:\n");
    scanf("%d",&pid);
    if (s->next == NULL) {
        printf("没有可唤醒的线程\n");
        return -1;
    }
    
    if (IsProcessBlock(LinkedListBlockingList, pid)) {
        s = FindProcess(LinkedListBlockingList, pid);
        s->next->state = RUNNING_STATE;
        PCB *p = LinkedListRunningList;
        while (p->next != NULL) 
            p = p->next;
        p->next = s->next;
        s->next = s->next->next;
        p->next->next = NULL;
        *cnt = *cnt + 1;
        printf("唤醒成功\n");
    }else{
        printf("该线程不存在\n");
    }
}

ReturnStatus IsProcessRunning(PCB *LinkedListRunningList,int pid){
    int result = 0;
    PCB *s = LinkedListRunningList->next;
    while (s != NULL) 
    {
        if (s->pid == pid) {
            //存在，直接返回
            result = 1;
            break;
        }
        s = s->next;
    }
    return result;
}

ReturnStatus IsProcessBlock(PCB *LinkedListBlockingList,int pid)
{
    int result = 0;
    PCB *s = LinkedListBlockingList->next;
    while (s != NULL)
     
    {
        if (s->pid == pid) {
            result = 1;
            break;
        }
        s = s->next;
    }
    
    return result;
}

int main() 
{
    int StorageNumber = 0;
    int Input = 1;
    PCB *LinkedListRunningList = (PCB *)malloc(sizeof(PCB));
    PCB *LinkedListBlockList = (PCB *)malloc(sizeof(PCB));
    if (!LinkedListRunningList || !LinkedListBlockList)
    {
        puts("内存分配出错");
        exit(1);
    }
    // 初始化
    LinkedListBlockList->next = NULL;
    LinkedListRunningList->next = NULL;
    
    while (true) 
    {
        puts("");
        printf("1.创建新的进程  2.查看运行进程\n");
        printf("3.换出某个进程  4.杀死运行进程\n");
        printf("5.唤醒某个进程  6.退出程序   \n");
        printf("输入(1-6):\n");
        scanf("%d",&Input);
        
        if (Input == 1) 
        {
            MakeProcess(LinkedListRunningList, LinkedListBlockList, &StorageNumber);
        }
        else if (Input == 2) 
        {
            ListRunProcess(LinkedListRunningList);
        }
        else if (Input == 3) 
        {
            SwapOutProcess(LinkedListRunningList, LinkedListBlockList, &StorageNumber);
        }
        else if (Input == 4) 
        {
            KillProcess(LinkedListRunningList, &StorageNumber);
        }
        else if (Input == 5) 
        {
            WakeUpProcess(LinkedListRunningList, LinkedListBlockList, &StorageNumber);
        }
        else 
        {
            fprintf(stderr, "没有这个选择项");
        }
    }
}
