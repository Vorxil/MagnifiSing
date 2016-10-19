#include "mainwindow.h"
#include "mainmenuview.h"
#include "startsingingview.h"
#include "helpview.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>



MainMenuView* mainMenuView;
StartSingingView* startSingingView;
HelpView* helpView;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    mainMenuView = new MainMenuView();
    startSingingView = new StartSingingView();
    helpView = new HelpView();

    ui->setupUi(this);

    /* Add all views to the Layout */
    ui->mainLayout->addWidget(mainMenuView);
    ui->mainLayout->addWidget(startSingingView);
    ui->mainLayout->addWidget(helpView);


    /* Hide the views that should not be displayed */
    startSingingView->hide();
    helpView->hide();

    /* Connect all buttons to the correct actions */
    connect(mainMenuView,SIGNAL(startSingingButtonClicked()),this,SLOT(enterSingingMenu()));
    connect(mainMenuView,SIGNAL(quitButtonClicked()),this,SLOT(close()));
    connect(mainMenuView,SIGNAL(helpButtonClicked()),this,SLOT(enterHelpMenu()));

    connect(startSingingView,SIGNAL(backButtonClicked()),this,SLOT(enterMainMenu()));

    connect(helpView,SIGNAL(backButtonClicked()),this,SLOT(enterMainMenu()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::enterMainMenu(){
    startSingingView->hide();
    helpView->hide();
    mainMenuView->show();
}

void MainWindow::enterSingingMenu(){
    mainMenuView->hide();
    helpView->hide();
    startSingingView->show();
}

void MainWindow::enterHelpMenu(){
    mainMenuView->hide();
    startSingingView->hide();
    helpView->show();

}
