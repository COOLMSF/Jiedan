#ifndef SPELINGMODEL_H
#define SPELINGMODEL_H

#include <QWidget>
#include <word.h>
#include <QKeyEvent>
namespace Ui {
class Spelingmodel;
}

class Spelingmodel : public QWidget
{
    Q_OBJECT

public:
    explicit Spelingmodel(QWidget *parent = nullptr);
    ~Spelingmodel();


    void setQuest(Wd wd);
    void setRetry(QString Note);
    void keyPressEvent(QKeyEvent *event);
signals:
    void choose(QString ans);
private:

    Ui::Spelingmodel *ui;
};

#endif // SPELINGMODEL_H
