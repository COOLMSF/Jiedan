#ifndef WORD_H
#define WORD_H
#include <QString>

struct Wd       //定义单词信息结构体
{
    QString EN;
    QString Attr;
    QString CN;

    Wd() {};

    Wd(QString &E, QString &A, QString &C)
    {
        EN = E;
        Attr = A;
        CN = C;
    }
};

struct NodeWd       //定义用于单词链表的结构体
{
    Wd info;
    NodeWd *next;

    NodeWd(Wd word, NodeWd *n = nullptr)        //不允许使用隐式转换
    {
        info = std::move(word);
        next = n;
    }
};

NodeWd *loadLib(QString filePath,int *total);

void saveLib(NodeWd *head, QString filePath);
void saveErrorWord(unsigned int id,Wd wd);
void deleteErrorWord(unsigned int id,Wd wd);
#endif // WORD_H
