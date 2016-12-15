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
#define updateInterval 40


cepsDWT cepsdwt(1024,4);
QTime m_time;


SingingViewController::SingingViewController(SingingView* singingView)
{
    midiView = singingView->getMidiView();
    midiView->setToneInterval(0,1000);

    audioInput = new audioinput();
    connect(audioInput,SIGNAL(readyRead()),this,SLOT(readSamples()));

    /* Update MIDI view every updateInterval milliseconds */
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateMidiView()));
    timer->start(updateInterval);


    /* Measure elapsed time */
    m_time.start();

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
    if(frequency != 0){
        midiView->addCorrectTone(int(frequency),m_time.elapsed(),updateInterval);
    }
}
