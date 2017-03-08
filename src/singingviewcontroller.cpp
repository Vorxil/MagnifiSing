
#include "iostream"
#include "stdlib.h"
#include "singingviewcontroller.h"
#include "singingview.h"
#include "midiview.h"
#include <QObject>
#include <QTime>
#include <QTimer>
#include <QStringList>
#include "audio_input/audioinput.h"
#include "audio_input/cepsdwt.h"
#include <QDebug>
#include "midiview.h"
#include "singingview.h"
#include "startsingingview.h"
#include "midifile/MidiFile.h"

/* Constants used in conversion from frequency to semitones */
const double const1 = 3/log(2);
const double const2 = log(4685120000L);

const double passband = 2000;
const double transband = 500;
const double fs = 48000;
const int downFactor = 8;
const int dwtLevels = 7;
const double silence = 30;
const double peak = 0.05;

cepsDWT cepsdwt(RETURN_SIZE,dwtLevels,silence,peak);

QTime m_time;
int total_time;
QTimer *timer;
SingingView *singView;
StartSingingView *startsingingView;

MidiFile midiFile;
int currentMidiToneEvent;
int currentMidiTextEvent;
int toneEventsNumber;
int textEventsNumber;
int toneTrack;
int textTrack;
int toneTrackEnded;
int textTrackEnded;
int keyNumber;
int midiTone;
QString midiText;
int sungTone;
int oldMidiTones[windowWidth/(2*updateInterval)];
int midiIndex;

int correctTonesCount;
int totalTonesCount;



SingingViewController::SingingViewController(SingingView* singingView, StartSingingView* ssView)
{
    singView = singingView;
    startsingingView = ssView;
    midiView = singingView->getMidiView();
    midiView->setToneInterval(-24,24);

    singingView->setSilentThresholdSlider(cepsdwt.getSilentThreshold());

    audioInput = new audioinput();
    connect(audioInput,SIGNAL(readyRead()),this,SLOT(readSamples()));
    connect(singingView,SIGNAL(playButtonClicked()),this,SLOT(play_pause()));
    connect(singingView,SIGNAL(menuButtonClicked()),this,SLOT(stop()));
    connect(singingView,SIGNAL(stopButtonClicked()),this,SLOT(stop()));
    connect(singingView,SIGNAL(backButtonClicked()),this,SLOT(stop()));
    connect(singingView,SIGNAL(silentThresholdSliderMoved(int)),this,SLOT(setSilentThreshold(int)));
    connect(startsingingView,SIGNAL(loadFileButtonClicked(QString)),this,SLOT(updateMidiFile(QString)));
    connect(startsingingView,SIGNAL(textTrackComboBoxIndexChanged(int)),this,SLOT(setTextTrack(int)));
    connect(startsingingView,SIGNAL(toneTrackComboBoxIndexChanged(int)),this,SLOT(setToneTrack(int)));


    /* Update MIDI view every updateInterval milliseconds */
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateMidiView()));

}

SingingViewController::~SingingViewController(){
    delete audioInput;
}

void SingingViewController::readSamples(){
    samples = audioInput->readMore();
    if ( samples != 0 ) {
        frequency = cepsdwt.detectPitchFrequency(samples,SAMPLE_RATE);
//        qDebug() << "\nFrequency: " << frequency;
    }
}



/* MIDI file key representation
 * middle C = 60
 * Scientific pitch = midikeynumber - 60
 */

