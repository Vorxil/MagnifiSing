#ifndef STARTSINGINGVIEW_H
#define STARTSINGINGVIEW_H

#include <QWidget>

namespace Ui {
class StartSingingView;
}

class StartSingingView : public QWidget
{
    Q_OBJECT

public:
    explicit StartSingingView(QWidget *parent = 0);
    ~StartSingingView();

    void setTextTrackComboBox(int n, int selectTrack);
    void setToneTrackComboBox(int n);
    void setContinueButtonEnabled(int e);
    void setMidiTextAreaText(QString text);
private slots:
    void on_backButton_clicked();

    void on_loadFileButton_clicked();

    void on_browseButton_clicked();

    void on_continueButton_clicked();

    void on_textTrackComboBox_currentIndexChanged(int index);

    void on_toneTrackComboBox_currentIndexChanged(int index);

private:
    Ui::StartSingingView *ui;
signals:
    void backButtonClicked();
    void loadFileButtonClicked(QString filepath);
    void continueButtonClicked();
    void textTrackComboBoxIndexChanged(int index);
    void toneTrackComboBoxIndexChanged(int index);
};

#endif // STARTSINGINGVIEW_H
