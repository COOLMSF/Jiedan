#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QKeyEvent>
#include <QCoreApplication>
#include "errordialog.h"
#define LEN 26

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void error(const QString msg);
    void Penter();

private slots:
    void on_Next_clicked();

    void on_Reload_clicked();

private:
    Ui::MainWindow *ui;
    const QString order="/order.txt";
    const QString words="/words.txt";
    QString path=QCoreApplication::applicationDirPath();
    QString wds[LEN];
    ErrorDialog *w;
    QTextStream in;
    int len=0;
    QFile wd;
    QFile od;
    bool stat=true;

    void keyPressEvent(QKeyEvent *event);

    void load();
};
#endif // MAINWINDOW_H
