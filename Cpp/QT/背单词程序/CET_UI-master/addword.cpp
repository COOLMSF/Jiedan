#include "addword.h"
#include "ui_addword.h"
#include <QDebug>
Addword::Addword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Addword)
{
    ui->setupUi(this);
    setFixedSize(300,230);

//    connect(ui->confirmBtn,&QPushButton::clicked,this,&Addword::addAction);

    connect(ui->cancelBtn,&QPushButton::clicked,this,&QDialog::close);

}

Addword::~Addword()
{
    delete ui;
}

void Addword::withWordsModify(Wd wd)
{
    ui->ENLabel->setText(wd.EN);
    ui->CNLabel->setText(wd.CN);
    ui->AttrLabel ->setText(wd.Attr);
}

void Addword::setMode(int mode) //1 Modify 0 add
{
    if(mode ==1)
    {
        ui->ENLabel->setFocusPolicy(Qt::NoFocus);
        disconnect(ui->confirmBtn,&QPushButton::clicked,this,&Addword::addAction);
        connect(ui->confirmBtn,&QPushButton::clicked,this,&Addword::ModifyAction);
    }
    else
    {
        ui->ENLabel->setFocusPolicy(Qt::StrongFocus);
        connect(ui->confirmBtn,&QPushButton::clicked,this,&Addword::addAction);
        disconnect(ui->confirmBtn,&QPushButton::clicked,this,&Addword::ModifyAction);
    }
}

void Addword::addAction()
{
    Wd wd;
    wd.EN = ui->ENLabel->text();
    wd.Attr = ui->AttrLabel->text();
    wd.CN = ui->CNLabel->text();
    ui->ENLabel->setText("");
    ui->CNLabel->setText("");
    ui->AttrLabel->setText("");
    qDebug()<< "emitadd";
    emit confirmadd(wd);
    this->close();
}
void Addword::ModifyAction()
{
    Wd wd;
    wd.EN = ui->ENLabel->text();
    wd.CN = ui->CNLabel->text();
    wd.Attr = ui->AttrLabel->text();
    ui->ENLabel->setText("");
    ui->CNLabel->setText("");
    ui->AttrLabel->setText("");
    emit confirmModify(wd);
        qDebug()<< "emitmodify";
    this->close();
}
