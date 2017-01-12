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

    if (!connOpen())
    {
        qDebug() << "Database connection failed!";
        return;
    }

    connOpen();
    QSqlQuery query;
    query.prepare("Select * from user where user_name = '"+username+"' and password = '"+password+"'");

    if(query.exec())
    {
        int count = 0;
        while(query.next())
        {
            count++;
        }
        if(count == 1)
        {
            qDebug() << "Logging In";
            connClose();
            this->hide();
            startsingingview = new StartSingingView();
            startsingingview->show();
        }

        if(count < 1)
        {
             QMessageBox::about(this,tr("Error"),tr("Incorrect Username and Password"));
        }
    }

}

void ManageUser::on_pushButton_add_clicked()
{
    this->hide();
    AddUser adduser;
    adduser.setModal(true);
    adduser.exec();
}
