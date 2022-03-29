/********************************************************************************
** Form generated from reading UI file 'addword.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDWORD_H
#define UI_ADDWORD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Addword
{
public:
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_4;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLineEdit *ENLabel;
    QLabel *label;
    QLineEdit *AttrLabel;
    QLabel *label_2;
    QLineEdit *CNLabel;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *confirmBtn;
    QPushButton *cancelBtn;

    void setupUi(QWidget *Addword)
    {
        if (Addword->objectName().isEmpty())
            Addword->setObjectName(QString::fromUtf8("Addword"));
        Addword->resize(295, 230);
        verticalLayout_2 = new QVBoxLayout(Addword);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        widget_2 = new QWidget(Addword);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        verticalLayout = new QVBoxLayout(widget_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget_3 = new QWidget(widget_2);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        verticalLayout_3 = new QVBoxLayout(widget_3);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_4 = new QLabel(widget_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        label_4->setFont(font);
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_4);


        verticalLayout->addWidget(widget_3);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_3 = new QLabel(widget_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        ENLabel = new QLineEdit(widget_2);
        ENLabel->setObjectName(QString::fromUtf8("ENLabel"));

        gridLayout->addWidget(ENLabel, 0, 1, 1, 1);

        label = new QLabel(widget_2);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        AttrLabel = new QLineEdit(widget_2);
        AttrLabel->setObjectName(QString::fromUtf8("AttrLabel"));

        gridLayout->addWidget(AttrLabel, 1, 1, 1, 1);

        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        CNLabel = new QLineEdit(widget_2);
        CNLabel->setObjectName(QString::fromUtf8("CNLabel"));

        gridLayout->addWidget(CNLabel, 2, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);


        verticalLayout_2->addWidget(widget_2);

        widget = new QWidget(Addword);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        confirmBtn = new QPushButton(widget);
        confirmBtn->setObjectName(QString::fromUtf8("confirmBtn"));
        confirmBtn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(0, 125, 255);"));

        horizontalLayout->addWidget(confirmBtn);

        cancelBtn = new QPushButton(widget);
        cancelBtn->setObjectName(QString::fromUtf8("cancelBtn"));

        horizontalLayout->addWidget(cancelBtn);


        verticalLayout_2->addWidget(widget);


        retranslateUi(Addword);

        QMetaObject::connectSlotsByName(Addword);
    } // setupUi

    void retranslateUi(QWidget *Addword)
    {
        Addword->setWindowTitle(QCoreApplication::translate("Addword", "\345\215\225\350\257\215\344\277\241\346\201\257", nullptr));
        label_4->setText(QCoreApplication::translate("Addword", "\350\276\223\345\205\245\345\215\225\350\257\215\347\233\270\345\205\263\344\277\241\346\201\257", nullptr));
        label_3->setText(QCoreApplication::translate("Addword", "\350\213\261\346\226\207\357\274\232", nullptr));
        label->setText(QCoreApplication::translate("Addword", "\350\257\215\346\200\247\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("Addword", "\344\270\255\346\226\207\357\274\232", nullptr));
        confirmBtn->setText(QCoreApplication::translate("Addword", "\346\217\220\344\272\244", nullptr));
        cancelBtn->setText(QCoreApplication::translate("Addword", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Addword: public Ui_Addword {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDWORD_H
