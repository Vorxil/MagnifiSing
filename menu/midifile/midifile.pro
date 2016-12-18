
# My first qt makefile

TEMPLATE = lib
DEFINES += midifile
INCLUDEPATH += .

QMAKE_CXXFLAGS += -std=c++0x

# Input
HEADERS += Binasc.h \
           MidiEvent.h \
           MidiEventList.h \
           MidiFile.h \
           MidiMessage.h \
           Options.h
SOURCES += Binasc.cpp \
           MidiEvent.cpp \
           MidiEventList.cpp \
           MidiFile.cpp \
           MidiMessage.cpp \
           Options.cpp
