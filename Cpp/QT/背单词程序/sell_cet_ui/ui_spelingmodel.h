/********************************************************************************
** Form generated from reading UI file 'spelingmodel.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPELINGMODEL_H
#define UI_SPELINGMODEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Spelingmodel
{
public:
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *AttrLabel;
    QLineEdit *anserLabel;
    QSpacerItem *horizontalSpacer;
    QLabel *CNLabel;
    QSpacerItem *verticalSpacer;
    QPushButton *checkBtn;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer_2;
    QLabel *note;

    void setupUi(QWidget *Spelingmodel)
    {
        if (Spelingmodel->objectName().isEmpty())
            Spelingmodel->setObjectName(QString::fromUtf8("Spelingmodel"));
        Spelingmodel->resize(500, 375);
        Spelingmodel->setMinimumSize(QSize(500, 375));
        Spelingmodel->setMaximumSize(QSize(500, 375));
        verticalLayout_2 = new QVBoxLayout(Spelingmodel);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        widget = new QWidget(Spelingmodel);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(20);
        font.setBold(false);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("color: rgb(7, 7, 7);"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 1, 0, 1, 1);

        AttrLabel = new QLabel(widget);
        AttrLabel->setObjectName(QString::fromUtf8("AttrLabel"));
        AttrLabel->setStyleSheet(QString::fromUtf8("color: rgb(137, 137, 137);"));
        AttrLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(AttrLabel, 4, 0, 1, 1);

        anserLabel = new QLineEdit(widget);
        anserLabel->setObjectName(QString::fromUtf8("anserLabel"));
        anserLabel->setMinimumSize(QSize(0, 40));
        anserLabel->setMaximumSize(QSize(16777215, 40));
        QFont font1;
        font1.setPointSize(13);
        anserLabel->setFont(font1);
        anserLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(anserLabel, 5, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 9, 0, 1, 1);

        CNLabel = new QLabel(widget);
        CNLabel->setObjectName(QString::fromUtf8("CNLabel"));
        QFont font2;
        font2.setPointSize(28);
        font2.setBold(true);
        CNLabel->setFont(font2);
        CNLabel->setStyleSheet(QString::fromUtf8("color: rgb(8, 0, 195);"));
        CNLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(CNLabel, 3, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 7, 0, 1, 1);

        checkBtn = new QPushButton(widget);
        checkBtn->setObjectName(QString::fromUtf8("checkBtn"));
        checkBtn->setMinimumSize(QSize(0, 40));
        checkBtn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgba(0, 142, 255, 158);"));

        gridLayout->addWidget(checkBtn, 8, 0, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_4, 0, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_3, 10, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 2, 0, 1, 1);

        note = new QLabel(widget);
        note->setObjectName(QString::fromUtf8("note"));

        gridLayout->addWidget(note, 6, 0, 1, 1);


        verticalLayout_2->addWidget(widget);


        retranslateUi(Spelingmodel);

        QMetaObject::connectSlotsByName(Spelingmodel);
    } // setupUi

    void retranslateUi(QWidget *Spelingmodel)
    {
        Spelingmodel->setWindowTitle(QCoreApplication::translate("Spelingmodel", "Form", nullptr));
        label->setText(QCoreApplication::translate("Spelingmodel", "\350\257\267\350\276\223\345\205\245\345\257\271\345\272\224\347\232\204\350\213\261\346\226\207", nullptr));
        AttrLabel->setText(QString());
        anserLabel->setText(QString());
        CNLabel->setText(QString());
        checkBtn->setText(QCoreApplication::translate("Spelingmodel", "\344\270\213\344\270\200\344\270\252", nullptr));
        note->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Spelingmodel: public Ui_Spelingmodel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPELINGMODEL_H
