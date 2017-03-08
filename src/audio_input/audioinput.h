#ifndef AUDIOINPUT_H
#define AUDIOINPUT_H

#include <QObject>
#include <QAudioFormat>
#include <QIODevice>

#define SAMPLE_RATE 48000
#define SAMPLE_SIZE 16
#define RETURN_SIZE 8192        // Number of samples returned when calling readMore()


class audioinput : public QObject
{
    Q_OBJECT
private:
    void printBufferData();
    double samples[RETURN_SIZE];

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
