#include "audioinput.h"
#include <QAudio>
#include <QAudioInput>
#include <QAudioDeviceInfo>
#include <QDebug>
#include <QObject>
#include <QAudioBuffer>



QAudioInput* m_audioInput;
QByteArray *m_buffer;
QIODevice *m_input;
QAudioDeviceInfo device_info;
QAudioFormat format;

const int BufferSize = RETURN_SIZE*SAMPLE_SIZE/8;

/* Setup the audio input */
audioinput::audioinput()
{
    m_buffer = new QByteArray(BufferSize,0);

    device_info = QAudioDeviceInfo::defaultInputDevice();


    format.setSampleRate(SAMPLE_RATE);
    format.setChannelCount(1);
    format.setSampleSize(SAMPLE_SIZE);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);


    if (!device_info.isFormatSupported(format)) {
        qWarning() << "Default format not supported - trying to use nearest";
        format = device_info.nearestFormat(format);
    }

    m_audioInput = new QAudioInput(device_info, format, this);
    m_audioInput->setBufferSize(BufferSize*5);
    m_input = m_audioInput->start();

    connect(m_input, SIGNAL(readyRead()), this, SLOT(emitReadyReadSignal()));
}

audioinput::~audioinput(){
    delete m_buffer;
    delete m_audioInput;
}

/* Read the available input and return a pointer to the data*/
double* audioinput::readMore()
{
    if (!m_audioInput)
        return 0;
    qint64 len = m_audioInput->bytesReady();
    if (len > BufferSize)
        len = BufferSize;
    qint64 l = m_input->read(m_buffer->data(), len);
    if (l > 0){

        QAudioBuffer audioBuffer(*m_buffer,format,(qint64)-1);

        const qint16 *dataPtr = audioBuffer.constData<qint16>();

        /* Convert the samples to double */
        for(int i = 0;i<RETURN_SIZE;i++){
            samples[i] = (double)dataPtr[i];
        }

        return samples;

    }
    return 0;
}

void audioinput::stopRecording(){
    m_audioInput->stop();
    qDebug() << "\nStopped recording";

    //printBufferData();
}

void audioinput::emitReadyReadSignal(){
    emit readyRead();
}

/* Print the data in the buffer to the screen */
void audioinput::printBufferData(){

    QAudioBuffer audioBuffer(*m_buffer,format,(qint64)-1);
    const qint16 *data = audioBuffer.constData<qint16>();

    qDebug() << "Data in buffer: ";

    for(int i = 0;i<audioBuffer.frameCount();i=i+8){
        qDebug() << data[i] << data[i+1] << data[i+2] << data[i+3] << data[i+4] << data[i+5] << data[i+6] << data[i+7];
    }
}
