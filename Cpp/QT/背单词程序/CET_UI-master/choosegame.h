#ifndef CHOOSEGAME_H
#define CHOOSEGAME_H

#include <QWidget>
#include "currentDTO.h"
#include "choicemodel.h"
#include "word.h"
namespace Ui {
class Choosegame;
}

class Choosegame : public QWidget
{
    Q_OBJECT

public:
    explicit Choosegame(QWidget *parent = nullptr);
    ~Choosegame();

    void transportCurrent(currentDTO * current);

private:
    Ui::Choosegame *ui;
    currentDTO * current;
    int libchooose = 2;
    int round = 0;
    int score = 0;
    int ans;
    int done;
    Wd currentWd;
};

#endif // CHOOSEGAME_H
