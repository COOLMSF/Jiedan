#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "currentDTO.h"
#include "addword.h"
#include "login.h"
#include "spelingmodel.h"
#include "profile.h"
#include "choosegame.h"
#include "spellinggame.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    currentDTO current;

    void on_loginBtn_clicked(currentDTO * current);

    void on_reciateBtn_clicked(currentDTO * current);

    void on_wordLearnBtn_clicked();

private:
    Ui::MainWindow *ui;
    Choosegame * chooseGame;
    Spellinggame * spellingGame;
};
#endif // MAINWINDOW_H
