#ifndef AUDIOINPUT_H
#define AUDIOINPUT_H

#include <QObject>
#include <QAudioFormat>
#include <QIODevice>


class audioinput : public QObject
{
    Q_OBJECT
public:
    audioinput();
    ~audioinput();

public Q_SLOTS:
    void readMore();
    void stopRecording();
};

#endif // AUDIOINPUT_H
