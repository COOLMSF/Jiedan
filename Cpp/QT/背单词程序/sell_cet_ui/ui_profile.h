/********************************************************************************
** Form generated from reading UI file 'profile.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROFILE_H
#define UI_PROFILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Profile
{
public:
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QGridLayout *gridLayout;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *name;
    QLabel *level;
    QLabel *score;
    QLabel *checkDays;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout;
    QLabel *LableN;
    QLabel *LableL;
    QLabel *LableS;
    QLabel *LableD;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *Profile)
    {
        if (Profile->objectName().isEmpty())
            Profile->setObjectName(QString::fromUtf8("Profile"));
        Profile->resize(320, 240);
        verticalLayout_2 = new QVBoxLayout(Profile);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        widget = new QWidget(Profile);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(21, 0, 206);"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        widget_3 = new QWidget(widget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        verticalLayout_3 = new QVBoxLayout(widget_3);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        name = new QLabel(widget_3);
        name->setObjectName(QString::fromUtf8("name"));
        QFont font;
        font.setPointSize(18);
        font.setBold(true);
        name->setFont(font);

        verticalLayout_3->addWidget(name);

        level = new QLabel(widget_3);
        level->setObjectName(QString::fromUtf8("level"));
        level->setFont(font);

        verticalLayout_3->addWidget(level);

        score = new QLabel(widget_3);
        score->setObjectName(QString::fromUtf8("score"));
        score->setFont(font);

        verticalLayout_3->addWidget(score);

        checkDays = new QLabel(widget_3);
        checkDays->setObjectName(QString::fromUtf8("checkDays"));
        QFont font1;
        font1.setPointSize(18);
        checkDays->setFont(font1);

        verticalLayout_3->addWidget(checkDays);


        gridLayout->addWidget(widget_3, 1, 1, 1, 1);

        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        verticalLayout = new QVBoxLayout(widget_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        LableN = new QLabel(widget_2);
        LableN->setObjectName(QString::fromUtf8("LableN"));
        QFont font2;
        font2.setPointSize(18);
        font2.setBold(false);
        LableN->setFont(font2);
        LableN->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(LableN);

        LableL = new QLabel(widget_2);
        LableL->setObjectName(QString::fromUtf8("LableL"));
        LableL->setFont(font1);
        LableL->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(LableL);

        LableS = new QLabel(widget_2);
        LableS->setObjectName(QString::fromUtf8("LableS"));
        LableS->setFont(font1);
        LableS->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(LableS);

        LableD = new QLabel(widget_2);
        LableD->setObjectName(QString::fromUtf8("LableD"));
        LableD->setFont(font1);
        LableD->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(LableD);


        gridLayout->addWidget(widget_2, 1, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 3, 1, 1);


        verticalLayout_2->addWidget(widget);


        retranslateUi(Profile);

        QMetaObject::connectSlotsByName(Profile);
    } // setupUi

    void retranslateUi(QWidget *Profile)
    {
        Profile->setWindowTitle(QCoreApplication::translate("Profile", "Form", nullptr));
        name->setText(QCoreApplication::translate("Profile", "\345\220\215\347\247\260\357\274\232", nullptr));
        level->setText(QCoreApplication::translate("Profile", "\347\255\211\347\272\247\357\274\232", nullptr));
        score->setText(QCoreApplication::translate("Profile", "\347\247\257\345\210\206\357\274\232", nullptr));
        checkDays->setText(QCoreApplication::translate("Profile", "\346\211\223\345\215\241\345\244\251\346\225\260\357\274\232", nullptr));
        LableN->setText(QString());
        LableL->setText(QString());
        LableS->setText(QString());
        LableD->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Profile: public Ui_Profile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROFILE_H
