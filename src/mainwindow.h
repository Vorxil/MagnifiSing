#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "singingview.h"
#include "startsingingview.h"

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

    StartSingingView* getStartSingingView();
public slots:
    void enterMainMenu();
    void enterSingingMenu();
    void enterHelpMenu();
    void enterSingingView();
private:
    Ui::MainWindow *ui;
    void resizeEvent(QResizeEvent *event);
};

#endif // MAINWINDOW_H