void SingingViewController::updateMidiView(){
    /* Add lyrics from midi file to midiview */
    /* Find next text event */
    if(!textTrackEnded){
        while((currentMidiTextEvent < textEventsNumber-1) &&((midiFile.getEvent(textTrack,currentMidiTextEvent).getP1() > 7) ||
              (int)(midiFile.getTimeInSeconds(textTrack,currentMidiTextEvent)*1000) < (m_time.elapsed()+total_time+windowWidth/2-updateInterval))){
            currentMidiTextEvent++;
        }
        /* Add the text if it is within the current time limit(depends on time resolution in midiview) */
        if((int)(midiFile.getTimeInSeconds(textTrack,currentMidiTextEvent)*1000) <= (m_time.elapsed() + total_time + windowWidth/2 +updateInterval)){
            midiText = "";
            for(int i = 0;i<midiFile.getEvent(textTrack,currentMidiTextEvent).getP2();i++){
                char ascii = midiFile.getEvent(textTrack,currentMidiTextEvent)[i+3];
                midiText.append(ascii);
            }
            midiView->addLyrics(midiText);
            currentMidiTextEvent++;
        }else{
            midiView->addLyrics("");
        }
    }else{
         midiView->addLyrics("");
    }

    /* Add tone from midi file to midiview */
    /* find next note */
    if(!toneTrackEnded){
        while((currentMidiToneEvent < toneEventsNumber-1) &&(!midiFile.getEvent(toneTrack,currentMidiToneEvent).isNoteOn() ||
              (int)((midiFile.getTimeInSeconds(toneTrack,currentMidiToneEvent) + midiFile.getEvent(toneTrack,currentMidiToneEvent).getDurationInSeconds())*1000) < (m_time.elapsed()+total_time+windowWidth/2))){
            currentMidiToneEvent++;
        }

        /* Add the tone if it is within the current time limit(depends on time resolution in midiview) */
        if((int)(midiFile.getTimeInSeconds(toneTrack,currentMidiToneEvent)*1000) <= (m_time.elapsed() + total_time+windowWidth/2)){
            keyNumber = midiFile.getEvent(toneTrack,currentMidiToneEvent).getKeyNumber();
            midiTone = keyNumber-60;
        }else{
            midiTone = -500;
        }
    }else{
        midiTone = -500;
    }

    oldMidiTones[midiIndex] = midiTone;
    midiIndex = (midiIndex+1) % (windowWidth/(2*updateInterval));

    midiView->addMidiTone(midiTone);
    midiView->setCurrentTime(m_time.elapsed()+total_time);


    /* Add correct sung pitch to midiview */
    int sungTone = freqToSemitone(frequency);
    if(abs(oldMidiTones[midiIndex %(windowWidth/(2*updateInterval))]-sungTone)<2){
        midiView->addCorrectTone(sungTone);
        midiView->addWrongTone(-500);

        totalTonesCount++;
        correctTonesCount++;
        midiView->setCurrentScore(correctTonesCount);
        midiView->setTotalTones(totalTonesCount);
    }else{
        /* Add wrong tone to midiview */
        midiView->setTotalTones(totalTonesCount);
        midiView->addCorrectTone(-500);
        midiView->addWrongTone(sungTone);

        if(oldMidiTones[midiIndex %(windowWidth/(2*updateInterval))] > -60 || sungTone > -60){
            totalTonesCount++;
        }
    }

    /* Stop if reaches end of midi track */
    if(total_time + m_time.elapsed() >= midiFile.getTotalTimeInSeconds()*1000 + windowWidth/2){
        stop();
    }
    if(currentMidiToneEvent >= toneEventsNumber-1){
        toneTrackEnded = 1;
    }
    if(currentMidiTextEvent >= textEventsNumber-1){
        textTrackEnded = 1;
    }

    /* Repeat part of the midi file if repeat button toggled*/
    if(singView->repeatButtonChecked()){
        if(total_time + m_time.elapsed() >= singView->getRepeatEnd()*1000){
            total_time = singView->getRepeatStart()*1000;

            currentMidiToneEvent = 0;
            currentMidiTextEvent = 0;
            m_time.restart();

        }
    }

}

