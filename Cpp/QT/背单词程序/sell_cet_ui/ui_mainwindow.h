/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLogin;
    QAction *actionRegister;
    QAction *actionInsert;
    QAction *actionHelp;
    QAction *actionAbout;
    QAction *actionLevel;
    QAction *actionScore;
    QAction *actionSignup;
    QAction *actionName;
    QAction *actionExit;
    QAction *actionchoiceModel;
    QAction *actionspellingModel;
    QAction *actionmodelComment;
    QAction *actionpersonalWordLib;
    QAction *actionwrongWordLib;
    QAction *actiondefLearn;
    QAction *actioncheck;
    QAction *actionconfirmexit;
    QAction *actionmodify;
    QAction *actiondelete;
    QAction *actionsuperadd;
    QAction *actionaddLib;
    QAction *actionprofile;
    QAction *actionexplorer;
    QAction *actionLearn;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_2;
    QWidget *widget;
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *horizontalSpacer_2;
    QLabel *CourageName;
    QLabel *courageLabel;
    QLabel *CourageText;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QWidget *widget_2;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer_4;
    QPushButton *loginBtn;
    QPushButton *checkBtn;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *verticalSpacer_6;
    QMenuBar *menubar;
    QMenu *user;
    QMenu *exitlogin;
    QMenu *wordlib;
    QMenu *menu_5;
    QMenu *start;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 480);
        MainWindow->setMinimumSize(QSize(800, 480));
        MainWindow->setMaximumSize(QSize(800, 617));
        actionLogin = new QAction(MainWindow);
        actionLogin->setObjectName(QString::fromUtf8("actionLogin"));
        actionRegister = new QAction(MainWindow);
        actionRegister->setObjectName(QString::fromUtf8("actionRegister"));
        actionInsert = new QAction(MainWindow);
        actionInsert->setObjectName(QString::fromUtf8("actionInsert"));
        actionHelp = new QAction(MainWindow);
        actionHelp->setObjectName(QString::fromUtf8("actionHelp"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionLevel = new QAction(MainWindow);
        actionLevel->setObjectName(QString::fromUtf8("actionLevel"));
        actionScore = new QAction(MainWindow);
        actionScore->setObjectName(QString::fromUtf8("actionScore"));
        actionSignup = new QAction(MainWindow);
        actionSignup->setObjectName(QString::fromUtf8("actionSignup"));
        actionName = new QAction(MainWindow);
        actionName->setObjectName(QString::fromUtf8("actionName"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionchoiceModel = new QAction(MainWindow);
        actionchoiceModel->setObjectName(QString::fromUtf8("actionchoiceModel"));
        actionspellingModel = new QAction(MainWindow);
        actionspellingModel->setObjectName(QString::fromUtf8("actionspellingModel"));
        actionmodelComment = new QAction(MainWindow);
        actionmodelComment->setObjectName(QString::fromUtf8("actionmodelComment"));
        actionpersonalWordLib = new QAction(MainWindow);
        actionpersonalWordLib->setObjectName(QString::fromUtf8("actionpersonalWordLib"));
        actionwrongWordLib = new QAction(MainWindow);
        actionwrongWordLib->setObjectName(QString::fromUtf8("actionwrongWordLib"));
        actiondefLearn = new QAction(MainWindow);
        actiondefLearn->setObjectName(QString::fromUtf8("actiondefLearn"));
        actioncheck = new QAction(MainWindow);
        actioncheck->setObjectName(QString::fromUtf8("actioncheck"));
        actionconfirmexit = new QAction(MainWindow);
        actionconfirmexit->setObjectName(QString::fromUtf8("actionconfirmexit"));
        actionmodify = new QAction(MainWindow);
        actionmodify->setObjectName(QString::fromUtf8("actionmodify"));
        actiondelete = new QAction(MainWindow);
        actiondelete->setObjectName(QString::fromUtf8("actiondelete"));
        actionsuperadd = new QAction(MainWindow);
        actionsuperadd->setObjectName(QString::fromUtf8("actionsuperadd"));
        actionaddLib = new QAction(MainWindow);
        actionaddLib->setObjectName(QString::fromUtf8("actionaddLib"));
        actionprofile = new QAction(MainWindow);
        actionprofile->setObjectName(QString::fromUtf8("actionprofile"));
        actionexplorer = new QAction(MainWindow);
        actionexplorer->setObjectName(QString::fromUtf8("actionexplorer"));
        actionLearn = new QAction(MainWindow);
        actionLearn->setObjectName(QString::fromUtf8("actionLearn"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        centralwidget->setLayoutDirection(Qt::LeftToRight);
        centralwidget->setStyleSheet(QString::fromUtf8("background-color: rgb(234, 234, 234);\n"
"border-color: rgba(255, 255, 255, 0);"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        widget = new QWidget(frame);
        widget->setObjectName(QString::fromUtf8("widget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy1);
        widget->setMaximumSize(QSize(750, 16777215));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_3, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 3, 2, 1, 1);

        CourageName = new QLabel(widget);
        CourageName->setObjectName(QString::fromUtf8("CourageName"));
        CourageName->setStyleSheet(QString::fromUtf8("color: rgb(140, 140, 140);"));
        CourageName->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(CourageName, 4, 1, 1, 1);

        courageLabel = new QLabel(widget);
        courageLabel->setObjectName(QString::fromUtf8("courageLabel"));
        QFont font;
        font.setPointSize(11);
        font.setItalic(true);
        courageLabel->setFont(font);
        courageLabel->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        courageLabel->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(courageLabel, 3, 1, 1, 1);

        CourageText = new QLabel(widget);
        CourageText->setObjectName(QString::fromUtf8("CourageText"));
        QFont font1;
        font1.setPointSize(18);
        font1.setBold(true);
        CourageText->setFont(font1);
        CourageText->setStyleSheet(QString::fromUtf8("color: rgb(0, 8, 164);"));
        CourageText->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(CourageText, 2, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 3, 0, 1, 1);


        verticalLayout_2->addWidget(widget);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        widget_2 = new QWidget(frame);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setMinimumSize(QSize(750, 0));
        widget_2->setMaximumSize(QSize(750, 16777215));
        gridLayout = new QGridLayout(widget_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_4, 3, 0, 1, 1);

        loginBtn = new QPushButton(widget_2);
        loginBtn->setObjectName(QString::fromUtf8("loginBtn"));
        loginBtn->setMinimumSize(QSize(0, 100));
        QFont font2;
        font2.setPointSize(24);
        font2.setBold(true);
        loginBtn->setFont(font2);
        loginBtn->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"color: rgb(27, 45, 151);\n"
"background-color: rgb(255, 255, 255);"));

        gridLayout->addWidget(loginBtn, 1, 2, 1, 1);

        checkBtn = new QPushButton(widget_2);
        checkBtn->setObjectName(QString::fromUtf8("checkBtn"));
        checkBtn->setMinimumSize(QSize(0, 100));
        checkBtn->setMaximumSize(QSize(16777215, 100));
        QFont font3;
        font3.setPointSize(24);
        font3.setBold(true);
        font3.setUnderline(false);
        checkBtn->setFont(font3);
        checkBtn->setCursor(QCursor(Qt::ArrowCursor));
        checkBtn->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"color: rgb(27, 45, 151);\n"
"background-color: rgb(255, 255, 255);"));
        checkBtn->setIconSize(QSize(32, 32));

        gridLayout->addWidget(checkBtn, 1, 0, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_5, 3, 2, 1, 1);


        verticalLayout_2->addWidget(widget_2);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_6);


        verticalLayout->addWidget(frame);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 24));
        user = new QMenu(menubar);
        user->setObjectName(QString::fromUtf8("user"));
        exitlogin = new QMenu(user);
        exitlogin->setObjectName(QString::fromUtf8("exitlogin"));
        wordlib = new QMenu(menubar);
        wordlib->setObjectName(QString::fromUtf8("wordlib"));
        menu_5 = new QMenu(menubar);
        menu_5->setObjectName(QString::fromUtf8("menu_5"));
        start = new QMenu(menu_5);
        start->setObjectName(QString::fromUtf8("start"));
        MainWindow->setMenuBar(menubar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menubar->addAction(menu_5->menuAction());
        menubar->addAction(user->menuAction());
        menubar->addAction(wordlib->menuAction());
        user->addAction(actionLogin);
        user->addAction(actionRegister);
        user->addAction(exitlogin->menuAction());
        user->addSeparator();
        user->addAction(actionprofile);
        exitlogin->addAction(actioncheck);
        exitlogin->addAction(actionconfirmexit);
        wordlib->addAction(actionexplorer);
        wordlib->addSeparator();
        menu_5->addAction(start->menuAction());
        menu_5->addAction(actionLearn);
        menu_5->addSeparator();
        menu_5->addAction(actionExit);
        start->addAction(actionspellingModel);
        start->addSeparator();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\350\203\214\350\203\214\345\215\225\350\257\215", nullptr));
        actionLogin->setText(QCoreApplication::translate("MainWindow", "\347\231\273\345\275\225", nullptr));
        actionRegister->setText(QCoreApplication::translate("MainWindow", "\346\263\250\345\206\214", nullptr));
        actionInsert->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\346\226\260\350\257\215", nullptr));
        actionHelp->setText(QCoreApplication::translate("MainWindow", "\345\270\256\345\212\251", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "\345\205\263\344\272\216", nullptr));
        actionLevel->setText(QCoreApplication::translate("MainWindow", "\347\255\211\347\272\247", nullptr));
        actionScore->setText(QCoreApplication::translate("MainWindow", "\345\210\206\346\225\260", nullptr));
        actionSignup->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\215\241\345\244\251\346\225\260", nullptr));
        actionName->setText(QCoreApplication::translate("MainWindow", "\345\220\215\347\247\260", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272\350\275\257\344\273\266", nullptr));
        actionchoiceModel->setText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\351\242\230\346\250\241\345\274\217", nullptr));
        actionspellingModel->setText(QCoreApplication::translate("MainWindow", "\346\213\274\345\206\231\346\250\241\345\274\217", nullptr));
        actionmodelComment->setText(QCoreApplication::translate("MainWindow", "\346\250\241\345\274\217\350\257\264\346\230\216", nullptr));
        actionpersonalWordLib->setText(QCoreApplication::translate("MainWindow", "\344\270\252\344\272\272\350\257\215\345\272\223", nullptr));
        actionwrongWordLib->setText(QCoreApplication::translate("MainWindow", "\351\224\231\350\257\215\350\257\215\345\272\223", nullptr));
        actiondefLearn->setText(QCoreApplication::translate("MainWindow", "\351\273\230\350\256\244\350\257\215\345\272\223", nullptr));
        actioncheck->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\215\241", nullptr));
        actionconfirmexit->setText(QCoreApplication::translate("MainWindow", "\347\241\256\350\256\244\351\200\200\345\207\272", nullptr));
        actionmodify->setText(QCoreApplication::translate("MainWindow", "\344\277\256\346\224\271", nullptr));
        actiondelete->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244", nullptr));
        actionsuperadd->setText(QCoreApplication::translate("MainWindow", "\350\241\245\345\205\205", nullptr));
        actionaddLib->setText(QCoreApplication::translate("MainWindow", "\350\257\215\345\272\223\345\257\274\345\205\245", nullptr));
        actionprofile->setText(QCoreApplication::translate("MainWindow", "\347\224\250\346\210\267\344\277\241\346\201\257", nullptr));
        actionexplorer->setText(QCoreApplication::translate("MainWindow", "\350\257\215\345\272\223\347\256\241\347\220\206", nullptr));
        actionLearn->setText(QCoreApplication::translate("MainWindow", "\345\215\225\350\257\215\345\255\246\344\271\240", nullptr));
        CourageName->setText(QCoreApplication::translate("MainWindow", "Stephen Hawking", nullptr));
        courageLabel->setText(QCoreApplication::translate("MainWindow", "we only have to look at ourselves to see how intelligent life might develop into something we wouldn't want to mee.", nullptr));
        CourageText->setText(QCoreApplication::translate("MainWindow", "\346\234\252\347\231\273\345\275\225", nullptr));
        loginBtn->setText(QCoreApplication::translate("MainWindow", "\347\231\273\345\275\225", nullptr));
        checkBtn->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\215\241", nullptr));
        user->setTitle(QCoreApplication::translate("MainWindow", "\347\224\250\346\210\267", nullptr));
        exitlogin->setTitle(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272\347\231\273\345\275\225", nullptr));
        wordlib->setTitle(QCoreApplication::translate("MainWindow", "\345\215\225\350\257\215\346\234\254", nullptr));
        menu_5->setTitle(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213", nullptr));
        start->setTitle(QCoreApplication::translate("MainWindow", "\345\215\225\350\257\215\350\203\214\350\257\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
