#include <stdio.h>
#include <stdlib.h>
#include "ProcessManagement.h"

int main(int argc, const char * argv[]) 
{
    size_t cnt = 0;
    int choose = 1;

    PCB *running_list = (PCB *)malloc(sizeof(PCB));
    if (running_list == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    PCB *block_list = (PCB *)malloc(sizeof(PCB));
    if (running_list == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    running_list->next = NULL;
    block_list->next = NULL;

    while (choose) {
        fprintf(stdout, "1.create process\n");
        fprintf(stdout, "2.kill process\n");
        fprintf(stdout, "3.swap process\n");
        fprintf(stdout, "4.show process\n");
        fprintf(stdout, "5.wakeup process\n");
        fprintf(stdout, "6.exit\n");
             
        printf("input:\n");
        scanf("%d",&choose);
             
        switch (choose) {
            case 1:
                create_process(running_list, block_list, &cnt);
                break;
            case 2:
                kill_process(running_list, &cnt);
                break;
            case 3:
                change_process(running_list, block_list, &cnt);
                break;
            case 4:
                show_running_process(running_list);
                break;
            case 5:
                wake_up_process(running_list, block_list, &cnt);
                break;
            case 6:
                exit(EXIT_SUCCESS);
            default:
                printf("input error\n");
                break;
        }
    }
    return 0;
}
