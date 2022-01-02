//
//  main.c
//  ProcessControlTest
//
//  Created by Apple on 2019/10/13.
//  Copyright © 2019 Yao YongXin. All rights reserved.
//

#include "ProcessControl.h"

void showLine(){
    printf("**************************\n");
}

int main(int argc, const char * argv[]) {
    
    //运行(就绪)队列(头结点不储存信息)
    PCB *running_list = (PCB *)malloc(sizeof(PCB));
    running_list->next = NULL;
    
    //阻塞队列(头结点不储存信息)
    PCB *block_list = (PCB *)malloc(sizeof(PCB));
    block_list->next = NULL;
    
    //当前运行的线程数量
    int storage_number = 0;
    
    int choose = 1;
    while (choose) {
        //展示菜单
        showLine();
        printf("*     进程演示系统      *\n");
        showLine();
        printf("1.创建新的进程  2.查看运行进程\n");
        printf("3.换出某个进程  4.杀死运行进程\n");
        printf("5.唤醒某个进程  6.退出程序   \n");
        showLine();
             
        printf("请选择(1~6):\n");
        scanf("%d",&choose);
             
        switch (choose) {
            case 1:
                //创建新的进程
                create(running_list, block_list, &storage_number);
                break;
            case 2:
                //查看运行进程
                show_running(running_list);
                break;
            case 3:
                //换出某个进程
                change(running_list, block_list, &storage_number);
                break;
            case 4:
                //杀死运行进程
                killed(running_list, &storage_number);
                break;
            case 5:
                //唤醒某个进程
                wake_up(running_list, block_list, &storage_number);
                break;
            case 6:
                return 0;
            default:
                printf("没有这个选项!\n");
                break;
        }
             
    }
      
    return 0;
}
