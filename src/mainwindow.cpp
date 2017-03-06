#include "mainwindow.h"
#include "mainmenuview.h"
#include "startsingingview.h"
#include "helpview.h"
#include "midiview.h"
#include "singingview.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>



MainMenuView* mainMenuView;
StartSingingView* startSingingView;
HelpView* helpView;
SingingView* singingView;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    mainMenuView = new MainMenuView();
    startSingingView = new StartSingingView();
    helpView = new HelpView();
    singingView = new SingingView();


    ui->setupUi(this);
    QPixmap background(":/images/background.jpg");
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, background);
    this->setPalette(palette);

    /* Add all views to the Layout */
    ui->mainLayout->addWidget(mainMenuView);
    ui->mainLayout->addWidget(startSingingView);
    ui->mainLayout->addWidget(helpView);
    ui->mainLayout->addWidget(singingView);


    /* Hide the views that should not be displayed */
    startSingingView->hide();
    helpView->hide();
    singingView->hide();


    /* Connect all buttons to the correct actions */
    connect(mainMenuView,SIGNAL(startSingingButtonClicked()),this,SLOT(enterSingingMenu()));
    connect(mainMenuView,SIGNAL(quitButtonClicked()),this,SLOT(close()));
    connect(mainMenuView,SIGNAL(helpButtonClicked()),this,SLOT(enterHelpMenu()));

    connect(startSingingView,SIGNAL(backButtonClicked()),this,SLOT(enterMainMenu()));
    connect(startSingingView,SIGNAL(continueButtonClicked()),this,SLOT(enterSingingView()));

    connect(helpView,SIGNAL(backButtonClicked()),this,SLOT(enterMainMenu()));

    connect(singingView,SIGNAL(menuButtonClicked()),this,SLOT(enterMainMenu()));
    connect(singingView,SIGNAL(backButtonClicked()),this,SLOT(enterSingingMenu()));


}

MainWindow::~MainWindow()
{
    delete mainMenuView;
    delete startSingingView;
    delete helpView;
    delete singingView;
    delete ui;
}

void MainWindow::enterMainMenu(){
    startSingingView->hide();
    helpView->hide();
    singingView->hide();
    mainMenuView->show();
}

void MainWindow::enterSingingMenu(){
    mainMenuView->hide();
    helpView->hide();
    singingView->hide();
    startSingingView->show();
}

void MainWindow::enterHelpMenu(){
    mainMenuView->hide();
    startSingingView->hide();
    singingView->hide();
    helpView->show();

}

void MainWindow::enterSingingView(){
    mainMenuView->hide();
    startSingingView->hide();
    helpView->hide();
    singingView->show();

}

SingingView* MainWindow::getSingingView(){
    return singingView;
}

StartSingingView* MainWindow::getStartSingingView(){
    return startSingingView;
}
