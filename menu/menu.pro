#-------------------------------------------------
#
# Project created by QtCreator 2016-10-18T17:20:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = menu
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mainmenuview.cpp \
    startsingingview.cpp \
    helpview.cpp

HEADERS  += mainwindow.h \
    mainmenuview.h \
    startsingingview.h \
    helpview.h

FORMS    += mainwindow.ui \
    mainmenuview.ui \
    startsingingview.ui \
    helpview.ui
