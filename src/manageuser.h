#ifndef MANAGEUSER_H
#define MANAGEUSER_H

#include <QDialog>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include "startsingingview.h"
#include "adduser.h"

namespace Ui {
class ManageUser;
}

class ManageUser : public QDialog
{
    Q_OBJECT

public:
    explicit ManageUser(QWidget *parent = 0);
    ~ManageUser();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_add_clicked();

private:
    Ui::ManageUser *ui;
    StartSingingView *startsingingview;
    void resizeEvent(QResizeEvent *event);
};

#endif // MANAGEUSER_H
