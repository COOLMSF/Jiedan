#include "mainwindow.h"
#include "login.h"
#include "spelingmodel.h"
#include <QApplication>
#include <QDialog>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
