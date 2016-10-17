#include <QCoreApplication>
#include "audioinput.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    audioinput audioIn;

    return a.exec();
}
