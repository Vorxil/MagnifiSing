#ifndef ADDUSER_H
#define ADDUSER_H
#include "manageuser.h"

#include <QDialog>
#include <QModelIndex>

namespace Ui {
class AddUser;
}

class AddUser : public QDialog
{
    Q_OBJECT

public:
    explicit AddUser(QWidget *parent = 0);
    ~AddUser();

private slots:


    void onUserTableClicked( const QModelIndex &index );
    void onCreateUserClicked();
    void onPlusClicked();

    void on_pushButton_save_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_view_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_pushButton_back_clicked();

private:
    void editState();
    void createState();
    void updateUsers();
    Ui::AddUser *ui;
    void resizeEvent(QResizeEvent *event);
};

#endif // ADDUSER_H
