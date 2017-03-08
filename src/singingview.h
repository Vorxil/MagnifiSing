#ifndef SINGINGVIEW_H
#define SINGINGVIEW_H

#include <QWidget>
#include "midiview.h"

namespace Ui {
class SingingView;
}

class SingingView : public QWidget
{
    Q_OBJECT

public:
    explicit SingingView(QWidget *parent = 0);
    ~SingingView();
    MIDIview* getMidiView();

    void setPlayPauseButtonText(QString text);
    void setSilentThresholdSlider(int position);
    int getSilentThresholdSliderPosition();
    int repeatButtonChecked();
    int getRepeatStart();
    int getRepeatEnd();
    void setRepeatMaximumSeconds(int sec);
private slots:
    void on_menuButton_clicked();


    void on_playButton_clicked();

    void on_stopButton_clicked();

    void on_backButton_clicked();

    void on_silentThresholdSlider_sliderMoved(int position);

signals:
    void menuButtonClicked();
    void playButtonClicked();
    void stopButtonClicked();
    void backButtonClicked();
    void silentThresholdSliderMoved(int position);

private:
    Ui::SingingView *ui;
};

#endif // SINGINGVIEW_H
