#include "manageuser.h"
#include "ui_manageuser.h"
#include "startsingingview.h"
#include <QMessageBox>

ManageUser::ManageUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManageUser)
{
    ui->setupUi(this);
    QPixmap background(":/images/background.jpg");
    QPalette palette;
    palette.setBrush(QPalette::Background, background);
    this->setPalette(palette);
}

ManageUser::~ManageUser()
{
    delete ui;
}
void ManageUser::resizeEvent(QResizeEvent *event){
    QPixmap background(":/images/background.jpg");
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, background);
    this->setPalette(p);
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
