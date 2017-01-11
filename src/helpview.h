#ifndef HELPVIEW_H
#define HELPVIEW_H

#include <QWidget>

namespace Ui {
class HelpView;
}

class HelpView : public QWidget
{
    Q_OBJECT

public:
    explicit HelpView(QWidget *parent = 0);
    ~HelpView();

private slots:
    void on_backButton_clicked();

private:
    Ui::HelpView *ui;
signals:
    void backButtonClicked();
};

#endif // HELPVIEW_H
