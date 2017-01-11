#ifndef MAINMENUVIEW_H
#define MAINMENUVIEW_H

#include <QWidget>

namespace Ui {
class MainMenuView;
}

class MainMenuView : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenuView(QWidget *parent = 0);
    ~MainMenuView();

private slots:
    void on_buttonSing_clicked();

    void on_buttonQuit_clicked();

    void on_buttonHelp_clicked();

private:
    Ui::MainMenuView *ui;

signals:
    void startSingingButtonClicked();
    void quitButtonClicked();
    void helpButtonClicked();
};

#endif // MAINMENUVIEW_H
