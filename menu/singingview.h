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

private slots:
    void on_menuButton_clicked();


signals:
    void menuButtonClicked();

private:
    Ui::SingingView *ui;
};

#endif // SINGINGVIEW_H
