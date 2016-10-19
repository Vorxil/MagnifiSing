#include "mainwindow.h"
#include <QApplication>
#include <QStyle>
#include <QDesktopWidget>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("MagnifiSing");

    w.show();

    a.exit(0);
    return a.exec();
}
