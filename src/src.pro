######################################################################
# Automatically generated by qmake (3.0) ons jan. 11 20:55:27 2017
######################################################################

QT       += core gui multimedia sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
TARGET = magnifising
INCLUDEPATH += .

unix:QMAKE_CXXFLAGS += -std=c++0x

# Input
HEADERS += helpview.h \
           mainmenuview.h \
           mainwindow.h \
           midiview.h \
           singingview.h \
           singingviewcontroller.h \
           startsingingview.h \
           database.h \
           aquila/aquila.h \
           aquila/Exceptions.h \
           aquila/filter.h \
           aquila/functions.h \
           aquila/global.h \
           aquila/ml.h \
           aquila/source.h \
           aquila/tools.h \
           aquila/transform.h \
           audio_input/audioinput.h \
           audio_input/cepsdwt.h \
           audio_input/pitchfreqdetector.h \
           audio_input/lowpassfilter.h \
           midifile/Binasc.h \
           midifile/MidiEvent.h \
           midifile/MidiEventList.h \
           midifile/MidiFile.h \
           midifile/MidiMessage.h \
           midifile/Options.h \
           aquila/filter/MelFilter.h \
           aquila/filter/MelFilterBank.h \
           aquila/ml/Dtw.h \
           aquila/ml/DtwPoint.h \
           aquila/source/Frame.h \
           aquila/source/FramesCollection.h \
           aquila/source/PlainTextFile.h \
           aquila/source/RawPcmFile.h \
           aquila/source/SignalSource.h \
           aquila/source/WaveFile.h \
           aquila/source/WaveFileHandler.h \
           aquila/tools/TextPlot.h \
           aquila/transform/AquilaFft.h \
           aquila/transform/Dct.h \
           aquila/transform/Dft.h \
           aquila/transform/Fft.h \
           aquila/transform/FftFactory.h \
           aquila/transform/Mfcc.h \
           aquila/transform/OouraFft.h \
           aquila/transform/Spectrogram.h \
           aquila/source/generator/Generator.h \
           aquila/source/generator/PinkNoiseGenerator.h \
           aquila/source/generator/SineGenerator.h \
           aquila/source/generator/SquareGenerator.h \
           aquila/source/generator/TriangleGenerator.h \
           aquila/source/generator/WhiteNoiseGenerator.h \
           aquila/source/window/BarlettWindow.h \
           aquila/source/window/BlackmanWindow.h \
           aquila/source/window/FlattopWindow.h \
           aquila/source/window/GaussianWindow.h \
           aquila/source/window/HammingWindow.h \
           aquila/source/window/HannWindow.h \
           aquila/source/window/RectangularWindow.h \
    manageuser.h \
    adduser.h \
    audio_input/hamminglpfilter.h \
    audio_input/pitchpipeline.h

FORMS += helpview.ui \
         mainmenuview.ui \
         mainwindow.ui \
         midiview.ui \
         singingview.ui \
         startsingingview.ui \
    manageuser.ui \
    adduser.ui
SOURCES += helpview.cpp \
           main.cpp \
           mainmenuview.cpp \
           mainwindow.cpp \
           midiview.cpp \
           singingview.cpp \
           singingviewcontroller.cpp \
           startsingingview.cpp \
           database.cpp \
           audio_input/audioinput.cpp \
           audio_input/cepsdwt.cpp \
           audio_input/lowpassfilter.cpp \
           midifile/Binasc.cpp \
           midifile/MidiEvent.cpp \
           midifile/MidiEventList.cpp \
           midifile/MidiFile.cpp \
           midifile/MidiMessage.cpp \
           midifile/Options.cpp \
           ooura/fft4g.c \
           aquila/filter/MelFilter.cpp \
           aquila/filter/MelFilterBank.cpp \
           aquila/ml/Dtw.cpp \
           aquila/source/Frame.cpp \
           aquila/source/FramesCollection.cpp \
           aquila/source/PlainTextFile.cpp \
           aquila/source/SignalSource.cpp \
           aquila/source/WaveFile.cpp \
           aquila/source/WaveFileHandler.cpp \
           aquila/tools/TextPlot.cpp \
           aquila/transform/AquilaFft.cpp \
           aquila/transform/Dct.cpp \
           aquila/transform/Dft.cpp \
           aquila/transform/FftFactory.cpp \
           aquila/transform/Mfcc.cpp \
           aquila/transform/OouraFft.cpp \
           aquila/transform/Spectrogram.cpp \
           aquila/source/generator/Generator.cpp \
           aquila/source/generator/PinkNoiseGenerator.cpp \
           aquila/source/generator/SineGenerator.cpp \
           aquila/source/generator/SquareGenerator.cpp \
           aquila/source/generator/TriangleGenerator.cpp \
           aquila/source/generator/WhiteNoiseGenerator.cpp \
           aquila/source/window/BarlettWindow.cpp \
           aquila/source/window/BlackmanWindow.cpp \
           aquila/source/window/FlattopWindow.cpp \
           aquila/source/window/GaussianWindow.cpp \
           aquila/source/window/HammingWindow.cpp \
           aquila/source/window/HannWindow.cpp \
    manageuser.cpp \
    adduser.cpp \
    audio_input/hamminglpfilter.cpp \
    audio_input/pitchpipeline.cpp

RESOURCES += \
    resource.qrc
