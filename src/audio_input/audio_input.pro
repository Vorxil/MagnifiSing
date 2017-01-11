QT += core multimedia
QT -= gui

CONFIG += c++11

TARGET = audioinput
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    audioinput.cpp \
    cepsdwt.cpp

HEADERS += \
    audioinput.h \
    pitchfreqdetector.h \
    cepsdwt.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/'../../../../../../../../Program Files (x86)/Aquila/lib/' -lAquila -looura
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/'../../../../../../../../Program Files (x86)/Aquila/lib/' -lAquila -looura
else:unix: LIBS += -L$$PWD/'../../../../../../../../Program Files (x86)/Aquila/lib/' -lAquila -looura

INCLUDEPATH += $$PWD/'../../../../../../../../Program Files (x86)/Aquila/include'
DEPENDPATH += $$PWD/'../../../../../../../../Program Files (x86)/Aquila/include'
