QT       += core gui
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    global.cpp \
    insert.cpp \
    loaddialog.cpp \
    main.cpp \
    mainwindow.cpp \
    register.cpp \
    update.cpp

HEADERS += \
    global.h \
    insert.h \
    loaddialog.h \
    mainwindow.h \
    register.h \
    update.h

FORMS += \
    insert.ui \
    loaddialog.ui \
    mainwindow.ui \
    register.ui \
    update.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
