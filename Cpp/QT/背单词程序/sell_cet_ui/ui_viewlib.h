/********************************************************************************
** Form generated from reading UI file 'viewlib.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWLIB_H
#define UI_VIEWLIB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_viewLib
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *personalL;
    QRadioButton *wrongL;
    QRadioButton *defaultL;
    QTableWidget *tableWidget;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *AddBtn;
    QPushButton *ModifyBtn;
    QPushButton *deleteBtn;
    QPushButton *clearBtn;

    void setupUi(QDialog *viewLib)
    {
        if (viewLib->objectName().isEmpty())
            viewLib->setObjectName(QString::fromUtf8("viewLib"));
        viewLib->resize(374, 585);
        verticalLayout = new QVBoxLayout(viewLib);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(viewLib);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(16);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        widget_2 = new QWidget(viewLib);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        personalL = new QRadioButton(widget_2);
        personalL->setObjectName(QString::fromUtf8("personalL"));

        horizontalLayout_2->addWidget(personalL);

        wrongL = new QRadioButton(widget_2);
        wrongL->setObjectName(QString::fromUtf8("wrongL"));

        horizontalLayout_2->addWidget(wrongL);

        defaultL = new QRadioButton(widget_2);
        defaultL->setObjectName(QString::fromUtf8("defaultL"));

        horizontalLayout_2->addWidget(defaultL);


        verticalLayout->addWidget(widget_2);

        tableWidget = new QTableWidget(viewLib);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        verticalLayout->addWidget(tableWidget);

        widget = new QWidget(viewLib);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        AddBtn = new QPushButton(widget);
        AddBtn->setObjectName(QString::fromUtf8("AddBtn"));

        horizontalLayout->addWidget(AddBtn);

        ModifyBtn = new QPushButton(widget);
        ModifyBtn->setObjectName(QString::fromUtf8("ModifyBtn"));

        horizontalLayout->addWidget(ModifyBtn);

        deleteBtn = new QPushButton(widget);
        deleteBtn->setObjectName(QString::fromUtf8("deleteBtn"));

        horizontalLayout->addWidget(deleteBtn);

        clearBtn = new QPushButton(widget);
        clearBtn->setObjectName(QString::fromUtf8("clearBtn"));

        horizontalLayout->addWidget(clearBtn);


        verticalLayout->addWidget(widget);


        retranslateUi(viewLib);

        QMetaObject::connectSlotsByName(viewLib);
    } // setupUi

    void retranslateUi(QDialog *viewLib)
    {
        viewLib->setWindowTitle(QCoreApplication::translate("viewLib", "\350\257\215\345\272\223", nullptr));
        label->setText(QCoreApplication::translate("viewLib", "\350\257\215\345\272\223\347\256\241\347\220\206", nullptr));
        personalL->setText(QCoreApplication::translate("viewLib", "\344\270\252\344\272\272\350\257\215\345\272\223", nullptr));
        wrongL->setText(QCoreApplication::translate("viewLib", "\351\224\231\350\257\215\345\272\223", nullptr));
        defaultL->setText(QCoreApplication::translate("viewLib", "\347\263\273\347\273\237\350\257\215\345\272\223", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("viewLib", "\345\215\225\350\257\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("viewLib", "\350\257\215\346\200\247", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("viewLib", "\351\207\212\344\271\211", nullptr));
        AddBtn->setText(QCoreApplication::translate("viewLib", "\346\226\260\345\242\236", nullptr));
        ModifyBtn->setText(QCoreApplication::translate("viewLib", "\344\277\256\346\224\271", nullptr));
        deleteBtn->setText(QCoreApplication::translate("viewLib", "\345\210\240\351\231\244", nullptr));
        clearBtn->setText(QCoreApplication::translate("viewLib", "\346\270\205\347\251\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class viewLib: public Ui_viewLib {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWLIB_H
