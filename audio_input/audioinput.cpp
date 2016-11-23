#include "audioinput.h"
#include <iostream>
#include <QAudio>
#include <QAudioInput>
#include <QAudioDeviceInfo>
#include <QDebug>
#include <QObject>
#include <QTimer>
#include <QAudioBuffer>
#include "cepsdwt.h"
#include "math.h"

QAudioInput* m_audioInput;
QByteArray *m_buffer;
QIODevice *m_input;
QAudioDeviceInfo device_info;
QAudioFormat format;
cepsDWT cepsdwt(1024,3);


const int BufferSize = 2048;

/* Setup the audio input */
audioinput::audioinput()
{
    m_buffer = new QByteArray(BufferSize,0);

    device_info = QAudioDeviceInfo::defaultInputDevice();


    format.setSampleRate(8000);
    format.setChannelCount(1);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);


    if (!device_info.isFormatSupported(format)) {
        qWarning() << "Default format not supported - trying to use nearest";
        format = device_info.nearestFormat(format);
    }

    m_audioInput = new QAudioInput(device_info, format, this);
    m_audioInput->setBufferSize(10240);
    m_input = m_audioInput->start();

    connect(m_input, SIGNAL(readyRead()), this, SLOT(readMore()));
    QTimer::singleShot(10000, this, SLOT(stopRecording()));  //Stop audio input after 10 seconds
}

audioinput::~audioinput(){
    delete m_buffer;
    delete m_audioInput;
}

/* Read the available input and return a pointer to the data*/
const quint16* audioinput::readMore()
{
    if (!m_audioInput)
        return (quint16)0;
    qint64 len = m_audioInput->bytesReady();
    if (len > BufferSize)
        len = BufferSize;
    qint64 l = m_input->read(m_buffer->data(), len);
    if (l > 0){

        QAudioBuffer audioBuffer(*m_buffer,format,(qint64)-1);

//        qDebug() << "duration" << audioBuffer.duration();
//        qDebug() << "byteCount" << audioBuffer.byteCount();
//        qDebug() << "format" << audioBuffer.format();
//        qDebug() << "samplecount" << audioBuffer.sampleCount();
//        qDebug() << " ";


        const quint16 *dataPtr = audioBuffer.constData<quint16>();

        /* Calculate and print pitch frequency */
        double samples[1024];
        for(int i = 0;i<1024;i++){
            samples[i] = (double)dataPtr[i];
        }
        std::cout << "\nPitch freq = " << cepsdwt.detectPitchFrequency(samples,8000);

        /* Test the pitch detection with a sine wave */
        double time;
        double y[1024];
        double f = 1000;
        double fs = 8000;

        for(int i = 0;i<1024;i++){
            time = i*1/fs;
            y[i] = sin(f*time);
        }
        std::cout << "\nSine wave freq = " << cepsdwt.detectPitchFrequency(y,8000) << "\n";


        return dataPtr;

    }
    return (quint16)0;
}

void audioinput::stopRecording(){
    m_audioInput->stop();
    qDebug() << "Stopped recording";


    //printBufferData();


}

/* Print the data in the buffer to the screen */
void audioinput::printBufferData(){

    QAudioBuffer audioBuffer(*m_buffer,format,(qint64)-1);
    const quint16 *data = audioBuffer.constData<quint16>();
    for(int i = 0;i<audioBuffer.frameCount();i++){
        std::cout << " " << data[i] << " ";
    }
}
