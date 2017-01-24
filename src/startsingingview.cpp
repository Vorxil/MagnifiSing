#include <QtWidgets/QFileDialog>
#include <QtCore/QString>
#include "startsingingview.h"
#include "ui_startsingingview.h"

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

void StartSingingView::on_chooseSongButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Sheet music file"), "", tr("Midi Files (*.mdi *.midi *.mid)"));
    emit chooseSongButtonClicked();
}
