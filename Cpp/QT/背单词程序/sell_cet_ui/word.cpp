#include "word.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
NodeWd *loadLib(QString filePath,int *total)
{
    NodeWd *head = nullptr;
    QFile file(filePath);
    if(!file.exists())
    {
        file.open(QIODevice::WriteOnly);
        file.close();
    }
    file.open(QIODevice::ReadOnly);
    QByteArray fileArray = file.readAll();
    QList<QByteArray> fileList = fileArray.split(';');
    *total = fileList.size()/3;
    if (*total==0) return nullptr;
    Wd wd;
    for(int i = (*total)*3-1 ;i >= 0;)
    {
        wd.CN = fileList.at(i--);
        wd.Attr = fileList.at(i--);
        wd.EN = fileList.at(i--);

        head = new NodeWd(wd,head);
    }
    file.close();
    return head;
}

void saveLib(NodeWd *head, QString filePath)
{
    QFile file(filePath);
    file.open(QIODevice::WriteOnly|QIODevice::Text);       //用于写入文件
    NodeWd *tp;
    QTextStream outfile(&file);
    while (head != nullptr)
    {
        QString wds = QString("%1;%2;%3;").arg(head->info.EN).arg(head->info.Attr).arg(head->info.CN); //将词条整理为存储标准格式
//        qDebug() << wds;
        outfile << wds;
        tp = head;
        head = head->next;
        delete tp;
    }
    file.close();
}

void saveErrorWord(unsigned int id,Wd wd)
{
    int total;
    QString filePath = QString("./src/lib/R_%1.dat").arg(QString::number(id));
    NodeWd* head = loadLib(filePath,&total);
    NodeWd * tp = head;bool added = false;
    while(tp != nullptr)
    {
        if(wd.EN == tp->info.EN)
        {
            added = true;
//            QMessageBox::warning(this,"错误","你想添加的单词已经存在");
            break;
        }
        tp = tp->next;
    }
    if(!added)
    {
        head = new NodeWd(wd,head);
    }
    saveLib(head,filePath);
}

void deleteErrorWord(unsigned int id,Wd wd)
{
    int total;
    QString filePath = QString("./src/lib/R_%1.dat").arg(QString::number(id));
    NodeWd* head = loadLib(filePath,&total);
    NodeWd *tp = head;
    NodeWd *tp1 = nullptr;
    NodeWd *del = nullptr;
    bool isFirst = true;//判断要删除的单词是否是头指针指向的节点

    while (tp != nullptr)
    {
        if (tp->info.EN == wd.EN)
        {
            del = tp;
            if (isFirst)
            {
                head = tp->next;        //将要删除的节点的尾指针赋值给头指针
                del->next = nullptr;
                delete tp;
                break;
            }
            else
            {
                tp1->next = tp->next;       //将尾指针赋值给第三变量
                del->next = nullptr;
                delete del;
                break;
            }
        }
        isFirst = false;
        tp1 = tp;
        tp = tp->next;  //下移，实现遍历
    }
    saveLib(head,filePath);
}
