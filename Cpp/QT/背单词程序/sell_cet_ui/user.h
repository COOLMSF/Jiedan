#ifndef USER_H
#define USER_H
#include <QString>

struct User     //定义用户类
{
    QString userName;
    QString password;
    unsigned int userId;
    unsigned int level;
    unsigned int score;
    int lastSignTime;

    User() {};
};

struct Node     //定义用于链表节点的结构体
{
    User info;
    Node *next;

    explicit Node(User user, Node *nextN = nullptr)     //不允许使用隐式转换
    {
        info = user;
        next = nextN;
    }
};

Node *read(int *userCount);

void save(Node * head);

#endif // USER_H
