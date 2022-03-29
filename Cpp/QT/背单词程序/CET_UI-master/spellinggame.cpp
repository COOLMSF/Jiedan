#include "spellinggame.h"
#include "ui_spellinggame.h"
#include <QMessageBox>
#include <QRandomGenerator>
#include <login.h>
Spellinggame::Spellinggame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Spellinggame)
{
    ui->setupUi(this);
    ui->StartBtn->setHidden(false);
    ui->StopBtn->setHidden(true);
    ui->defaultL->setChecked(true);
    ui->model->setHidden(true);
    ui->defaultL->setCheckable(true);
    ui->PersonalL->setCheckable(true);
    ui->WrongL->setCheckable(true);
    connect(ui->PersonalL,&QRadioButton::clicked,[=](){
        this->libchoose = 0;
    });
    connect(ui->WrongL,&QRadioButton::clicked,[=](){
        this->libchoose = 1;
    });
    connect(ui->defaultL,&QRadioButton::clicked,[=](){
        this->libchoose = 2;
    });

    connect(ui->StartBtn,&QPushButton::clicked,[=](){
        this->round = 0;
        ui->StartBtn->setHidden(true);
        ui->StopBtn->setHidden(false);
        ui->score->setText("0");
        this->score = 0;
        QString filePath;
        switch (this->libchoose)
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
            ui->PersonalL->setCheckable(false);
            ui->WrongL->setCheckable(false);
            NodeWd * tp = head;
            this->done = QRandomGenerator::global()->bounded(0,total);
            for(int i = 0;i<this->done;i++)
            {
                tp = tp->next;
            }
            this->currentWd = tp->info;
            saveLib(head,filePath);
            qDebug() << "123";
            ui->model->setQuest(this->currentWd);
            ui->model->setHidden(false);
        }
    });

    connect(ui->model,&Spelingmodel::choose,[=](QString ans){
        if(ans == this->currentWd.EN)
        {
            this->score+=10;
            this->chance = 3;
            deleteErrorWord(current->Id,currentWd);
        }
        else
        {
            QString note;
            if(this->chance >0)
            {
                if(ans.size() != this->currentWd.EN.size())
                {
                    note = "长度不对";
                } else {
                    note = "";
                    for(int i = 0;i < ans.size();i++)
                    {
                        if(ans.at(i) == this->currentWd.EN.at(i))
                        {
                            note.append(ans.at(i));
                        }
                        else note.append("_");
                    }
                }
                chance--;
                QString add = QString(", 还有%1次机会").arg(QString::number(this->chance));

                note.append(add);

                ui->model->setRetry(note);
                return ;
            }
            else
            {
                this->score-=10;
                saveErrorWord(current->Id,currentWd);
            }
        }
        ui->score->setText(QString::number(this->score));
        ui->progressBar->setValue((round+1)*10);
        this->round++;
        qDebug() << this->round;
        if(this->round<10)
        {
            QString filePath;
            int total;
            switch (this->libchoose)
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
                for(int i = 0;i<this->done;i++)
                {
                    tp = tp->next;
                }
                this->currentWd = tp->info;
                saveLib(head,filePath);
                ui->model->setQuest(currentWd);
            }
            else
            {
                this->current->score +=score;
                login_2::update(current);
                ui->StartBtn->setHidden(false);
                ui->StopBtn->setHidden(true);
                ui->defaultL->setCheckable(true);
                ui->PersonalL->setCheckable(true);
                ui->WrongL->setCheckable(true);
                ui->model->setHidden(true);
            }

        }
        else
        {
            this->current->score +=score;
            login_2::update(current);
            ui->StartBtn->setHidden(false);
            ui->StopBtn->setHidden(true);
            ui->defaultL->setCheckable(true);
            ui->PersonalL->setCheckable(true);
            ui->WrongL->setCheckable(true);
            ui->model->setHidden(true);
        }


    });
    connect(ui->StopBtn,&QPushButton::clicked,[=]()
    {
        this->current->score +=score;
        login_2::update(current);
        ui->StartBtn->setHidden(false);
        ui->StopBtn->setHidden(true);
        ui->defaultL->setCheckable(true);
        ui->PersonalL->setCheckable(true);
        ui->WrongL->setCheckable(true);
        this->close();
    });
}

Spellinggame::~Spellinggame()
{
    delete ui;
}

void Spellinggame::transportCurrent(currentDTO *current)
{
    this->current = current;
}
