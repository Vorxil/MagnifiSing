#ifndef MIDIVIEW_H
#define MIDIVIEW_H

#include <QWidget>

namespace Ui {
class MIDIview;
}

class MIDIview : public QWidget
{
    Q_OBJECT

public:
    explicit MIDIview(QWidget *parent = 0);
    ~MIDIview();

    void addTone(int tone, int start, int duration);
    void addCorrectTone(int tone, int start, int duration);
    void addWrongTone(int tone, int start, int duration);


    void testView();
private:
    Ui::MIDIview *ui;
    void paintEvent(QPaintEvent *event);
};

#endif // MIDIVIEW_H
