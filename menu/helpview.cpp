#include "helpview.h"
#include "ui_helpview.h"

HelpView::HelpView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HelpView)
{
    ui->setupUi(this);
}

HelpView::~HelpView()
{
    delete ui;
}

void HelpView::on_backButton_clicked()
{
    emit backButtonClicked();
}
