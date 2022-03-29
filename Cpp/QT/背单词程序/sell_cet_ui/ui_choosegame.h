/********************************************************************************
** Form generated from reading UI file 'choosegame.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOOSEGAME_H
#define UI_CHOOSEGAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "choicemodel.h"

QT_BEGIN_NAMESPACE

class Ui_Choosegame
{
public:
    QHBoxLayout *horizontalLayout;
    Choicemodel *model;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QRadioButton *personalL;
    QRadioButton *WrongL;
    QRadioButton *defaultL;
    QLabel *score;
    QLabel *scorela;
    QProgressBar *progressBar;
    QSpacerItem *verticalSpacer_2;
    QPushButton *startBtn;
    QPushButton *stopBtn;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QWidget *Choosegame)
    {
        if (Choosegame->objectName().isEmpty())
            Choosegame->setObjectName(QString::fromUtf8("Choosegame"));
        Choosegame->resize(770, 420);
        Choosegame->setMinimumSize(QSize(770, 420));
        Choosegame->setMaximumSize(QSize(770, 420));
        horizontalLayout = new QHBoxLayout(Choosegame);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        model = new Choicemodel(Choosegame);
        model->setObjectName(QString::fromUtf8("model"));

        horizontalLayout->addWidget(model);

        widget_2 = new QWidget(Choosegame);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        verticalLayout_2 = new QVBoxLayout(widget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        groupBox = new QGroupBox(widget_2);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        personalL = new QRadioButton(groupBox);
        personalL->setObjectName(QString::fromUtf8("personalL"));

        verticalLayout->addWidget(personalL);

        WrongL = new QRadioButton(groupBox);
        WrongL->setObjectName(QString::fromUtf8("WrongL"));

        verticalLayout->addWidget(WrongL);

        defaultL = new QRadioButton(groupBox);
        defaultL->setObjectName(QString::fromUtf8("defaultL"));

        verticalLayout->addWidget(defaultL);


        verticalLayout_2->addWidget(groupBox);

        score = new QLabel(widget_2);
        score->setObjectName(QString::fromUtf8("score"));

        verticalLayout_2->addWidget(score);

        scorela = new QLabel(widget_2);
        scorela->setObjectName(QString::fromUtf8("scorela"));
        QFont font;
        font.setPointSize(15);
        scorela->setFont(font);
        scorela->setLayoutDirection(Qt::LeftToRight);
        scorela->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_2->addWidget(scorela);

        progressBar = new QProgressBar(widget_2);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(progressBar->sizePolicy().hasHeightForWidth());
        progressBar->setSizePolicy(sizePolicy);
        progressBar->setValue(0);

        verticalLayout_2->addWidget(progressBar);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        startBtn = new QPushButton(widget_2);
        startBtn->setObjectName(QString::fromUtf8("startBtn"));
        sizePolicy.setHeightForWidth(startBtn->sizePolicy().hasHeightForWidth());
        startBtn->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(startBtn);

        stopBtn = new QPushButton(widget_2);
        stopBtn->setObjectName(QString::fromUtf8("stopBtn"));

        verticalLayout_2->addWidget(stopBtn);

        verticalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_2->addItem(verticalSpacer_3);


        horizontalLayout->addWidget(widget_2);


        retranslateUi(Choosegame);

        QMetaObject::connectSlotsByName(Choosegame);
    } // setupUi

    void retranslateUi(QWidget *Choosegame)
    {
        Choosegame->setWindowTitle(QCoreApplication::translate("Choosegame", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Choosegame", "\350\257\215\345\272\223\351\200\211\346\213\251", nullptr));
        personalL->setText(QCoreApplication::translate("Choosegame", "\344\270\252\344\272\272\350\257\215\345\272\223", nullptr));
        WrongL->setText(QCoreApplication::translate("Choosegame", "\351\224\231\351\242\230\345\272\223", nullptr));
        defaultL->setText(QCoreApplication::translate("Choosegame", "\347\263\273\347\273\237\351\242\230\345\272\223", nullptr));
        score->setText(QCoreApplication::translate("Choosegame", "\345\210\206\346\225\260\357\274\232", nullptr));
        scorela->setText(QString());
        startBtn->setText(QCoreApplication::translate("Choosegame", "\345\274\200\345\247\213\347\255\224\351\242\230", nullptr));
        stopBtn->setText(QCoreApplication::translate("Choosegame", "\347\273\223\346\235\237\347\255\224\351\242\230", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Choosegame: public Ui_Choosegame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOOSEGAME_H
