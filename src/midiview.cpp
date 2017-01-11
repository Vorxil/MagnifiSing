#include "midiview.h"
#include "ui_midiview.h"
#include <QPixmap>
#include <QPainter>
#include <QLinkedList>
#include <QDebug>
#include "math.h"


QPixmap* px;
QLinkedList<int> correctToneList;
QLinkedList<int>::iterator itr;
int i;
int highestTone;
int lowestTone;
int currentTime;
double timeWindow;


/* Constants used in conversion from frequency to semitones */
const double const1 = 3/log(2);
const double const2 = log(4685120000);

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

    /* Initialize the linked list */
    for(int i=0;i<windowWidth/(2*updateInterval);i++){
        correctToneList << -500;
    }

}

MIDIview::~MIDIview()
{
    delete px;
    delete ui;
}

int MIDIview::freqToSemitone(double frequency){
    return (int)round(const1*(4*log(frequency)-const2));
}


void MIDIview::paintEvent(QPaintEvent *event){
    px->fill(Qt::white);
    QPainter p(px);
    QFont f;
    f.setFamily("Arial");
    f.setPixelSize(15);
    p.setFont(f);
    p.drawText(10,px->height()*0.25,"C7");
    p.drawText(10,px->height()*0.5,"C4");
    p.drawText(10,px->height()*0.75,"C1");
    f.setPixelSize(25);
    p.setFont(f);
    p.drawText(px->width()*0.9,px->height()*0.1,QString::number(currentTime/1000));

    QPen pen(QBrush(QColor(0,150,0,120)),18,Qt::SolidLine,Qt::FlatCap, Qt::BevelJoin);
    p.setPen(pen);

    i = 0;
    for(itr = correctToneList.begin(); itr!= correctToneList.end(); ++itr){
        int tone = *itr;
        int start = i*updateInterval;
        int duration = updateInterval;

        /* Scale the y axis so that all correct tones are displayed at coordinates between 25% and 75% of widget height */
        double diff = highestTone - lowestTone;
        double sFactor = px->height()/(diff*2);
        int y = px->height()-(0.25*px->height()+(tone-lowestTone)*sFactor);


        /* Scale the x axis so that the length of the axis = 10 seconds */
        int x1 = px->width()*(start % windowWidth)/(double)windowWidth;
        int x2 = px->width()*((start+duration) % windowWidth)/(double)windowWidth;

        p.drawLine(x1,y,x2,y);
        i++;
    }
    ui->imageLabel->setPixmap(*px);

}


void MIDIview::addCorrectFrequency(double frequency, int time){
    int tone = freqToSemitone(frequency);
    correctToneList.removeFirst();
    correctToneList << tone;
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
