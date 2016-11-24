#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "singingview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    SingingView* getSingingView();

public slots:
    void enterMainMenu();
    void enterSingingMenu();
    void enterHelpMenu();
    void enterSingingView();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
