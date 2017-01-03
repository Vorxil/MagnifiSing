#include "singingviewcontroller.h"
#include "singingview.h"
#include "midiview.h"
#include <QObject>
#include <QTime>
#include <QTimer>
#include "../audio_input/audioinput.h"
#include "../audio_input/cepsdwt.h"
#include <QDebug>
#include "midiview.h"
#include "singingview.h"


#define fs 8000


cepsDWT cepsdwt(1024,4);
QTime m_time;
int total_time;
QTimer *timer;
SingingView *singView;


SingingViewController::SingingViewController(SingingView* singingView)
{
    singView = singingView;
    midiView = singingView->getMidiView();
    midiView->setToneInterval(-36,36);

    audioInput = new audioinput();
    connect(audioInput,SIGNAL(readyRead()),this,SLOT(readSamples()));
    connect(singingView,SIGNAL(playButtonClicked()),this,SLOT(play_pause()));
    connect(singingView,SIGNAL(menuButtonClicked()),this,SLOT(play_pause()));

    /* Update MIDI view every updateInterval milliseconds */
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateMidiView()));

}

SingingViewController::~SingingViewController(){
    delete audioInput;
}

void SingingViewController::readSamples(){
    samples = audioInput->readMore();
    frequency = cepsdwt.detectPitchFrequency(samples,fs);

    qDebug() << "\nFrequency: " << frequency;

}

void SingingViewController::updateMidiView(){
    midiView->addCorrectFrequency(frequency,m_time.elapsed()+total_time);
}

void SingingViewController::play_pause(){
    if(timer->isActive()){
        timer->stop();
        total_time += m_time.elapsed();
        singView->setPlayPauseButtonText("Play");
    }else{
        timer->start(updateInterval);
        m_time.restart();
        singView->setPlayPauseButtonText("Pause");
    }
}
