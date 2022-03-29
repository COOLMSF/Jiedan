/********************************************************************************
** Form generated from reading UI file 'choicemodel.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOICEMODEL_H
#define UI_CHOICEMODEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Choicemodel
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QLabel *EnLabel;
    QLabel *AttrLabel;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *BtnA;
    QRadioButton *BtnB;
    QRadioButton *BtnC;
    QRadioButton *BtnD;
    QSpacerItem *horizontalSpacer;
    QPushButton *checkBtn;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *Choicemodel)
    {
        if (Choicemodel->objectName().isEmpty())
            Choicemodel->setObjectName(QString::fromUtf8("Choicemodel"));
        Choicemodel->resize(500, 375);
        Choicemodel->setMinimumSize(QSize(500, 375));
        Choicemodel->setMaximumSize(QSize(500, 375));
        verticalLayout = new QVBoxLayout(Choicemodel);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new QWidget(Choicemodel);
        widget->setObjectName(QString::fromUtf8("widget"));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(20);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label);

        EnLabel = new QLabel(widget);
        EnLabel->setObjectName(QString::fromUtf8("EnLabel"));
        QFont font1;
        font1.setPointSize(28);
        font1.setBold(true);
        EnLabel->setFont(font1);
        EnLabel->setStyleSheet(QString::fromUtf8("color: rgb(8, 0, 195);"));
        EnLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(EnLabel);

        AttrLabel = new QLabel(widget);
        AttrLabel->setObjectName(QString::fromUtf8("AttrLabel"));
        QFont font2;
        font2.setPointSize(17);
        font2.setBold(true);
        font2.setItalic(true);
        AttrLabel->setFont(font2);
        AttrLabel->setAutoFillBackground(false);
        AttrLabel->setStyleSheet(QString::fromUtf8("color: rgb(137, 137, 137);"));
        AttrLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(AttrLabel);


        verticalLayout->addWidget(widget);

        groupBox = new QGroupBox(Choicemodel);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        widget_3 = new QWidget(groupBox);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        verticalLayout_3 = new QVBoxLayout(widget_3);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        BtnA = new QRadioButton(widget_3);
        BtnA->setObjectName(QString::fromUtf8("BtnA"));
        QFont font3;
        font3.setPointSize(12);
        BtnA->setFont(font3);

        verticalLayout_3->addWidget(BtnA);

        BtnB = new QRadioButton(widget_3);
        BtnB->setObjectName(QString::fromUtf8("BtnB"));
        BtnB->setFont(font3);

        verticalLayout_3->addWidget(BtnB);

        BtnC = new QRadioButton(widget_3);
        BtnC->setObjectName(QString::fromUtf8("BtnC"));
        BtnC->setFont(font3);

        verticalLayout_3->addWidget(BtnC);

        BtnD = new QRadioButton(widget_3);
        BtnD->setObjectName(QString::fromUtf8("BtnD"));
        BtnD->setFont(font3);

        verticalLayout_3->addWidget(BtnD);


        horizontalLayout->addWidget(widget_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        checkBtn = new QPushButton(groupBox);
        checkBtn->setObjectName(QString::fromUtf8("checkBtn"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(checkBtn->sizePolicy().hasHeightForWidth());
        checkBtn->setSizePolicy(sizePolicy);
        QFont font4;
        font4.setPointSize(61);
        checkBtn->setFont(font4);
        checkBtn->setCheckable(false);
        checkBtn->setChecked(false);
        checkBtn->setFlat(false);

        horizontalLayout->addWidget(checkBtn);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addWidget(groupBox);


        retranslateUi(Choicemodel);

        QMetaObject::connectSlotsByName(Choicemodel);
    } // setupUi

    void retranslateUi(QWidget *Choicemodel)
    {
        Choicemodel->setWindowTitle(QCoreApplication::translate("Choicemodel", "Form", nullptr));
        label->setText(QCoreApplication::translate("Choicemodel", "\351\200\211\346\213\251\346\255\243\347\241\256\347\232\204\351\200\211\351\241\271", nullptr));
        EnLabel->setText(QString());
        AttrLabel->setText(QString());
        groupBox->setTitle(QString());
        BtnA->setText(QString());
        BtnB->setText(QString());
        BtnC->setText(QString());
        BtnD->setText(QString());
        checkBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Choicemodel: public Ui_Choicemodel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOICEMODEL_H
