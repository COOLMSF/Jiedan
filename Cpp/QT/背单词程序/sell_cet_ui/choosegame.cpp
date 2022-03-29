#include "choosegame.h"
#include "ui_choosegame.h"
#include <QMessageBox>
#include <QDebug>
#include "login.h"
Choosegame::Choosegame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Choosegame)
{
    ui->setupUi(this);
    ui->startBtn->setHidden(false);
    ui->stopBtn->setHidden(true);
    ui->defaultL->setChecked(true);
    ui->model->setHidden(true);
    ui->defaultL->setCheckable(true);
    ui->personalL->setCheckable(true);
    ui->WrongL->setCheckable(true);
    connect(ui->personalL,&QRadioButton::clicked,[=](){
        this->libchooose = 0;
    });
    connect(ui->WrongL,&QRadioButton::clicked,[=](){
        this->libchooose = 1;
    });
    connect(ui->defaultL,&QRadioButton::clicked,[=](){
        this->libchooose = 2;
    });

    connect(ui->startBtn,&QPushButton::clicked,[=]()
    {
        this->round = 0;
        ui->startBtn->setHidden(true);
        ui->stopBtn->setHidden(false);
        ui->scorela->setText("0");
        this->score = 0;
        QString filePath;
        switch (this->libchooose)
        {
        case 0: filePath = QString("./src/lib/L_%1.dat").arg(current->Id);
            break;
        case 1:filePath = QString("./src/lib/R_%1.dat").arg(current->Id);
            break;
        case 2:filePath = QString("./src/lib/defaultWordLib.dat");
            break;
        default:
            QMessageBox::warning(this,"错误","请选择词库后操作");
            return;
        }

        int total;
        NodeWd * head = loadLib(filePath,&total);
        if(head == nullptr)
        {
            QMessageBox::warning(this,"错误","词库为空");
        }
        else
        {
            ui->defaultL->setCheckable(false);
            ui->personalL->setCheckable(false);
            ui->WrongL->setCheckable(false);
            NodeWd * tp = head;
            this->done = QRandomGenerator::global()->bounded(0,total);
            this->ans = QRandomGenerator::global()->bounded(0,4);
            for(int i = 0;i<this->done;i++)
            {
                tp = tp->next;
            }
            this->currentWd = tp->info;
            saveLib(head,filePath);
            qDebug() << "123";
            ui->model->setQuest(this->currentWd,this->ans);
            ui->model->setHidden(false);
        }

    });

    connect(ui->model,&Choicemodel::choose,[=](int cAns){
        if(cAns == this->ans)
        {
            this->score+=10;
            deleteErrorWord(current->Id,currentWd);
        }
        else
        {
            this->score-=10;
            saveErrorWord(current->Id,currentWd);
        }
        ui->scorela->setText(QString::number(this->score));
        ui->progressBar->setValue((round+1)*10);
        this->round++;
        qDebug() << this->round;
        if(this->round<10)
        {
            QString filePath;
            int total;
            switch (this->libchooose)
            {
            case 0: filePath = QString("./src/lib/L_%1.dat").arg(current->Id);
                break;
            case 1:filePath = QString("./src/lib/R_%1.dat").arg(current->Id);
                break;
            case 2:filePath = QString("./src/lib/defaultWordLib.dat");
                break;
            }
            NodeWd * head = loadLib(filePath,&total);
            NodeWd * tp = head;
            if(head != nullptr)
            {
                this->done = QRandomGenerator::global()->bounded(0,total);
                this->ans = QRandomGenerator::global()->bounded(0,4);
                for(int i = 0;i<this->done;i++)
                {
                    tp = tp->next;
                }
                this->currentWd = tp->info;
                saveLib(head,filePath);
                ui->model->setQuest(currentWd,ans);
            }
            else
            {
                this->current->score +=score;
                login_2::update(current);
                ui->startBtn->setHidden(false);
                ui->stopBtn->setHidden(true);
                ui->defaultL->setCheckable(true);
                ui->personalL->setCheckable(true);
                ui->WrongL->setCheckable(true);
                ui->model->setHidden(true);
            }

        }
        else
        {
            this->current->score +=score;
            login_2::update(current);
            ui->startBtn->setHidden(false);
            ui->stopBtn->setHidden(true);
            ui->defaultL->setCheckable(true);
            ui->personalL->setCheckable(true);
            ui->WrongL->setCheckable(true);
            ui->model->setHidden(true);
        }


    });

    connect(ui->stopBtn,&QPushButton::clicked,[=]()
    {
        this->current->score +=score;
        login_2::update(current);
        ui->startBtn->setHidden(false);
        ui->stopBtn->setHidden(true);
        ui->defaultL->setCheckable(true);
        ui->personalL->setCheckable(true);
        ui->WrongL->setCheckable(true);
        this->close();
    });


}

Choosegame::~Choosegame()
{
    delete ui;
}

void Choosegame::transportCurrent(currentDTO *current)
{
    this->current = current;
}
