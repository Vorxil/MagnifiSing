#include "audioinput.h"
#include <iostream>
#include <QAudio>
#include <QAudioInput>
#include <QAudioDeviceInfo>
#include <QDebug>
#include <QObject>
#include <QTimer>

QAudioInput* m_audioInput;
QByteArray *m_buffer;
QIODevice *m_input;
QAudioDeviceInfo device_info;

const int BufferSize = 4096;

/* Setup the audio input */
audioinput::audioinput()
{
    m_buffer = new QByteArray(BufferSize,0);

    device_info = QAudioDeviceInfo::defaultInputDevice();

    QAudioFormat format;
    format.setSampleRate(8000);
    format.setChannelCount(1);
    format.setSampleSize(8);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);


    if (!device_info.isFormatSupported(format)) {
        qWarning() << "Default format not supported - trying to use nearest";
        format = device_info.nearestFormat(format);
    }

    m_audioInput = new QAudioInput(device_info, format, this);
    m_input = m_audioInput->start();
    connect(m_input, SIGNAL(readyRead()), SLOT(readMore()));
    QTimer::singleShot(2000, this, SLOT(stopRecording()));  //Stop audio input after 2 seconds
}

audioinput::~audioinput(){

}

/* Read the available input and print it to the screen*/
void audioinput::readMore()
{
    if (!m_audioInput)
        return;
    qint64 len = m_audioInput->bytesReady();
    if (len > BufferSize)
        len = BufferSize;
    qint64 l = m_input->read(m_buffer->data(), len);
    if (l > 0){
        // Print the data to the screen
        std::cout << "\nFirst 8 bytes in buffer:\n";
        for(int i = 0;i<10;i++){
            std::cout << (int)m_buffer->data()[i] << ", ";
        }
        std::cout << "\n";
    }
}

void audioinput::stopRecording(){
    m_audioInput->stop();
    delete m_audioInput;
    std::cout << "Stopped recording\n";



    /* Printing some bytes from the buffer*/
    for(int i = 300;i < 330;i++){
        std::cout << "\nbyte " << i << ": " << (int)m_buffer->at(i);
    }

    /* Printing different supported audio formats */
    qDebug() << "\n\nDevices available:";
    foreach (QAudioDeviceInfo info, QAudioDeviceInfo::availableDevices(QAudio::AudioInput)) {
        qDebug() << info.deviceName();
    }
    qDebug() << "\nSupported formats for default input device";
    qDebug() << "Supported sample rates: " << device_info.supportedSampleRates();
    qDebug() << "Supported sample sizes: " << device_info.supportedSampleSizes();
    qDebug() << "Supported sample types: " << device_info.supportedSampleTypes();
    qDebug() << "Supported codecs: " << device_info.supportedCodecs();
    qDebug() << "Supported byte orders: " << device_info.supportedByteOrders();
    qDebug() << "Supported channel counts: " << device_info.supportedChannelCounts();

}
