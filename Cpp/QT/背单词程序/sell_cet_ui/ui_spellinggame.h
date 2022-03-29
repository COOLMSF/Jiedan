/********************************************************************************
** Form generated from reading UI file 'spellinggame.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPELLINGGAME_H
#define UI_SPELLINGGAME_H

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
#include "spelingmodel.h"

QT_BEGIN_NAMESPACE

class Ui_Spellinggame
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_3;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QRadioButton *PersonalL;
    QRadioButton *WrongL;
    QRadioButton *defaultL;
    QLabel *label_2;
    QLabel *score;
    QProgressBar *progressBar;
    QSpacerItem *verticalSpacer_2;
    QPushButton *StartBtn;
    Spelingmodel *model;
    QPushButton *StopBtn;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *Spellinggame)
    {
        if (Spellinggame->objectName().isEmpty())
            Spellinggame->setObjectName(QString::fromUtf8("Spellinggame"));
        Spellinggame->resize(770, 420);
        Spellinggame->setMinimumSize(QSize(770, 420));
        Spellinggame->setMaximumSize(QSize(770, 420));
        horizontalLayout = new QHBoxLayout(Spellinggame);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget_2 = new QWidget(Spellinggame);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        verticalLayout_2 = new QVBoxLayout(widget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);

        groupBox = new QGroupBox(widget_2);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        PersonalL = new QRadioButton(groupBox);
        PersonalL->setObjectName(QString::fromUtf8("PersonalL"));

        verticalLayout->addWidget(PersonalL);

        WrongL = new QRadioButton(groupBox);
        WrongL->setObjectName(QString::fromUtf8("WrongL"));

        verticalLayout->addWidget(WrongL);

        defaultL = new QRadioButton(groupBox);
        defaultL->setObjectName(QString::fromUtf8("defaultL"));

        verticalLayout->addWidget(defaultL);


        verticalLayout_2->addWidget(groupBox);

        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);

        score = new QLabel(widget_2);
        score->setObjectName(QString::fromUtf8("score"));
        score->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_2->addWidget(score);

        progressBar = new QProgressBar(widget_2);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(progressBar->sizePolicy().hasHeightForWidth());
        progressBar->setSizePolicy(sizePolicy);
        progressBar->setValue(0);

        verticalLayout_2->addWidget(progressBar);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        StartBtn = new QPushButton(widget_2);
        StartBtn->setObjectName(QString::fromUtf8("StartBtn"));

        verticalLayout_2->addWidget(StartBtn);

        model = new Spelingmodel(widget_2);
        model->setObjectName(QString::fromUtf8("model"));

        verticalLayout_2->addWidget(model);

        StopBtn = new QPushButton(widget_2);
        StopBtn->setObjectName(QString::fromUtf8("StopBtn"));

        verticalLayout_2->addWidget(StopBtn);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout->addWidget(widget_2);


        retranslateUi(Spellinggame);

        QMetaObject::connectSlotsByName(Spellinggame);
    } // setupUi

    void retranslateUi(QWidget *Spellinggame)
    {
        Spellinggame->setWindowTitle(QCoreApplication::translate("Spellinggame", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Spellinggame", "\350\257\215\345\272\223\351\200\211\346\213\251", nullptr));
        PersonalL->setText(QCoreApplication::translate("Spellinggame", "\344\270\252\344\272\272\350\257\215\345\272\223", nullptr));
        WrongL->setText(QCoreApplication::translate("Spellinggame", "\351\224\231\351\242\230\345\272\223", nullptr));
        defaultL->setText(QCoreApplication::translate("Spellinggame", "\347\263\273\347\273\237\350\257\215\345\272\223", nullptr));
        label_2->setText(QCoreApplication::translate("Spellinggame", "\345\210\206\346\225\260", nullptr));
        score->setText(QString());
        StartBtn->setText(QCoreApplication::translate("Spellinggame", "\345\274\200\345\247\213\347\255\224\351\242\230", nullptr));
        StopBtn->setText(QCoreApplication::translate("Spellinggame", "\345\201\234\346\255\242\347\255\224\351\242\230", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Spellinggame: public Ui_Spellinggame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPELLINGGAME_H
