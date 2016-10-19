#ifndef STARTSINGINGVIEW_H
#define STARTSINGINGVIEW_H

#include <QWidget>

namespace Ui {
class StartSingingView;
}

class StartSingingView : public QWidget
{
    Q_OBJECT

public:
    explicit StartSingingView(QWidget *parent = 0);
    ~StartSingingView();

private slots:
    void on_backButton_clicked();

private:
    Ui::StartSingingView *ui;
signals:
    void backButtonClicked();
};

#endif // STARTSINGINGVIEW_H
