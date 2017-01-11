#ifndef MIDIVIEW_H
#define MIDIVIEW_H

#include <QWidget>

#define updateInterval 40   // milliseconds
#define windowWidth 10000   // milliseconds

namespace Ui {
class MIDIview;
}

class MIDIview : public QWidget
{
    Q_OBJECT

public:
    explicit MIDIview(QWidget *parent = 0);
    ~MIDIview();

    void setToneInterval(int lowTone, int highTone);
    int freqToSemitone(double frequency);
    void setLyrics(QString lyrics);
    void addCorrectFrequency(double frequency, int time);

private:
    Ui::MIDIview *ui;
    void paintEvent(QPaintEvent *event);
};

#endif // MIDIVIEW_H
