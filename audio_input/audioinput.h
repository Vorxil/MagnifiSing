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
public:
    audioinput();
    ~audioinput();

public Q_SLOTS:
    const quint16* readMore();
    void stopRecording();
};

#endif // AUDIOINPUT_H
