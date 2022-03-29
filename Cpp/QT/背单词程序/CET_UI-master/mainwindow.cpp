#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDialog>
#include <QMessageBox>
#include <QStatusBar>
#include <QFileDialog>
#include <QString>
#include <QDir>
#include <QMessageBox>
#include <QDateTime>
#include "viewlib.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // ui->menuBar->setNativeMenuBar(false);
    ui->statusBar->setSizeGripEnabled(false);//去掉状态栏右下角的三角
    ui->statusBar->showMessage(tr("welcome to BCD!"),10000);//显示临时信息2000ms
    setWindowIcon(QIcon(":/icon.png"));

    QDateTime qt = QDateTime::currentDateTime();
    current.dateOfToday = qt.toString("MMdd").toInt();

    connect(ui->actionAbout,&QAction::triggered,[=](){
        QMessageBox::about(this,"关于","\t背背单词\n");

    });

    connect(ui->actionmodelComment,&QAction::triggered,[=](){
        QMessageBox::about(this,"模式说明","模式说明\n选择题模式：显示英文及四个中文选项，用户选择正确的选项\n拼写模式：显示英文，用户输入对应英文");
    });

    connect(ui->actionHelp,&QAction::triggered,[=](){
        QDialog * dig = new QDialog(this) ;
        dig->resize(100,100);
        dig->setAttribute(Qt::WA_DeleteOnClose);
        dig->show();
    });

    connect(ui->actionLogin,&QAction::triggered,[=](){
        login_2 * loginWindow = new login_2(this);
        loginWindow->setAttribute(Qt::WA_DeleteOnClose);
        loginWindow->showWithIndex(0,&current);
        if(QDialog::Accepted ==  loginWindow->exec() && current.Id != 0)
        {
            QString welcome = QString(" 欢迎，%1\t \t").arg(this->current.UserName);
            QMessageBox::information(this,"登陆成功",welcome,QMessageBox::Ok,QMessageBox::Ok);
        }
        qDebug() << this->current.Id;
        if(current.Id == 0)
        {
            QString courage = "未登录";
            ui->CourageText->setText(courage);
        }
        else
        {
            QString courage = QString("已坚持打卡%1天，继续努力！").arg(current.level/12);
            ui->CourageText->setText(courage);
            ui->loginBtn->setText("退出登录");
            if(current.lastSignTime == current.dateOfToday)
            {
                ui->checkBtn->setText("今日已打卡");
            }
            else
            {
                ui->checkBtn->setText("打卡");
            }
            disconnect(ui->loginBtn,&QPushButton::clicked,ui->actionLogin,&QAction::triggered);
            connect(ui->loginBtn,&QPushButton::clicked,ui->actionconfirmexit,&QAction::triggered);

        }
    });

    connect(ui->actionconfirmexit,&QAction::triggered,[=](){
       login_2::update(&current);
       ui->CourageText->setText("已退出");
       ui->checkBtn->setText("打卡");
       connect(ui->loginBtn,&QPushButton::clicked,ui->actionLogin,&QAction::triggered);
       disconnect(ui->loginBtn,&QPushButton::clicked,ui->actionconfirmexit,&QAction::triggered);
       ui->loginBtn->setText("登录");
       current.Id = 0;
    });

    connect(ui->actionRegister,&QAction::triggered,[=](){
        login_2 * loginWindow = new login_2(this);
        loginWindow->setAttribute(Qt::WA_DeleteOnClose);
        loginWindow->showWithIndex(1,&current);
        loginWindow->exec();
    });

    connect(ui->actionExit,&QAction::triggered,[=](){
        if(QMessageBox::Yes ==  QMessageBox::question(this,"tcqd","是否退出"))
        {
            login_2::update(&current);
            this->close();
        }
    });

    connect(ui->actionaddLib,&QAction::triggered,[=](){
        QFileDialog::getOpenFileName(this,"打开词库","","(*.txt)");
    });

    connect(ui->actionLearn,&QAction::triggered,[=](){
        viewLib * Lib = new viewLib(this);
        Lib->setAttribute(Qt::WA_DeleteOnClose);
        Lib->transferCurrent(&current,1);
        Lib->exec();
    });

    //打卡
    connect(ui->actioncheck,&QAction::triggered,[=](){
        if(current.Id == 0)
        {
            QMessageBox::warning(this,"未登录","请先登录后再进行打卡");
        }
        else
        {
            if(current.dateOfToday != current.lastSignTime) {
                current.level += 12;
                current.lastSignTime = current.dateOfToday;
                login_2::update(&current);
                ui->checkBtn->setText("今日已打卡");
                QMessageBox::about(this,"check","打卡成功！");
                QString courage = QString("已坚持打卡%1天，继续努力！").arg(current.level/12);
                ui->CourageText->setText(courage);
            } else {
                QMessageBox::warning(this,"抱歉","今天已经打过卡啦，明天再来吧");
            }
        }

    });
    //查看个人信息
    connect(ui->actionprofile,&QAction::triggered,[=](){
        Profile * profile = new Profile(this);
        profile->setAttribute(Qt::WA_DeleteOnClose);
        profile->showWithCurrent(&current);
        profile->show();
    });
    //
    connect(ui->actionexplorer,&QAction::triggered,[=](){
        viewLib * Lib = new viewLib(this);
        Lib->setAttribute(Qt::WA_DeleteOnClose);
        Lib->transferCurrent(&current,0);
        Lib->exec();
//        if(QDialog::Rejected ==  Lib->exec())
//        {
//            QMessageBox::warning(this,"错误","您未登录，请登陆后重试。");
//        }
    });

    connect(ui->actionspellingModel,&QAction::triggered,[=](){
        if(current.Id == 0)
        {
            QMessageBox::warning(this,"未登录","请先登录");
        }
        else
        {
            this->spellingGame = new Spellinggame();
            this->spellingGame->transportCurrent(&current);
            this->spellingGame->show();
        }
    });

    connect(ui->actionchoiceModel,&QAction::triggered,[=](){
        if(current.Id == 0)
        {
            QMessageBox::warning(this,"未登录","请先登录");
        }
        else
        {
            this->chooseGame = new Choosegame();
            this->chooseGame->transportCurrent(&current);
            this->chooseGame->show();
        }
    });

    connect(ui->loginBtn,&QPushButton::clicked,ui->actionLogin,&QAction::triggered);

    connect(ui->checkBtn,&QPushButton::clicked,ui->actioncheck,&QAction::triggered);

    connect(ui->wordLearnBtn,&QPushButton::clicked,ui->actiondefLearn,&QAction::triggered);
    if(current.Id == 0)
    {
        QString courage = "未登录";
        ui->CourageText->setText(courage);
    }
}
MainWindow::~MainWindow()
{
    delete ui;
    qDebug() << "delete";
}
