#ifndef SINGINGVIEWCONTROLLER_H
#define SINGINGVIEWCONTROLLER_H

#include <QObject>
#include "singingview.h"
#include "startsingingview.h"
#include "midiview.h"
#include "audio_input/audioinput.h"
#include "audio_input/cepsdwt.h"
#include "midifile/MidiFile.h"

class SingingViewController : public QObject
{
    Q_OBJECT
private:
    MIDIview* midiView;
    double frequency;
    double* samples;
    audioinput* audioInput;

public:
    SingingViewController(SingingView*singingView, StartSingingView *ssView);
    ~SingingViewController();

    int freqToSemitone(double frequency);
    int setMidiFile(QString filepath);
    QString getMidiTextAsString(MidiFile midifile);
    int getTrack_MaxTextEvents();
    QStringList getTrackNames();
public Q_SLOTS:
    void readSamples();
    void updateMidiView();
    void play_pause();
    void stop();
    void updateMidiFile(QString filepath);
    void setToneTrack(int track);
    void setTextTrack(int track);
};

#endif // SINGINGVIEWCONTROLLER_H
