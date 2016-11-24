#include "midiview.h"
#include "ui_midiview.h"
#include <QPixmap>
#include <QPainter>
#include <QDebug>
#include "math.h"


QPixmap* px;
int highestTone;
int lowestTone;
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

    //testView();

}

MIDIview::~MIDIview()
{
    delete px;
    delete ui;
}

/* Add some tones to test the view */
void MIDIview::testView(){

    highestTone = 30;
    lowestTone = 26;

    addTone(26,300,1500);
    addTone(28,2000,800);
    addTone(30,2800,1000);
    addTone(29,3900,2000);
    addTone(28,5900,1200);

    addCorrectTone(26,300,500);
    addWrongTone(27,900,100);
    addCorrectTone(26,1300,500);

    addWrongTone(26,2100,200);
    addCorrectTone(28,2300,500);

    addCorrectTone(30,2800,700);

    setLyrics(QString("This is some example lyrics"));

//    resetView();
//    setLyrics(QString("This is some other lyrics"));

}

void MIDIview::paintEvent(QPaintEvent *event){
    QPainter p(px);
    QFont f;
    f.setFamily("Arial");
    f.setPixelSize(15);
    p.setFont(f);
    p.drawText(10,px->height()*0.25,"1000 Hz");
    p.drawText(10,px->height()*0.75,"0 Hz");
    ui->imageLabel->setPixmap(*px);

}
void MIDIview::resetView(){
    px->fill(Qt::white);
    ui->imageLabel->setPixmap(*px);
}

/* Add a tone to the MIDI view.
 * start and duration are given in milliseconds*/
void MIDIview::addTone(int tone, int start, int duration){

    /* Clear the view if restarting from beginning of screen */
    if(start/1000.0 > timeWindow+10){
        timeWindow = floor(start/10000)*10;
        resetView();
    }


    /* Scale the y axis so that all correct tones are displayed at coordinates between 25% and 75% of widget height */
    double diff = highestTone - lowestTone;
    double sFactor = px->height()/(diff*2);
    int y = px->height()-(0.25*px->height()+(tone-lowestTone)*sFactor);


    /* Scale the x axis so that the length of the axis = 10 seconds */
    int x1 = px->width()*(start % 10000)/(double)10000;
    int x2 = px->width()*((start+duration) % 10000)/(double)10000;

    if(x1 > x2){
        return;
    }


    QPainter p(px);
    QPen pen(Qt::gray,14,Qt::SolidLine,Qt::FlatCap, Qt::BevelJoin);
    p.setPen(pen);
    p.drawLine(x1,y,x2,y);
    ui->imageLabel->setPixmap(*px);
}

/* Add a correct tone to the MIDI view.
 * start and duration are given in milliseconds*/
void MIDIview::addCorrectTone(int tone, int start, int duration){

    /* Clear the view if restarting from beginning of screen */
    if(start/1000.0 > timeWindow+10){
        timeWindow = floor(start/10000)*10;
        resetView();
    }

    /* Scale the y axis so that all correct tones are displayed at coordinates between 25% and 75% of widget height */
    double diff = highestTone - lowestTone;
    double sFactor = px->height()/(diff*2);
    int y = px->height()-(0.25*px->height()+(tone-lowestTone)*sFactor);


    /* Scale the x axis so that the length of the axis = 10 seconds */
    int x1 = px->width()*(start % 10000)/(double)10000;
    int x2 = px->width()*((start+duration) % 10000)/(double)10000;

    if(x1 > x2){
        return;
    }



    QPainter p(px);
    QPen pen(QBrush(QColor(0,150,0,120)),18,Qt::SolidLine,Qt::FlatCap, Qt::BevelJoin);
    p.setPen(pen);
    p.drawLine(x1,y,x2,y);
    ui->imageLabel->setPixmap(*px);
}

/* Add a wrong tone to the MIDI view.
 * start and duration are given in milliseconds*/
void MIDIview::addWrongTone(int tone, int start, int duration){

    /* Clear the view if restarting from beginning of screen */
    if(start/1000.0 > timeWindow+10){
        timeWindow = floor(start/10000)*10;
        resetView();
    }

    /* Scale the y axis so that all correct tones are displayed at coordinates between 25% and 75% of widget height */
    double diff = highestTone - lowestTone;
    double sFactor = px->height()/(diff*2);
    int y = px->height()-(0.25*px->height()+(tone-lowestTone)*sFactor);


    /* Scale the x axis so that the length of the axis = 10 seconds */
    int x1 = px->width()*(start % 10000)/(double)10000;
    int x2 = px->width()*((start+duration) % 10000)/(double)10000;

    if(x1 > x2){
        return;
    }

    QPainter p(px);
    QPen pen(QBrush(QColor(200,0,0,160)),18,Qt::SolidLine,Qt::FlatCap, Qt::BevelJoin);
    p.setPen(pen);
    p.drawLine(x1,y,x2,y);
    ui->imageLabel->setPixmap(*px);
}

void MIDIview::setLyrics(QString lyrics){

    QPainter p(px);
    QFont f;
    f.setFamily("Arial");
    f.setPixelSize(30);
    p.setFont(f);

    // draw text at the lowest 25% of widget
    p.drawText(QRect(0,0.75*px->height(),px->width(),0.25*px->height()),Qt::AlignCenter,lyrics);
    ui->imageLabel->setPixmap(*px);

}

void MIDIview::setToneInterval(int lowestFrequency,int highestFrequency){
    lowestTone = lowestFrequency;
    highestTone = highestFrequency;
}
