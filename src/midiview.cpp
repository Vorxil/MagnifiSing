#include "midiview.h"
#include "ui_midiview.h"
#include <QPixmap>
#include <QPainter>
#include <QLinkedList>
#include <QDebug>
#include "math.h"


QPixmap* px;

int correctTones[windowWidth/(2*updateInterval)];
int wrongTones[windowWidth/(2*updateInterval)];
int midiTones[windowWidth/updateInterval];
int correctIdx;
int wrongIdx;
int midiIdx;

int i;
int highestTone;
int lowestTone;
int currentTime;
double timeWindow;




MIDIview::MIDIview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MIDIview)
{
    ui->setupUi(this);

    px = new QPixmap(this->width(),this->height());
    px->fill(Qt::white);
    ui->imageLabel->setPixmap(*px);

    timeWindow = 0; // Time shown starts from 0 seconds
    currentTime = 0;

    /* Initialize the tone arrays */
    for(int i=0;i<windowWidth/(2*updateInterval);i++){
        correctTones[i] = -500;
        wrongTones[i] = -500;
    }
    for(int i=0;i<windowWidth/(updateInterval);i++){
        midiTones[i] = -500;
    }

}

MIDIview::~MIDIview()
{
    delete px;
    delete ui;
}


void MIDIview::paintEvent(QPaintEvent *event){
    px->fill(Qt::white);
    QPainter p(px);
    QFont f;
    f.setFamily("Arial");
    f.setPixelSize(15);
    p.setFont(f);
    p.drawText(10,px->height()*0.25,"C6");
    p.drawText(10,px->height()*0.5,"C4");
    p.drawText(10,px->height()*0.75,"C2");
    f.setPixelSize(25);
    p.setFont(f);
    p.drawText(px->width()*0.9,px->height()*0.1,QString::number(currentTime/1000));



    /* Draw tones from midi file */
    QPen pen(QBrush(QColor("darkGrey")),18,Qt::SolidLine,Qt::FlatCap, Qt::BevelJoin);
    p.setPen(pen);
    for(i=0; i<windowWidth/updateInterval; i++){
        int tone = midiTones[(midiIdx+i)%(windowWidth/updateInterval)];
        int start = i*updateInterval;
        int duration = updateInterval;

        /* Scale the y axis so that all correct tones are displayed at coordinates between 25% and 75% of widget height */
        double diff = highestTone - lowestTone;
        double sFactor = px->height()/(diff*2);
        int y = px->height()-(0.25*px->height()+(tone-lowestTone)*sFactor);


        /* Scale the x axis so that the length of the axis = 10 seconds */
        int x1 = px->width()*(start % windowWidth)/(double)windowWidth;
        int x2 = px->width()*((start+duration) % windowWidth)/(double)windowWidth;
        if(x1 < x2){
            p.drawLine(x1,y,x2,y);
        }
    }

    /* Draw correct sung tones */
    QPen pen1(QBrush(QColor(0,150,0,120)),18,Qt::SolidLine,Qt::FlatCap, Qt::BevelJoin);
    p.setPen(pen1);
    for(i=0; i<windowWidth/(2*updateInterval); i++){
        int tone = correctTones[(correctIdx+i)%(windowWidth/(2*updateInterval))];
        int start = i*updateInterval;
        int duration = updateInterval;

        /* Scale the y axis so that all correct tones are displayed at coordinates between 25% and 75% of widget height */
        double diff = highestTone - lowestTone;
        double sFactor = px->height()/(diff*2);
        int y = px->height()-(0.25*px->height()+(tone-lowestTone)*sFactor);


        /* Scale the x axis so that the length of the axis = 10 seconds */
        int x1 = px->width()*(start % windowWidth)/(double)windowWidth;
        int x2 = px->width()*((start+duration) % windowWidth)/(double)windowWidth;

        if(x1 < x2){
            p.drawLine(x1,y,x2,y);
        }
    }

    /* Draw wrong sung tones */
    QPen pen2(QBrush(QColor("red")),18,Qt::SolidLine,Qt::FlatCap, Qt::BevelJoin);
    p.setPen(pen2);
    for(i=0; i<windowWidth/(2*updateInterval); i++){
        int tone = wrongTones[(wrongIdx+i)%(windowWidth/(2*updateInterval))];
        int start = i*updateInterval;
        int duration = updateInterval;

        /* Scale the y axis so that all correct tones are displayed at coordinates between 25% and 75% of widget height */
        double diff = highestTone - lowestTone;
        double sFactor = px->height()/(diff*2);
        int y = px->height()-(0.25*px->height()+(tone-lowestTone)*sFactor);


        /* Scale the x axis so that the length of the axis = 10 seconds */
        int x1 = px->width()*(start % windowWidth)/(double)windowWidth;
        int x2 = px->width()*((start+duration) % windowWidth)/(double)windowWidth;

        if(x1 < x2){
            p.drawLine(x1,y,x2,y);
        }
    }

    ui->imageLabel->setPixmap(*px);

}


void MIDIview::addCorrectTone(int tone){
    correctIdx = (correctIdx+1)%(windowWidth/(2*updateInterval));
    correctTones[correctIdx] = tone;
}

void MIDIview::addWrongTone(int tone){
    wrongIdx = (wrongIdx+1)%(windowWidth/(2*updateInterval));
    wrongTones[wrongIdx] = tone;
}

void MIDIview::addMidiTone(int tone){
    midiIdx = (midiIdx+1)%(windowWidth/updateInterval);
    midiTones[midiIdx] = tone;
}

void MIDIview::setCurrentTime(int time){
    currentTime = time;
}


void MIDIview::setLyrics(QString lyrics){

    QPainter p(px);
    QFont f;
    f.setFamily("Arial");
    f.setPixelSize(30);
    p.setFont(f);

    // draw text at the lowest 15% of widget
    p.drawText(QRect(0,0.75*px->height(),px->width(),0.25*px->height()),Qt::AlignCenter,lyrics);
    ui->imageLabel->setPixmap(*px);

}


void MIDIview::setToneInterval(int lowTone,int highTone){
    lowestTone = lowTone;
    highestTone = highTone;
}
