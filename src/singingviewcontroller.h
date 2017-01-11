#ifndef SINGINGVIEWCONTROLLER_H
#define SINGINGVIEWCONTROLLER_H

#include <QObject>
#include "singingview.h"
#include "midiview.h"
#include "audio_input/audioinput.h"
#include "audio_input/cepsdwt.h"

class SingingViewController : public QObject
{
    Q_OBJECT
private:
    MIDIview* midiView;
    double frequency;
    double* samples;
    audioinput* audioInput;

public:
    SingingViewController(SingingView*singingView);
    ~SingingViewController();
public Q_SLOTS:
    void readSamples();
    void updateMidiView();
    void play_pause();
};

#endif // SINGINGVIEWCONTROLLER_H
