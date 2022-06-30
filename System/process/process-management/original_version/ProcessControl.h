//
//  ProcessControl.h
//  ProcessControlTest
//
//  Created by Apple on 2019/10/13.
//  Copyright © 2019 Yao YongXin. All rights reserved.
//

#ifndef ProcessControl_h
#define ProcessControl_h

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//最大内存的大小
#define MAX_SIZE 20

//线程状态：运行(就绪)  阻塞
enum process_type{
    process_type_running = 1000,
    process_type_block = -1000,
    process_type_ready = 500
};

//进程控制块结构体
typedef struct PCB_Type{
    //进程的id
    int pid;
    //进程的优先级
    int priority;
    //进程大小（执行时间）
    int size;
    //进程内容
    char content[20];
    //进程的状态  执行  阻塞
    int state;
    //下一个要执行的进程
    struct PCB_Type *next;
}PCB;

//创建新的进程
void create(PCB *running_list,PCB *block_list,int *size);
//查看运行进程
void show_running(PCB *running_list);
//换出某个进程
void change(PCB *running_list,PCB *block_list,int *size);
//杀死运行进程
void killed(PCB *running_list,int *size);
//唤醒某个进程
void wake_up(PCB *running_list,PCB *block_list,int *size);

//判断在运行(就绪)队列中是否存在有该pid值的进程 0->不存在 1->存在
int exist_in_running(PCB *running_list,int pid);
//判断在阻塞队列中是否存在有该pid值的进程 0->不存在 1->存在
int exist_in_block(PCB *block_list,int pid);
//通过pid寻找进程的位置(返回其前一个结点的地址
PCB *find(PCB *list,int pid);

#endif /* ProcessControl_h */
