#include "singingview.h"
#include "midiview.h"
#include "ui_singingview.h"

MIDIview* midiView;

SingingView::SingingView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SingingView)
{
    ui->setupUi(this);

    midiView = new MIDIview();
    ui->viewLayout->addWidget(midiView);
}

SingingView::~SingingView()
{
    delete midiView;
    delete ui;
}

void SingingView::on_menuButton_clicked()
{
    emit menuButtonClicked();
}

MIDIview* SingingView::getMidiView(){
    return midiView;
}

void SingingView::on_playButton_clicked()
{
    emit playButtonClicked();
}

void SingingView::setPlayPauseButtonText(QString text){
    ui->playButton->setText(text);
}
