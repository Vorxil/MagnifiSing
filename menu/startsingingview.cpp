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
    emit chooseSongButtonClicked();
}
