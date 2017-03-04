#include "adduser.h"
#include "ui_adduser.h"
#include <QMessageBox>
#include "database.h"

AddUser::AddUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUser)
{
    ui->setupUi(this);
}

AddUser::~AddUser()
{
    delete ui;
}

void AddUser::on_pushButton_save_clicked()
{
    ManageUser con;
    QString name,password, realname;
    name = ui->lineEdit_name->text();
    password = ui->lineEdit_password->text();
    realname = ui->lineEdit_realname->text();

    Database d( DB_FILENAME );
    d.addUser( name, password, realname );
}


void AddUser::on_pushButton_delete_clicked()
{
    ManageUser con;
    QString name,password;
    name = ui->lineEdit_name->text();
    password = ui->lineEdit_password->text();

    if (!con.connOpen())
    {
        qDebug() << "Database connection failed!";
        return;
    }

    con.connOpen();
    QSqlQuery query;
    query.prepare("Delete from user where user_name = '"+name+"'");
    QMessageBox::critical(this,tr("Warning!"),tr("Delete this user?"));

    if(query.exec())
    {
      QMessageBox::about(this,tr("Delete"),tr("User information deleted"));
      con.connClose();
      ui->lineEdit_name->clear();
      ui->lineEdit_password->clear();
    }
    else
    {
        QMessageBox::critical(this,tr("Error:"),query.lastError().text());
    }
}

void AddUser::on_pushButton_view_clicked()
{
    ManageUser con;
    QSqlQueryModel *table = new QSqlQueryModel();
    con.connOpen();

    QSqlQuery * query = new QSqlQuery(con.db);
    query->prepare("Select user_name from user");
    query->exec();

    table->setQuery(*query);
    ui->tableView->setModel(table);

    con.connClose();
    qDebug() << (table->rowCount());

}

void AddUser::on_tableView_activated(const QModelIndex &index)
{
    QString str = ui->tableView->model()->data(index).toString();

    ManageUser con;
    if (!con.connOpen())
    {
        qDebug() << "Database connection failed!";
        return;
    }

    con.connOpen();
    QSqlQuery query;
    query.prepare("Select * from user where user_name = '"+str+"'");

    if(query.exec())
    {
        while(query.next())
        {
            ui->lineEdit_name->setText(query.value(1).toString());
            ui->lineEdit_password->setText(query.value(2).toString());
        }
        con.connClose();
    }
    else
    {
        QMessageBox::critical(this,tr("Error:"),query.lastError().text());
    }
}

void AddUser::on_pushButton_back_clicked()
{
    this->hide();
    ManageUser mnguser;
    mnguser.setModal(true);
    mnguser.exec();
}
