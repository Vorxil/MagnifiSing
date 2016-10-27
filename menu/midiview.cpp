#include "midiview.h"
#include "ui_midiview.h"
#include <QPixmap>
#include <QPainter>


QPixmap* px;
int highestTone;
int lowestTone;

MIDIview::MIDIview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MIDIview)
{
    ui->setupUi(this);

    px = new QPixmap(this->width(),this->height());
    px->fill(Qt::white);
    ui->imageLabel->setPixmap(*px);

    testView();

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

    addTone(26,30,150);
    addTone(28,200,80);
    addTone(30,280,100);
    addTone(29,390,200);
    addTone(28,590,120);

    addCorrectTone(26,30,50);
    addWrongTone(27,90,10);
    addCorrectTone(26,130,50);

    addWrongTone(26,210,20);
    addCorrectTone(28,230,50);

    addCorrectTone(30,280,70);

    setLyrics(QString("This is some example lyrics"));

//    resetView();
//    setLyrics(QString("This is some other lyrics"));

}

void MIDIview::paintEvent(QPaintEvent *event){


}
void MIDIview::resetView(){
    px->fill(Qt::white);
    ui->imageLabel->setPixmap(*px);
}

void MIDIview::addTone(int tone, int start, int duration){

    // Scales the y axis so that all correct tones are displayed at coordinates between 25% and 75% of widget height
    int diff = highestTone - lowestTone;
    int sFactor = px->height()/(diff*2);
    int y = px->height()-(0.25*px->height()+(tone-lowestTone)*sFactor);


    QPainter p(px);
    QPen pen(Qt::gray,14,Qt::SolidLine,Qt::FlatCap, Qt::BevelJoin);
    p.setPen(pen);
    p.drawLine(start,y,start+duration,y);
    ui->imageLabel->setPixmap(*px);
}

void MIDIview::addCorrectTone(int tone, int start, int duration){

    // Scales the y axis so that all correct tones are displayed at coordinates between 25% and 75% of widget height
    int diff = highestTone - lowestTone;
    int sFactor = px->height()/(diff*2);
    int y = px->height()-(0.25*px->height()+(tone-lowestTone)*sFactor);

    QPainter p(px);
    QPen pen(QBrush(QColor(0,150,0,120)),18,Qt::SolidLine,Qt::RoundCap, Qt::BevelJoin);
    p.setPen(pen);
    p.drawLine(start,y,start+duration,y);
    ui->imageLabel->setPixmap(*px);
}

void MIDIview::addWrongTone(int tone, int start, int duration){

    // Scales the y axis so that all correct tones are displayed at coordinates between 25% and 75% of widget height
    int diff = highestTone - lowestTone;
    int sFactor = px->height()/(diff*2);
    int y = px->height()-(0.25*px->height()+(tone-lowestTone)*sFactor);

    QPainter p(px);
    QPen pen(QBrush(QColor(200,0,0,160)),18,Qt::SolidLine,Qt::RoundCap, Qt::BevelJoin);
    p.setPen(pen);
    p.drawLine(start,y,start+duration,y);
    ui->imageLabel->setPixmap(*px);
}

void MIDIview::setLyrics(QString lyrics){

    QPainter p(px);
    QFont f;
    f.setFamily("Arial");
    f.setPixelSize(30);
    p.setFont(f);

    // draw text at the lowest 25% of widget
    p.drawText(QRect(0,0.85*px->height(),px->width(),0.25*px->height()),Qt::AlignHCenter,lyrics);
    ui->imageLabel->setPixmap(*px);

}
