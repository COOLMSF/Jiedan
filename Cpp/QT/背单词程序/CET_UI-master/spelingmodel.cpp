#include "spelingmodel.h"
#include "ui_spelingmodel.h"

Spelingmodel::Spelingmodel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Spelingmodel)
{
    ui->setupUi(this);

    connect(ui->checkBtn,&QPushButton::clicked,[=](){
        emit choose(ui->anserLabel->text().trimmed());
        ui->anserLabel->setText("");
    });
}

Spelingmodel::~Spelingmodel()
{
    delete ui;
}

void Spelingmodel::setQuest(Wd wd)
{
    ui->CNLabel->setText(wd.CN);
    qDebug() << wd.EN;
    ui->AttrLabel->setText(wd.Attr);
    ui->note->setText("");
    ui->anserLabel->setFocus();

}

void Spelingmodel::setRetry(QString Note)
{
//    ui->anserLabel->setText("");
    ui->note->setText(Note);
        ui->anserLabel->setFocus();
}

void Spelingmodel::keyPressEvent(QKeyEvent *e)
{
    if( e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return )  //判断是否是回车键按下
    {
         emit ui->checkBtn->clicked();
    }

}
