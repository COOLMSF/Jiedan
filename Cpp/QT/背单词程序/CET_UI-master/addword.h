#ifndef ADDWORD_H
#define ADDWORD_H

#include <QDialog>
#include "word.h"

namespace Ui {
class Addword;
}

class Addword : public QDialog
{
    Q_OBJECT

public:
    explicit Addword(QWidget *parent = nullptr);
    ~Addword();
    void withWordsModify(Wd wd);
    void setMode(int mode);
    void addAction();
    void ModifyAction();

signals:
    void confirmadd(Wd wd);
    void confirmModify(Wd wd);

private:
    Ui::Addword *ui;
};

#endif // ADDWORD_H
