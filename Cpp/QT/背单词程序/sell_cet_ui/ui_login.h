/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_login_2
{
public:
    QVBoxLayout *verticalLayout;
    QStackedWidget *stackedWidget;
    QWidget *login;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_3;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLineEdit *LogUserI;
    QLabel *user;
    QLabel *password;
    QLineEdit *LogUserP;
    QLabel *info;
    QSpacerItem *verticalSpacer_2;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *LoginBtn;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *Btn_to_Reg;
    QWidget *reg;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_4;
    QWidget *widget_3;
    QGridLayout *gridLayout_2;
    QLineEdit *RegUserN;
    QLabel *label_4;
    QLineEdit *RegPass1;
    QLabel *label_3;
    QLabel *label_5;
    QLineEdit *RegPass2;
    QLabel *RegInfo;
    QSpacerItem *verticalSpacer;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *regBtn;
    QSpacerItem *horizontalSpacer_12;
    QPushButton *Btn_to_Log;

    void setupUi(QWidget *login_2)
    {
        if (login_2->objectName().isEmpty())
            login_2->setObjectName(QString::fromUtf8("login_2"));
        login_2->resize(350, 246);
        login_2->setMinimumSize(QSize(350, 240));
        login_2->setMaximumSize(QSize(350, 246));
        verticalLayout = new QVBoxLayout(login_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        stackedWidget = new QStackedWidget(login_2);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        login = new QWidget();
        login->setObjectName(QString::fromUtf8("login"));
        verticalLayout_2 = new QVBoxLayout(login);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_2->addItem(verticalSpacer_3);

        widget = new QWidget(login);
        widget->setObjectName(QString::fromUtf8("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        LogUserI = new QLineEdit(widget);
        LogUserI->setObjectName(QString::fromUtf8("LogUserI"));
        LogUserI->setMinimumSize(QSize(0, 30));

        gridLayout->addWidget(LogUserI, 0, 1, 1, 1);

        user = new QLabel(widget);
        user->setObjectName(QString::fromUtf8("user"));

        gridLayout->addWidget(user, 0, 0, 1, 1);

        password = new QLabel(widget);
        password->setObjectName(QString::fromUtf8("password"));

        gridLayout->addWidget(password, 1, 0, 1, 1);

        LogUserP = new QLineEdit(widget);
        LogUserP->setObjectName(QString::fromUtf8("LogUserP"));
        LogUserP->setMinimumSize(QSize(0, 30));
        LogUserP->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(LogUserP, 1, 1, 1, 1);


        verticalLayout_2->addWidget(widget);

        info = new QLabel(login);
        info->setObjectName(QString::fromUtf8("info"));
        QFont font;
        font.setPointSize(10);
        font.setBold(false);
        info->setFont(font);

        verticalLayout_2->addWidget(info);

        verticalSpacer_2 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        widget_2 = new QWidget(login);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        sizePolicy.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        LoginBtn = new QPushButton(widget_2);
        LoginBtn->setObjectName(QString::fromUtf8("LoginBtn"));

        horizontalLayout->addWidget(LoginBtn);

        horizontalSpacer_5 = new QSpacerItem(100, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        Btn_to_Reg = new QPushButton(widget_2);
        Btn_to_Reg->setObjectName(QString::fromUtf8("Btn_to_Reg"));

        horizontalLayout->addWidget(Btn_to_Reg);


        verticalLayout_2->addWidget(widget_2);

        stackedWidget->addWidget(login);
        reg = new QWidget();
        reg->setObjectName(QString::fromUtf8("reg"));
        verticalLayout_3 = new QVBoxLayout(reg);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalSpacer_4 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_4);

        widget_3 = new QWidget(reg);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        sizePolicy.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());
        widget_3->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(widget_3);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        RegUserN = new QLineEdit(widget_3);
        RegUserN->setObjectName(QString::fromUtf8("RegUserN"));
        RegUserN->setMinimumSize(QSize(0, 30));

        gridLayout_2->addWidget(RegUserN, 2, 2, 1, 1);

        label_4 = new QLabel(widget_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 3, 1, 1, 1);

        RegPass1 = new QLineEdit(widget_3);
        RegPass1->setObjectName(QString::fromUtf8("RegPass1"));
        RegPass1->setMinimumSize(QSize(0, 30));
        RegPass1->setEchoMode(QLineEdit::Password);

        gridLayout_2->addWidget(RegPass1, 3, 2, 1, 1);

        label_3 = new QLabel(widget_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 2, 1, 1, 1);

        label_5 = new QLabel(widget_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 4, 1, 1, 1);

        RegPass2 = new QLineEdit(widget_3);
        RegPass2->setObjectName(QString::fromUtf8("RegPass2"));
        RegPass2->setMinimumSize(QSize(0, 30));
        RegPass2->setEchoMode(QLineEdit::Password);

        gridLayout_2->addWidget(RegPass2, 4, 2, 1, 1);


        verticalLayout_3->addWidget(widget_3);

        RegInfo = new QLabel(reg);
        RegInfo->setObjectName(QString::fromUtf8("RegInfo"));

        verticalLayout_3->addWidget(RegInfo);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        widget_4 = new QWidget(reg);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        sizePolicy.setHeightForWidth(widget_4->sizePolicy().hasHeightForWidth());
        widget_4->setSizePolicy(sizePolicy);
        horizontalLayout_2 = new QHBoxLayout(widget_4);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        regBtn = new QPushButton(widget_4);
        regBtn->setObjectName(QString::fromUtf8("regBtn"));
        regBtn->setFlat(false);

        horizontalLayout_2->addWidget(regBtn);

        horizontalSpacer_12 = new QSpacerItem(100, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_12);

        Btn_to_Log = new QPushButton(widget_4);
        Btn_to_Log->setObjectName(QString::fromUtf8("Btn_to_Log"));

        horizontalLayout_2->addWidget(Btn_to_Log);


        verticalLayout_3->addWidget(widget_4);

        stackedWidget->addWidget(reg);

        verticalLayout->addWidget(stackedWidget);


        retranslateUi(login_2);

        stackedWidget->setCurrentIndex(1);
        LoginBtn->setDefault(true);
        regBtn->setDefault(true);


        QMetaObject::connectSlotsByName(login_2);
    } // setupUi

    void retranslateUi(QWidget *login_2)
    {
        login_2->setWindowTitle(QCoreApplication::translate("login_2", "Form", nullptr));
        LogUserI->setPlaceholderText(QCoreApplication::translate("login_2", "\350\257\267\350\276\223\345\205\245\347\224\250\346\210\267ID", nullptr));
        user->setText(QCoreApplication::translate("login_2", "\347\224\250\346\210\267ID:", nullptr));
        password->setText(QCoreApplication::translate("login_2", "\345\257\206\347\240\201:", nullptr));
        LogUserP->setPlaceholderText(QCoreApplication::translate("login_2", "\350\257\267\350\276\223\345\205\245\347\224\250\346\210\267\345\257\206\347\240\201", nullptr));
        info->setText(QString());
        LoginBtn->setText(QCoreApplication::translate("login_2", "\347\231\273\345\275\225", nullptr));
        Btn_to_Reg->setText(QCoreApplication::translate("login_2", "\346\263\250\345\206\214", nullptr));
        RegUserN->setPlaceholderText(QCoreApplication::translate("login_2", "\350\257\267\350\276\223\345\205\245\347\224\250\346\210\267\345\220\215", nullptr));
        label_4->setText(QCoreApplication::translate("login_2", "\345\257\206\347\240\201:", nullptr));
        RegPass1->setPlaceholderText(QCoreApplication::translate("login_2", "\350\257\267\350\276\223\345\205\245\345\257\206\347\240\201", nullptr));
        label_3->setText(QCoreApplication::translate("login_2", "\347\224\250\346\210\267\345\220\215:", nullptr));
        label_5->setText(QCoreApplication::translate("login_2", "\347\241\256\350\256\244\345\257\206\347\240\201:", nullptr));
        RegPass2->setPlaceholderText(QCoreApplication::translate("login_2", "\350\257\267\345\206\215\346\254\241\350\276\223\345\205\245\345\257\206\347\240\201", nullptr));
        RegInfo->setText(QString());
        regBtn->setText(QCoreApplication::translate("login_2", "\346\263\250\345\206\214", nullptr));
        Btn_to_Log->setText(QCoreApplication::translate("login_2", "\347\231\273\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class login_2: public Ui_login_2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
