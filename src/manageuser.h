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
    QSqlDatabase db;
    void connClose()
    {
        db.close();
        db.removeDatabase(QSqlDatabase::defaultConnection);
    }

    bool connOpen()
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("F:/CS&SE(MSc.)/Project Course/MagnifiDB.sqlite");

        if(!db.open())
        {
            qDebug() << "Database connection failed";
            return false;
        }
        else
        {
            qDebug() << "Connected to database";
            return true;
        }
    }


public:
    explicit ManageUser(QWidget *parent = 0);
    ~ManageUser();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_add_clicked();

private:
    Ui::ManageUser *ui;
    StartSingingView *startsingingview;
};

#endif // MANAGEUSER_H
