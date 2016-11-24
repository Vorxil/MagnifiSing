#ifndef SINGINGVIEWCONTROLLER_H
#define SINGINGVIEWCONTROLLER_H

#include <QObject>
#include "singingview.h"
#include "midiview.h"
#include "../audio_input/audioinput.h"
#include "../audio_input/cepsdwt.h"

class SingingViewController : public QObject
{
    Q_OBJECT
private:
    MIDIview* midiView;
    double frequency;
    double* samples;
    audioinput* audioInput;

public:
    SingingViewController(SingingView*);
    ~SingingViewController();
public Q_SLOTS:
    void readSamples();
    void updateMidiView();
};

#endif // SINGINGVIEWCONTROLLER_H
