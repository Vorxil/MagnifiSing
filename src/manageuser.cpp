#include "manageuser.h"
#include "ui_manageuser.h"
#include "startsingingview.h"
#include <QMessageBox>

ManageUser::ManageUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManageUser)
{
    ui->setupUi(this);
}

ManageUser::~ManageUser()
{
    delete ui;
}

void ManageUser::on_pushButton_clicked()
{
    QString username,password;
    username = ui->lineEdit_username->text();
    password = ui->lineEdit_password->text();

}

void ManageUser::on_pushButton_add_clicked()
{
    this->hide();
    AddUser adduser;
    adduser.setModal(true);
    adduser.exec();
}
