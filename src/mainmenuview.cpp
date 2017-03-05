#include "mainmenuview.h"
#include "ui_mainmenuview.h"
#include "manageuser.h"

MainMenuView::MainMenuView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMenuView)
{
    ui->setupUi(this);
}

MainMenuView::~MainMenuView()
{
    delete ui;
}

void MainMenuView::on_buttonSing_clicked()
{
    emit startSingingButtonClicked();
}

void MainMenuView::on_buttonQuit_clicked()
{
    emit quitButtonClicked();
}

void MainMenuView::on_buttonHelp_clicked()
{
    emit helpButtonClicked();
}

void MainMenuView::on_buttonLogIn_clicked()
{
    AddUser addUser;
    addUser.exec();
}
