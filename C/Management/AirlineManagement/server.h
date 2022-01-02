//
// Created by Coolder Coolder on 2021/10/9.
//

#include "list.h"

#ifndef PRO_SERVER_H
#define PRO_SERVER_H

#endif //PRO_SERVER_H

char sendbuf[1024];
struct list_node *head = NULL;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

//乘客信息结构体
struct Ordinary_passenger
{
    char name[20];
    char id[20];
    int age;
    char phone_number[20];
    char passwd[8];
    char pay_passwd[8];
    char question[20];
    char answer[20];
    int balance;
    int vip;
    int integral;


};

struct OrdinaryPassNode
{
    struct Ordinary_passenger info;
    struct list_head Ordinary_passenger_list;
};

//登录链表节点
struct login_user{

    int connfd;
    char name[50];
    struct list_head login_user_list;
};

struct list_node{

    struct OrdinaryPassNode *Ordinary_passenger_list_head;
    struct flight_num_pas_node *flight_num_list_head;
    struct Verified_identity_pas_node *Verified_identity_list_head;
    struct buy_ticket_node *buy_ticket_list_head;
    struct admin_node *admin_list_head;
    struct admin_node *admin_login_in_list_head;
    struct flight_num_pas_node *rm_flight_num_list_head;
    struct login_user *login_user_list_head;
    char user_name[30];
    int connfd;  //数据域
    struct list_head list; //指针域
};

struct list_node *init_list_head()
{
    //1. 为头节点申请空间。
    head = malloc(sizeof(struct list_node));
    if(head == NULL)
        printf("malloc head error!\n");

    //2. 为指针域赋值。
    INIT_LIST_HEAD(&(head->list));

    return head;
}

