#include "viewlib.h"
#include "ui_viewlib.h"
#include <QFile>
#include <QMessageBox>
#include "addword.h"

viewLib::viewLib(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::viewLib)
{
    ui->setupUi(this);
//    ui->defaultL->setChecked(true);
    this->adw = new Addword(this);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(ui->defaultL,&QRadioButton::clicked,[=]()
    {
        ui->tableWidget->clearContents();
//        QFile file("./src/lib/defaultWordLib.dat");
//        file.open(QIODevice::ReadOnly);
        int total;
        NodeWd* hd = loadLib("./src/lib/defaultWordLib.dat",&total);
        NodeWd * head = hd;
        ui->tableWidget->setRowCount(total);
        for(int i = 0;i < total;i++)
        {
            int col=0;
            ui->tableWidget->setItem(i,col++,new QTableWidgetItem(head->info.EN));
            ui->tableWidget->setItem(i,col++,new QTableWidgetItem(head->info.Attr));
            ui->tableWidget->setItem(i,col++,new QTableWidgetItem(head->info.CN));
            head = head->next;
        }
        ui->label->setText("系统词库");
        saveLib(hd,"./src/lib/defaultWordLib.dat");
//        file.close();
    });

    connect(ui->personalL,&QRadioButton::clicked,this,[=](){
        if(current->Id == 0)
        {
            QMessageBox::warning(this,"错误","您未登录，请登陆后重试。");
            ui->defaultL->setChecked(true);
        }
        else
        {
            ui->tableWidget->clearContents();
            int total;
            QString filePath = QString("./src/lib/L_%1.dat").arg(current->Id);
            NodeWd* hd = loadLib(filePath,&total);
            NodeWd * head = hd;
            ui->tableWidget->setRowCount(total);
            for(int i = 0;i < total;i++)
            {
                int col=0;
                ui->tableWidget->setItem(i,col++,new QTableWidgetItem(head->info.EN));
                ui->tableWidget->setItem(i,col++,new QTableWidgetItem(head->info.Attr));
                ui->tableWidget->setItem(i,col++,new QTableWidgetItem(head->info.CN));
                head = head->next;
            }
            QString name = QString("%1的个人词库").arg(current->UserName);
            ui->label->setText(name);
            saveLib(hd,filePath);
        }
    });

    connect(ui->clearBtn,&QPushButton::clicked,ui->tableWidget,&QTableWidget::clearContents);

    connect(ui->wrongL,&QRadioButton::clicked,[=](){
        if(current->Id == 0)
        {
            QMessageBox::warning(this,"错误","您未登录，请登陆后重试。");
            ui->defaultL->setChecked(true);
        }
        else
        {
            ui->tableWidget->clearContents();
            int total;
            QString filePath = QString("./src/lib/R_%1.dat").arg(current->Id);
            NodeWd* hd = loadLib(filePath,&total);
            NodeWd * head = hd;
            ui->tableWidget->setRowCount(total);
            for(int i = 0;i < total;i++)
            {
                int col=0;
                ui->tableWidget->setItem(i,col++,new QTableWidgetItem(head->info.EN));
                ui->tableWidget->setItem(i,col++,new QTableWidgetItem(head->info.Attr));
                ui->tableWidget->setItem(i,col++,new QTableWidgetItem(head->info.CN));
                head = head->next;
            }
            QString name = QString("%1的错题库").arg(current->UserName);
            ui->label->setText(name);
            saveLib(hd,filePath);
        }
    });

    connect(ui->AddBtn,&QPushButton::clicked,[=](){
        if(ui->defaultL->isChecked())
        {
            QMessageBox::information(this,"抱歉","系统词库不允许添加");
        }
        else
        {

            this->adw->setMode(0);
            this->adw->show();
        }
    });

    connect(ui->ModifyBtn,&QPushButton::clicked,[=](){
        if(ui->defaultL->isChecked())
        {
            QMessageBox::information(this,"抱歉","系统词库不允许修改");
        }
        else {
            QList<QTableWidgetItem *> SelList = ui->tableWidget->selectedItems();
            if(SelList.size() !=3)
            {
                QMessageBox::warning(this,"警告","每次有且只有一个单词可以修改");
            }
            else
            {
                Wd wd;
                wd.EN = SelList[0]->text();
                wd.CN = SelList[2]->text();
                wd.Attr = SelList[1]->text();
                this->adw->withWordsModify(wd);
                this->adw->setMode(1);
                this->adw->show();
            }
        }
    });

    connect(ui->deleteBtn,&QPushButton::clicked,[=](){
        if(ui->defaultL->isChecked())
        {
            QMessageBox::information(this,"抱歉","系统词库不允许删除");
        }
        else
        {
            QList<QTableWidgetItem *> SelList = ui->tableWidget->selectedItems();
            if(SelList.size() == 0)
            {
                QMessageBox::information(this,"提示","请选择你要删除的单词");
            }
            else
            {
                int total;
                QString filePath;
                if(ui->personalL->isChecked())
                {
                    filePath = QString("./src/lib/L_%1.dat").arg(current->Id);
                } else if(ui->wrongL->isChecked())
                {
                    filePath = QString("./src/lib/R_%1.dat").arg(current->Id);
                }
                QString wrn = QString("你确定要删除 %1 个单词吗？该操作将无法撤销").arg(QString::number(SelList.size()/3));
                if(QMessageBox::Ok == QMessageBox::warning(this,"确认",wrn,QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Cancel))
                {
                    qDebug() << SelList.size();
                    NodeWd *head = loadLib(filePath, &total);
                    Wd wd;
                    int count = 0;
                    for(int i = 0;i<SelList.size()/3;i++)
                    {
                        NodeWd *tp = head;
                        NodeWd *tp1 = nullptr;
                        NodeWd *del = nullptr;
                        bool isFirst = true;//判断要删除的单词是否是头指针指向的节点

                        wd.EN = SelList[count++]->text();
                        wd.Attr = SelList[count++]->text();
                        wd.CN = SelList[count++]->text();
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
                            tp = tp->next;      //下移，实现遍历
                        }
                    }

                    saveLib(head, filePath);
                }
                if(ui->personalL->isChecked())
                {
                    ui->personalL->click();
                } else if(ui->wrongL->isChecked())
                {
                    ui->wrongL->click();
                }
            }
        }
    });

    connect(this->adw,&Addword::confirmadd,[=](Wd wd){
        int total;
        QString filePath;
        if(ui->personalL->isChecked())
        {
            filePath = QString("./src/lib/L_%1.dat").arg(current->Id);
        } else if(ui->wrongL->isChecked())
        {
            filePath = QString("./src/lib/R_%1.dat").arg(current->Id);
        }
        NodeWd* head = loadLib(filePath,&total);
        NodeWd * tp = head;bool added = false;
        while(tp != nullptr)
        {
            if(wd.EN == tp->info.EN)
            {
                added = true;
                QMessageBox::warning(this,"错误","你想添加的单词已经存在");
                break;
            }
            tp = tp->next;
        }
        if(!added)
        {
            head = new NodeWd(wd,head);
        }
        saveLib(head,filePath);
        qDebug() << "end add";
        if(ui->personalL->isChecked())
        {
            ui->personalL->click();
        } else if(ui->wrongL->isChecked())
        {
            ui->wrongL->click();
        }
    });

    connect(this->adw,&Addword::confirmModify,[=](Wd wd){
        int total;
        QString filePath;
        if(ui->personalL->isChecked())
        {
            filePath = QString("./src/lib/L_%1.dat").arg(current->Id);
        } else if(ui->wrongL->isChecked())
        {
            filePath = QString("./src/lib/R_%1.dat").arg(current->Id);
        }
        NodeWd* head = loadLib(filePath,&total);
        NodeWd * tp = head;
        while(tp != nullptr)
        {
            if(wd.EN == tp->info.EN)
            {
                tp->info.CN = wd.CN;
                tp->info.Attr = wd.Attr;
                break;
            }
            tp = tp->next;
        }
        saveLib(head,filePath);
        if(ui->personalL->isChecked())
        {
            ui->personalL->click();
        } else if(ui->wrongL->isChecked())
        {
            ui->wrongL->click();
        }
    });
}

viewLib::~viewLib()
{
    delete ui;
}

void viewLib::transferCurrent(currentDTO* current,int status)
{
    this->current = current;
    if(status == 1)
    {
        ui->label->setText("选择单词本学习");
    }
}

void viewLib::closeEvent(QCloseEvent *)
{
    ui->tableWidget->clearContents();
}
