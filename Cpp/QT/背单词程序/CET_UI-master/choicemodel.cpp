#include "choicemodel.h"
#include "ui_choicemodel.h"

Choicemodel::Choicemodel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Choicemodel)
{
    ui->setupUi(this);
    ui->checkBtn->setText("确定");
    connect(ui->BtnA,&QRadioButton::clicked,[=](){
        ui->checkBtn->setText("A");
    });
    connect(ui->BtnB,&QRadioButton::clicked,[=](){
        ui->checkBtn->setText("B");
    });
    connect(ui->BtnC,&QRadioButton::clicked,[=](){
        ui->checkBtn->setText("C");
    });
    connect(ui->BtnD,&QRadioButton::clicked,[=](){
        ui->checkBtn->setText("D");
    });

    connect(ui->checkBtn,&QPushButton::clicked,[=]()
    {
        if(ui->checkBtn->text()=="A") emit choose(0);
        if(ui->checkBtn->text()=="B") emit choose(1);
        if(ui->checkBtn->text()=="C") emit choose(2);
        if(ui->checkBtn->text()=="D") emit choose(3);
    });
}

Choicemodel::~Choicemodel()
{
    delete ui;
}

void Choicemodel::setQuest(Wd wd,int ans)
{
    ui->EnLabel->setText(wd.EN);
    ui->AttrLabel->setText(wd.Attr);
    qDebug() << "4";
    int total,temp;
    NodeWd * head = loadLib("./src/lib/defaultWordLib.dat",&total);
    NodeWd * tp;
    if(ans ==0)
    {
        ui->BtnA->setText(wd.CN);
    }
    else
    {
        tp = head;
        temp = QRandomGenerator::global()->bounded(0,total);
        for(int i = 0;i<temp;i++)
        {
            tp = tp->next;
        }
        ui->BtnA->setText(tp->info.CN);
    }
    if(ans ==1)
    {
        ui->BtnB->setText(wd.CN);
    }
    else
    {
        tp = head;
        temp = QRandomGenerator::global()->bounded(0,total);
        for(int i = 0;i<temp;i++)
        {
            tp = tp->next;
        }
        ui->BtnB->setText(tp->info.CN);
    }
    if(ans ==2)
    {
        ui->BtnC->setText(wd.CN);
    }
    else
    {
        tp = head;
        temp = QRandomGenerator::global()->bounded(0,total);
        for(int i = 0;i<temp;i++)
        {
            tp = tp->next;
        }
        ui->BtnC->setText(tp->info.CN);
    }
    if(ans ==3)
    {
        ui->BtnD->setText(wd.CN);
    }
    else
    {
        tp = head;
        temp = QRandomGenerator::global()->bounded(0,total);
        for(int i = 0;i<temp;i++)
        {
            tp = tp->next;
        }
        ui->BtnD->setText(tp->info.CN);
    }

}
