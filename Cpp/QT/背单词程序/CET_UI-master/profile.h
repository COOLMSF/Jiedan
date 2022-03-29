#ifndef PROFILE_H
#define PROFILE_H

#include <QDialog>
#include "currentDTO.h"
namespace Ui {
class Profile;
}

class Profile : public QDialog
{
    Q_OBJECT

public:
    explicit Profile(QWidget *parent = nullptr);
    ~Profile();

    void showWithCurrent(currentDTO *current);

    currentDTO * current;

private:
    Ui::Profile *ui;
};

#endif // PROFILE_H
