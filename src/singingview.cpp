#include "singingview.h"
#include "midiview.h"
#include "ui_singingview.h"

MIDIview* midiView;

SingingView::SingingView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SingingView)
{
    ui->setupUi(this);
    ui->silentThresholdSlider->setMaximum(300);
    ui->silentThresholdSlider->setMinimum(0);

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

void SingingView::on_stopButton_clicked()
{
    emit stopButtonClicked();
}

void SingingView::on_backButton_clicked()
{
    emit backButtonClicked();
}

void SingingView::setSilentThresholdSlider(int position){
    ui->silentThresholdSlider->setSliderPosition(position);
}

int SingingView::getSilentThresholdSliderPosition(){
    return ui->silentThresholdSlider->sliderPosition();
}

void SingingView::on_silentThresholdSlider_sliderMoved(int position)
{
    emit silentThresholdSliderMoved(position);
}

int SingingView::repeatButtonChecked(){
    return ui->repeatCheckBox->isChecked();
}

int SingingView::getRepeatStart(){
    return ui->repeatStartSpinBox->value();
}

int SingingView::getRepeatEnd(){
    return ui->repeatEndSpinBox->value();
}

void SingingView::setRepeatMaximumSeconds(int sec){
    ui->repeatStartSpinBox->setMaximum(sec);
    ui->repeatEndSpinBox->setMaximum(sec);
}
