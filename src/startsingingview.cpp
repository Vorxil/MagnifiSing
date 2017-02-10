#include <QtWidgets/QFileDialog>
#include <QtCore/QString>
#include "startsingingview.h"
#include "ui_startsingingview.h"
#include "QDebug"

StartSingingView::StartSingingView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartSingingView)
{
    ui->setupUi(this);
}

StartSingingView::~StartSingingView()
{
    delete ui;
}


void StartSingingView::on_backButton_clicked()
{
    emit backButtonClicked();
}


void StartSingingView::on_loadFileButton_clicked()
{
    emit loadFileButtonClicked(ui->filePathField->text());
}

void StartSingingView::on_browseButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Sheet music file"), "", tr("Midi Files (*.mdi *.midi *.mid)"));
    ui->filePathField->setText(fileName);
}

void StartSingingView::on_continueButton_clicked()
{
    emit continueButtonClicked();
}

void StartSingingView::on_textTrackComboBox_currentIndexChanged(int index)
{
    emit textTrackComboBoxIndexChanged(index);
}

void StartSingingView::on_toneTrackComboBox_currentIndexChanged(int index)
{
    emit toneTrackComboBoxIndexChanged(index);
}

void StartSingingView::setTextTrackComboBox(int n){

    /* Add new items */
    for(int i=0; i<n; i++){
        ui->textTrackComboBox->addItem(QString::number(i),Qt::DisplayRole);
    }
    /* Remove all old items */
    while(ui->textTrackComboBox->count()>n){
        ui->textTrackComboBox->removeItem(0);
    }

}

void StartSingingView::setToneTrackComboBox(int n){

    /* Add new items */
    for(int i=0; i<n; i++){
        ui->toneTrackComboBox->addItem(QString::number(i),Qt::DisplayRole);
    }
    /* Remove all old items */
    while(ui->toneTrackComboBox->count()>n){
        ui->toneTrackComboBox->removeItem(0);
    }
}
void StartSingingView::setContinueButtonEnabled(int e){
    ui->continueButton->setEnabled(e);
}

void StartSingingView::setMidiTextAreaText(QString text){
    ui->displayMidiTextArea->setText(text);
}
