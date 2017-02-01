
#include "iostream"
#include "stdlib.h"
#include "singingviewcontroller.h"
#include "singingview.h"
#include "midiview.h"
#include <QObject>
#include <QTime>
#include <QTimer>
#include "audio_input/audioinput.h"
#include "audio_input/cepsdwt.h"
#include <QDebug>
#include "midiview.h"
#include "singingview.h"
#include "midifile/MidiFile.h"

/* Constants used in conversion from frequency to semitones */
const double const1 = 3/log(2);
const double const2 = log(4685120000);


cepsDWT cepsdwt(RETURN_SIZE,6);
QTime m_time;
int total_time;
QTimer *timer;
SingingView *singView;

MidiFile midiFile;
int currentMidiEvent;
int eventsNumber;
int track;
int keyNumber;
int midiTone;
int sungTone;
int oldMidiTones[windowWidth/(2*updateInterval)];
int midiIndex;

int SingingViewController::freqToSemitone(double frequency){
    return (int)round(const1*(4*log(frequency)-const2));
}

SingingViewController::SingingViewController(SingingView* singingView)
{
    /* Import midi file */
    currentMidiEvent = 0;
    track = 3;
    midiFile.read("Strangers_in_the_Night.mid");
    midiFile.linkNotePairs();
    midiFile.sortTracks();
    midiFile.doTimeAnalysis();
    eventsNumber = midiFile.getEventCount(track);

    /* Print some info about the midi file */
    cout << "\n" << midiFile.getFilename();
    cout << "\nDuration: " << midiFile.getTotalTimeInSeconds() << " sec";
    cout << "\n\nText events";
    for(int t=0;t<midiFile.getTrackCount();t++){
        for(int e=0; e<midiFile.getEventCount(t);e++){
            if(midiFile.getEvent(t,e).isMeta() && midiFile.getEvent(t,e)[1] <= 7){
                cout << "\nTrack " << t << ", Time: " << midiFile.getTimeInSeconds(t,e) << " ";
                for(int i = 0;i<midiFile.getEvent(t,e).getP2();i++){
                    char ascii = midiFile.getEvent(t,e)[i+3];
                    cout << ascii;
                }
            }
            cout <<  std::flush;
        }
    }



    singView = singingView;
    midiView = singingView->getMidiView();
    midiView->setToneInterval(-24,24);

    audioInput = new audioinput();
    connect(audioInput,SIGNAL(readyRead()),this,SLOT(readSamples()));
    connect(singingView,SIGNAL(playButtonClicked()),this,SLOT(play_pause()));
    connect(singingView,SIGNAL(menuButtonClicked()),this,SLOT(play_pause()));
    connect(singingView,SIGNAL(stopButtonClicked()),this,SLOT(stop()));

    /* Update MIDI view every updateInterval milliseconds */
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateMidiView()));

}

SingingViewController::~SingingViewController(){
    delete audioInput;
}

void SingingViewController::readSamples(){
    samples = audioInput->readMore();
    frequency = cepsdwt.detectPitchFrequency(samples,SAMPLE_RATE);

    //qDebug() << "\nFrequency: " << frequency;

}



/* MIDI file key representation
 * middle C = 60
 * Scientific pitch = midikeynumber - 60
 */

void SingingViewController::updateMidiView(){
    /* Add tone from midi file to midiview */
    /* find next note */
    while((currentMidiEvent < eventsNumber-1) &&(!midiFile.getEvent(track,currentMidiEvent).isNoteOn() ||
          (int)((midiFile.getTimeInSeconds(track,currentMidiEvent) + midiFile.getEvent(track,currentMidiEvent).getDurationInSeconds())*1000) < (m_time.elapsed()+total_time+windowWidth/2))){
        currentMidiEvent++;
    }

    //qDebug() << "Time:" << (m_time.elapsed()+total_time) << " currEvent: " << currentMidiEvent << " startTime: " << midiFile.getTimeInSeconds(track,currentMidiEvent)*1000;

    /* Add the tone if it is within the current time limit(depends on time resolution in midiview) */
    if((int)(midiFile.getTimeInSeconds(track,currentMidiEvent)*1000) <= (m_time.elapsed() + total_time+windowWidth/2)){
        keyNumber = midiFile.getEvent(track,currentMidiEvent).getKeyNumber();
        midiTone = keyNumber-60;
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
    }else{
        /* Add wrong tone to midiview */
        midiView->addCorrectTone(-500);
        midiView->addWrongTone(sungTone);
    }

    /* Stop if reaches end of midi track */
    if(currentMidiEvent >= eventsNumber-1){
        stop();
    }
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
    currentMidiEvent = 0;
    singView->setPlayPauseButtonText("Play");
    for(int i=0;i<windowWidth/(updateInterval);i++){
        midiView->addMidiTone(-500);
    }
}
