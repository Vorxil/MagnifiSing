#include "mainwindow.h"
#include <QApplication>
#include <QStyle>
#include <QDesktopWidget>
#include "singingviewcontroller.h"
#include "singingview.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.getSingingView();
    SingingViewController* singingViewController = new SingingViewController(w.getSingingView());

    w.setWindowTitle("MagnifiSing");

    w.show();

    a.exit(0);
    return a.exec();
}
