#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "person.h"

#define MAX_PERSON 100

int g_c = 0;
// �������飬�洢������Ա��Ϣ
struct Person *person_arr[MAX_PERSON];

void welcome_menu()
{
    puts("1��¼����Ϣ");
    puts("2�����к�����");
    puts("3�����ͬ�Թܵ���Ա");
};

void add_person(queue *queue) 
{
    struct Person *p = malloc(sizeof(struct Person));
    if (!p) {
        perror("malloc");
        exit(-1);
    }
    printf("������ID:");
    scanf("%d", &p->id);
    printf("���������֤��:");
    scanf("%s", p->id_num);
    printf("����������:");
    scanf("%s", p->name);
    printf("��Ϣ��ӳɹ�");
    queue_push_data(queue, p);
    person_arr[g_c++] = p;

    //����ʾǰ���ж����˺͵ȴ�ʱ��
    int n_num = queue->length - 1;
    int n_min = (queue->length - 1) * 1;
    if (n_num == 0) {
        printf("ǰ��û���ˣ�����ȴ�\n");
    } else {
        printf("ǰ��һ����%d���ˣ���Ҫ�ȴ�%d����\n",  n_num, n_min);
    }
};

void start_check(queue *queue)
{
    if (queue->length == 0) {
        printf("��û���˽����Ŷӣ��޷����м��");
        return;
    }

    struct Person *p = (struct Person *)queue_pull_data(queue);
    printf("��ǰ%s���ڽ��к�����\n", p->name);
};

void get_same_tube_person()
{
    if (g_c == 0) {
        printf("Ŀǰ��û��Ϣ\n");
        return;
    }
    printf("����Ϊͬ�Թ���Ա\n");
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
    // ��������
    queue *queue = queue_create();
    puts("��ӭʹ�ú�����ϵͳ");

    while (1) {
        welcome_menu();

        int input;
        puts("�������ѡ��:");
        int ret = scanf("%d", &input);
        if (ret != 1) {
            printf("����������������������!");
            continue;
        }

        if (input == 1) {
            add_person(queue);
        } else if (input == 2) {
            start_check(queue);
        } else if (input == 3) {
            get_same_tube_person();
        } else {
            printf("����������������������!");
            continue;
        }
    }
    /* �ͷŶ����нڵ� */
    queue_empty(queue);
    /* �ͷŶ��� */
    queue_release(queue);
    
    return 0;
}