#include "mainwindow.h"
#include <QApplication>
#include <QStyle>
#include <QDesktopWidget>
#include "singingviewcontroller.h"
#include "singingview.h"
#include "database.h"

Database *db;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    db = new Database( DB_FILENAME );
    SingingViewController* singingViewController = new SingingViewController(w.getSingingView(), w.getStartSingingView());

    w.setWindowTitle("MagnifiSing");

    w.show();

    a.exit(0);
    return a.exec();

}
