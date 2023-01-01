#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "person.h"

#define MAX_PERSON 100

int g_c = 0;
// 对象数组，存储所有人员信息
struct Person *person_arr[MAX_PERSON];

void welcome_menu()
{
    puts("1）录入信息");
    puts("2）进行核酸检测");
    puts("3）输出同试管的人员");
};

void add_person(queue *queue) 
{
    struct Person *p = malloc(sizeof(struct Person));
    if (!p) {
        perror("malloc");
        exit(-1);
    }
    printf("请输入ID:");
    scanf("%d", &p->id);
    printf("请输入身份证号:");
    scanf("%s", p->id_num);
    printf("请输入姓名:");
    scanf("%s", p->name);
    printf("信息添加成功");
    queue_push_data(queue, p);
    person_arr[g_c++] = p;

    //并提示前面有多少人和等待时间
    int n_num = queue->length - 1;
    int n_min = (queue->length - 1) * 1;
    if (n_num == 0) {
        printf("前面没有人，无需等待\n");
    } else {
        printf("前面一共有%d个人，需要等待%d分钟\n",  n_num, n_min);
    }
};

void start_check(queue *queue)
{
    if (queue->length == 0) {
        printf("还没有人进行排队，无法进行检测");
        return;
    }

    struct Person *p = (struct Person *)queue_pull_data(queue);
    printf("当前%s正在进行和酸检测\n", p->name);
};

void get_same_tube_person()
{
    if (g_c == 0) {
        printf("目前还没信息\n");
        return;
    }
    printf("以下为同试管人员\n");
    for (int i = 0; i < MAX_PERSON; i+=9) {
        for (int j = 0; j < 10; j++) {
            int tmp = i * 10 + j;
            if (tmp >= g_c) {
                break;
            }
            printf("%s\n", person_arr[i*10+j]->name);
        }
    }
};

int main() {
    // 创建队列
    queue *queue = queue_create();
    puts("欢迎使用核酸检测系统");

    while (1) {
        welcome_menu();

        int input;
        puts("输入你的选项:");
        int ret = scanf("%d", &input);
        if (ret != 1) {
            printf("您的输入有误，请重新输入!");
            continue;
        }

        if (input == 1) {
            add_person(queue);
        } else if (input == 2) {
            start_check(queue);
        } else if (input == 3) {
            get_same_tube_person();
        } else {
            printf("您的输入有误，请重新输入!");
            continue;
        }
    }
    /* 释放队列中节点 */
    queue_empty(queue);
    /* 释放队列 */
    queue_release(queue);
    
    return 0;
}