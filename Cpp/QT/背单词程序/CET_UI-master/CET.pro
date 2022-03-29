QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 force_debug_info release

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    choosegame.cpp \
    main.cpp \
    mainwindow.cpp\
    addword.cpp\
    choicemodel.cpp\
    login.cpp\
    profile.cpp\
    spellinggame.cpp \
    user.cpp\
    spelingmodel.cpp\
    viewlib.cpp \
    word.cpp \

HEADERS += \
    addword.h \
    choicemodel.h \
    choosegame.h \
    currentDTO.h \
    login.h \
    mainwindow.h \
    profile.h \
    spelingmodel.h \
    spellinggame.h \
    user.h \
    viewlib.h \
    word.h

FORMS += \
    choosegame.ui \
    mainwindow.ui\
    addword.ui\
    choicemodel.ui\
    login.ui\
    profile.ui\
    spelingmodel.ui \
    spellinggame.ui \
    viewlib.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    rs.qrc
