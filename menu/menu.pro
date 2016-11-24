#-------------------------------------------------
#
# Project created by QtCreator 2016-10-18T17:20:46
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = menu
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mainmenuview.cpp \
    startsingingview.cpp \
    helpview.cpp \
    midiview.cpp \
    singingview.cpp \
    singingviewcontroller.cpp \
    ../audio_input/audioinput.cpp \
    ../audio_input/cepsdwt.cpp

HEADERS  += mainwindow.h \
    mainmenuview.h \
    startsingingview.h \
    helpview.h \
    midiview.h \
    singingview.h \
    singingviewcontroller.h \
    ../audio_input/audioinput.h \
    ../audio_input/cepsdwt.h \
    ../audio_input/pitchfreqdetector.h

FORMS    += mainwindow.ui \
    mainmenuview.ui \
    startsingingview.ui \
    helpview.ui \
    midiview.ui \
    singingview.ui



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Aquila/build-aquila-src-Desktop_Qt_5_7_0_MinGW_32bit-Default/ -lAquila
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Aquila/build-aquila-src-Desktop_Qt_5_7_0_MinGW_32bit-Default/ -lAquila
else:unix: LIBS += -L$$PWD/../../Aquila/build-aquila-src-Desktop_Qt_5_7_0_MinGW_32bit-Default/ -lAquila

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Aquila/build-aquila-src-Desktop_Qt_5_7_0_MinGW_32bit-Default/lib/ -lOoura_fft
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Aquila/build-aquila-src-Desktop_Qt_5_7_0_MinGW_32bit-Default/lib/ -lOoura_fft
else:unix: LIBS += -L$$PWD/../../Aquila/build-aquila-src-Desktop_Qt_5_7_0_MinGW_32bit-Default/lib/ -lOoura_fft

INCLUDEPATH += $$PWD/../../Aquila/aquila-src
DEPENDPATH += $$PWD/../../Aquila/aquila-src

INCLUDEPATH += $$PWD/../../Aquila/build-aquila-src-Desktop_Qt_5_7_0_MinGW_32bit-Default
DEPENDPATH += $$PWD/../../Aquila/build-aquila-src-Desktop_Qt_5_7_0_MinGW_32bit-Default
