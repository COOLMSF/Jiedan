#include "profile.h"
#include "ui_profile.h"

Profile::Profile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Profile)
{
    ui->setupUi(this);


}

Profile::~Profile()
{
    delete ui;
}

void Profile::showWithCurrent(currentDTO *current)
{
    this->current = current;
    if(current->Id == 0)
    {
        ui->LableD->setText("**");
        ui->LableN->setText("**");
        ui->LableS->setText("**");
        ui->LableL->setText("**");
    }
    else
    {
        ui->LableD->setText(QString::number(current->level/12));
        ui->LableN->setText(current->UserName);
        ui->LableS->setText(QString::number(current->score));
        ui->LableL->setText(QString::number(current->level));
    }
}