int SingingViewController::freqToSemitone(double frequency){
    return (int)round(const1*(4*log(frequency)-const2));
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

void SingingViewController::stop(){
    timer->stop();
    total_time = 0;
    currentMidiToneEvent = 0;
    currentMidiTextEvent = 0;
    textTrackEnded = 0;
    toneTrackEnded = 0;
    midiView->setCurrentTime(0);
    singView->setPlayPauseButtonText("Play");
    for(int i=0;i<2*windowWidth/(updateInterval);i++){
        midiView->addMidiTone(-500);
        midiView->addLyrics("");
    }
    for(int i=0;i<windowWidth/(2*updateInterval);i++){
        midiView->addCorrectTone(-500);
        midiView->addWrongTone(-500);
    }

    correctTonesCount = 0;
    totalTonesCount = 0;
    midiView->setCurrentScore(correctTonesCount);
    midiView->setTotalTones(totalTonesCount);
}

void SingingViewController::updateMidiFile(QString filepath){
    int midiRead = setMidiFile(filepath);
    setTextTrack(0);
    setToneTrack(0);
    if(midiRead){
        midiFile.linkNotePairs();
        midiFile.sortTracks();
        midiFile.doTimeAnalysis();
        qDebug() << "Midi imported successfully";

        startsingingView->setTextTrackComboBox(midiFile.getTrackCount(), getTrackNames(), getTrack_MaxTextEvents());
        startsingingView->setToneTrackComboBox(midiFile.getTrackCount(), getTrackNames());
        startsingingView->setContinueButtonEnabled(1);
        startsingingView->setMidiTextAreaText(getMidiTextAsString(midiFile));

        singView->setRepeatMaximumSeconds(midiFile.getTotalTimeInSeconds());
    }else{
        qDebug() << "Error in midi import";
        startsingingView->setContinueButtonEnabled(0);
    }
}
int SingingViewController::setMidiFile(QString filepath){
    return midiFile.read(filepath.toStdString());
}

void SingingViewController::setToneTrack(int track){
    toneTrack = track;
    currentMidiToneEvent = 0;
    if(toneTrack < midiFile.getTrackCount()){
        toneEventsNumber = midiFile.getEventCount(toneTrack);
    }
}

void SingingViewController::setTextTrack(int track){
    textTrack = track;
    currentMidiTextEvent = 0;
    if(textTrack < midiFile.getTrackCount()){
        textEventsNumber = midiFile.getEventCount(textTrack);
    }
}

QString SingingViewController::getMidiTextAsString(MidiFile midifile){
    QString s;
    s += midiFile.getFilename();
    s += "\nDuration: ";
    s += QString::number(midiFile.getTotalTimeInSeconds());
    s += " sec";
    s += "\nTracks: ";
    s += QString::number(midiFile.getTrackCount());
    s += "\n\nText events:";
    for(int t=0;t<midiFile.getTrackCount();t++){
        for(int e=0; e<midiFile.getEventCount(t);e++){
            if(midiFile.getEvent(t,e).isMeta() && midiFile.getEvent(t,e)[1] <= 7){
                s += "\nTrack ";
                s += QString::number(t);
                s += ", Time: ";
                s += QString::number(midiFile.getTimeInSeconds(t,e));
                s += " ";
                for(int i = 0;i<midiFile.getEvent(t,e).getP2();i++){
                    char ascii = midiFile.getEvent(t,e)[i+3];
                    s += ascii;
                }
            }
        }
    }
    return s;
}

int SingingViewController::getTrack_MaxTextEvents(){

    int track = 0;
    int currentTextEventCount = 0;
    int prevTextEventCount = 0;

    for(int t=0;t<midiFile.getTrackCount();t++){

        /* Calculate number of text events */
        currentTextEventCount = 0;
        for(int e=0; e<midiFile.getEventCount(t); e++){
            if(midiFile.getEvent(t,e).isMeta() && midiFile.getEvent(t,e)[1] <= 7){
                currentTextEventCount++;
            }
        }
        /* Compare to previous tracks */
        if(prevTextEventCount < currentTextEventCount){
            track = t;
            prevTextEventCount = currentTextEventCount;
        }
    }
    return track;
}

QStringList SingingViewController::getTrackNames(){
    QStringList trackList;
    for(int t=0;t<midiFile.getTrackCount(); t++){
        QString track = QString::number(t);
        for(int e=0; e<midiFile.getEventCount(t); e++){
            if(midiFile.getEvent(t,e).isMeta() && midiFile.getEvent(t,e)[1] == 3){
                track += " ";
                for(int i = 0;i<midiFile.getEvent(t,e).getP2();i++){
                    char ascii = midiFile.getEvent(t,e)[i+3];
                    track += ascii;
                }
                break;
            }
        }
        trackList << track;
    }
    return trackList;
}

void SingingViewController::setSilentThreshold(int threshold){
    cepsdwt.setSilentThreshold(threshold);
}
