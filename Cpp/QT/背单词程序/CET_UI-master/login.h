#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "currentDTO.h"
#include <user.h>
#include <QKeyEvent>

namespace Ui {
class login_2;
}

class login_2 : public QDialog
{
    Q_OBJECT

public:
    explicit login_2(QWidget *parent = nullptr);
    ~login_2();
    void showWithIndex(int index,currentDTO *current);
    void userLogin(currentDTO *current);
    void userReg();
    currentDTO *current;

    static void update(currentDTO *current);
    void keyPressEvent(QKeyEvent *e);
private:
    Ui::login_2 *ui;
};

#endif // LOGIN_H
