#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFont>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFont font;
    font.setPointSize(30);
    ui->label->setFont(font);
    w=new ErrorDialog();
    connect(this,&MainWindow::error,w,&ErrorDialog::getError);
    connect(this,&MainWindow::Penter,ui->Next,&QPushButton::click);
    ui->label_2->setText(QCoreApplication::applicationDirPath());
    load();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::load(){
    wd.setFileName(path+words);
    if(!wd.open(QIODevice::ReadOnly | QIODevice::Text)){
        //emit error("error in opening words.txt");
        //w->show();
        ui->label->setText(path+"words.txt异常");
        stat=false;
        return;
    }
    od.setFileName(path+order);
    if(!od.open(QIODevice::ReadOnly | QIODevice::Text)){
        //emit error("error in opening order.txt");
        //w->show();
        ui->label->setText("order.txt异常");
        stat=false;
        return;
    }
    in.setDevice(&wd);
    while(!in.atEnd()){
        in>>wds[len++];
        //去除空行
        if(wds[len-1]==""){
            len--;
            break;
        }
    }
    in.setDevice(&od);
    qDebug()<<(char)('a'+len);
}

void MainWindow::on_Next_clicked()
{
    if(!stat){
        return;
    }
    bool flag=true;
    char c;
    int i;
    while(!in.atEnd()){
        in>>c;
        i=(int)(c-'a');
        if(i<len){
            ui->label->setText(wds[i]);
            flag=false;
            qDebug()<<c;
            break;
        }
    }
    if(flag&&in.atEnd()){
        ui->label->setText("END");
    }
}

void MainWindow::on_Reload_clicked()
{
    if(!stat){
        return;
    }
    in.flush();
    od.reset();
    in.setDevice(&od);
    ui->label->setText("开始");
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return){
        emit Penter();
    }
}
