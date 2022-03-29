#ifndef CHOICEMODEL_H
#define CHOICEMODEL_H

#include <QWidget>
#include "word.h"
#include <QRandomGenerator>

namespace Ui {
class Choicemodel;
}

class Choicemodel : public QWidget
{
    Q_OBJECT

public:
    explicit Choicemodel(QWidget *parent = nullptr);
    ~Choicemodel();

    void setQuest(Wd wd,int ans);

signals:
    void choose(int choise);

private:
    Ui::Choicemodel *ui;

};

#endif // CHOICEMODEL_H
