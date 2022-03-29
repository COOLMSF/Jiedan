#ifndef SPELLINGGAME_H
#define SPELLINGGAME_H

#include <QWidget>
#include "currentDTO.h"
#include "word.h"
namespace Ui {
class Spellinggame;
}

class Spellinggame : public QWidget
{
    Q_OBJECT

public:
    explicit Spellinggame(QWidget *parent = nullptr);
    ~Spellinggame();
    void transportCurrent(currentDTO *current);
private:
    Ui::Spellinggame *ui;
    currentDTO * current;
    int libchoose = 2;
    int round = 0;
    int score = 0;
    int done;
    Wd currentWd;
    int chance = 3;
};

#endif // SPELLINGGAME_H
