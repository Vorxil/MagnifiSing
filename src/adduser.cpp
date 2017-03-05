#include "adduser.h"
#include "ui_adduser.h"
#include <QMessageBox>
#include <QTableView>
#include <QStandardItemModel>
#include "database.h"
#include "mainmenuview.h"

AddUser::AddUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUser)
{
    ui->setupUi(this);

    Database d( DB_FILENAME );
    QList<QString> *users = d.getUsers();

    QStandardItemModel *model = new QStandardItemModel( users->size(), 1, this );
    for ( int i = 0; i < users->size(); i++ ) {
        QStandardItem *item1 = new QStandardItem( users->at( i ) );
        model->setItem( i, 0, item1 );
    }
    ui->usersTable->setModel( model );

}

AddUser::~AddUser()
{
    delete ui;
}

void AddUser::on_pushButton_save_clicked()
{
    QString name,password, realname;
    name = ui->lineEdit_name->text();
    password = ui->lineEdit_password->text();
    realname = ui->lineEdit_realname->text();

    Database d( DB_FILENAME );
    d.addUser( name, password, realname );
}


void AddUser::on_pushButton_delete_clicked()
{
    QString name,password;
    name = ui->lineEdit_name->text();
    password = ui->lineEdit_password->text();

}

void AddUser::on_pushButton_view_clicked()
{

}

void AddUser::on_tableView_activated(const QModelIndex &index) {
}

void AddUser::on_pushButton_back_clicked()
{
    this->hide();
}
