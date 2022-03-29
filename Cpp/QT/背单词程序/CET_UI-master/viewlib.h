#ifndef VIEWLIB_H
#define VIEWLIB_H

#include <QDialog>
#include <QString>
#include "currentDTO.h"
#include "word.h"
#include "addword.h"
namespace Ui {
class viewLib;
}

class viewLib : public QDialog
{
    Q_OBJECT

public:
    explicit viewLib(QWidget *parent = nullptr);
    ~viewLib();

    currentDTO * current;
    int status = -1;
    void transferCurrent(currentDTO* current,int status);
    void addwd(Wd wd);
    void closeEvent(QCloseEvent *);
private:
    Ui::viewLib *ui;
    Addword * adw;
};

#endif // VIEWLIB_H
