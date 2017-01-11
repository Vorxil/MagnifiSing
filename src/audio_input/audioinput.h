#ifndef AUDIOINPUT_H
#define AUDIOINPUT_H

#include <QObject>
#include <QAudioFormat>
#include <QIODevice>


class audioinput : public QObject
{
    Q_OBJECT
private:
    void printBufferData();
    double samples[1024];

public:
    audioinput();
    ~audioinput();

signals:
    void readyRead();

public Q_SLOTS:
    double *readMore();
    void stopRecording();
    void emitReadyReadSignal();
};

#endif // AUDIOINPUT_H
