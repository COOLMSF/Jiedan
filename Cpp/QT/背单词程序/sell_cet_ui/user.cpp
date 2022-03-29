#include "user.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QFileDialog>
#include <QDir>

Node *read(int *userCount)
{
    Node *head = nullptr;
    qDebug() << QDir::currentPath();
    QFile file("./src/user.dat");
    if(!file.exists())
    {
        file.open(QIODevice::WriteOnly);
        file.close();
    }
    file.open(QIODevice::ReadOnly|QIODevice::Text);     //以读方式打开文件
    *userCount = 0;
    qDebug() << "success";
    if(!file.isOpen())
    {
        qDebug() << "can't open";
        return nullptr;
    }
//    QTextStream infile(&file);
    User tuser;
//    Node* tp;
    while(!file.atEnd())
    {
        tuser.userId = file.readLine().toUInt();
            qDebug() << tuser.userId;
        tuser.userName=file.readLine().trimmed();
            qDebug() << tuser.userName;
            tuser.password= file.readLine().trimmed();
        qDebug() << tuser.password;
        tuser.level = file.readLine().toUInt();
            qDebug() << tuser.level;
        tuser.score= file.readLine().toUInt();
            qDebug() << tuser.score;
        tuser.lastSignTime= file.readLine().toInt();
            qDebug() << tuser.lastSignTime;
//        tp = (Node *) malloc(sizeof(Node)); //分配动态内存
//        tp->info = tuser;
//        tp->next = head;
//        tp = head;
            head = new Node(tuser,head);
        (*userCount)++;     //计数器自增
    }
    qDebug() << *userCount;
    file.close();
    return head;        //返回链表指针
}

void save(Node * head)
{

    QFile file("./src/user.dat");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    Node * tp;
    QTextStream outfile(&file);
    while (head != nullptr)     //将用户信息存入文件
    {
        outfile << head->info.userId << "\n";
        outfile << head->info.userName << "\n";
        outfile << head->info.password << "\n";
        outfile << head->info.level << "\n";
        outfile << head->info.score << "\n";
        outfile << head->info.lastSignTime << "\n";
        tp = head;
        head = head->next;      //指针指向下一个节点
        delete tp;      //释放指针
    }
    file.close();
}
