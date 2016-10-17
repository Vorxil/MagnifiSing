QT += core multimedia
QT -= gui

CONFIG += c++11

TARGET = audioinput
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    audioinput.cpp

HEADERS += \
    audioinput.h
