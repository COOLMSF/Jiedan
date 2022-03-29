#include "login.h"
#include "ui_login.h"
#include <QDebug>
#include <QFile>
#include <QMessageBox>

login_2::login_2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login_2)
{
    ui->setupUi(this);

    connect(ui->Btn_to_Reg,&QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(1);
        this->setWindowTitle("注册");
    });

    connect(ui->Btn_to_Log,&QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(0);
        this->setWindowTitle("登录");
    });

    connect(ui->LoginBtn,&QPushButton::clicked,[=](){
        userLogin(current);
    });

    connect(ui->regBtn,&QPushButton::clicked,this,&login_2::userReg);

}

login_2::~login_2()
{
    qDebug() << "delete";
    delete ui;
}

void login_2::showWithIndex(int index,currentDTO *current)
{
    this->ui->stackedWidget->setCurrentIndex(index);
    if(index ==1) this->setWindowTitle("注册");
    else this->setWindowTitle("登录");
    this->current = current;
}

void login_2::userLogin(currentDTO *current)
{
    int userCount;
    QString Id;bool auth = false;
    if(ui->LogUserI->text().isEmpty()||ui->LogUserP->text().isEmpty())
    {
        ui->info->setText("用户名或密码为空");
        return ;
    }
    Node * head = read(&userCount);
    Node * tp = head;
    while(tp != nullptr)
    {
        Id = QString::number(tp->info.userId);
        if (tp->info.password == ui->LogUserP->text() && Id == ui->LogUserI->text())
        {
            qDebug() << "user password:" << tp->info.password;
            qDebug() << "input password:" << ui->LogUserP->text();
            qDebug() << "user id:" << Id;
            qDebug() << "input id:" << ui->LogUserI->text();
            current->Id = tp->info.userId;
            current->score = tp->info.score;
            current->level = tp->info.level;
            current->lastSignTime = tp->info.lastSignTime;
            current->UserName = tp->info.userName;
            qDebug() << "auth" ;
            auth =true;
            break;
        }
        tp = tp->next;
    }
    if(auth)
    {
        save(head);
        QDialog::accept();
    }
    else
    {
        ui->info->setText("用户名或密码错误");
        save(head);
    }

}

void login_2::userReg()
{
    int userCount;
    QString Id;
    bool isReged = false;
    if(ui->RegUserN->text().isEmpty()||ui->RegPass1->text().isEmpty()||ui->RegPass2->text().isEmpty())
    {
        ui->info->setText("请正确填入信息");
        return ;
    }
    qDebug() << "1";
    Node * head = read(&userCount);
    Node * tp = head;
    while(tp != nullptr)
    {
        Id = QString::number(tp->info.userId);
        if (tp->info.userName == ui->RegUserN->text())
        {
            qDebug() << "is" ;
            isReged =true;
            break;
        }
        tp = tp->next;
            qDebug() << "2";
    }

    if(!isReged)
    {
        if(ui->RegPass1->text() != ui->RegPass2->text())
        {
            ui->RegInfo->setText("两次输入的密码不正确！");
            save(head);
                qDebug() << "3";
            return ;
        }
        else
        {
            User user;
            user.userName = ui->RegUserN->text();
            user.userId = 190000+userCount;
            user.password = ui->RegPass1->text();
            user.score = 0;
            user.lastSignTime = 0;
            user.level = 0;
            head = new Node(user,head);
                qDebug() << "4";
            save(head);
            QString susmeg = QString("\t注册成功，你的Id是\t%1\t").arg(QString::number(user.userId));
            QMessageBox::information(this,"注册成功！",susmeg);
            QDialog::accept();
        }

    }
    else
    {
        QString errmsg = QString("该用户已注册，注册Id是\t%1\t").arg(tp->info.userId);
            qDebug() << "5";
        ui->RegInfo->setText(errmsg);
        save(head);
    }

}

void login_2::update(currentDTO *current)
{
    int userCount;
    if(current->Id ==0) return;
    Node*head = read(&userCount);

    Node * tp = head;
    while(tp!=nullptr)
    {
        if(tp->info.userId == current->Id)
        {
            tp->info.lastSignTime = current->lastSignTime;
            tp->info.level = current->level;
            tp->info.score = current->score;
            tp->info.userName = current->UserName;
            break;
        }
        tp = tp->next;
    }
    save(head);
}

void login_2::keyPressEvent(QKeyEvent *e)
{
    if( e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return )  //判断是否是回车键按下
    {
        if(ui->stackedWidget->currentIndex()==1) emit ui->regBtn->clicked();
        else emit ui->LoginBtn->click();//发送出登录按钮的点击信号
    }
}

