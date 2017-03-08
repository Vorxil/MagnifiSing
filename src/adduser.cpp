#include "adduser.h"
#include "ui_adduser.h"
#include <QMessageBox>
#include <QTableView>
#include <QStandardItemModel>
#include "database.h"
#include "mainmenuview.h"

extern Database *db;


void AddUser::updateUsers() {
    QList<QString> *users = db->getUsers();
    QStandardItemModel *model = new QStandardItemModel( users->size(), 1, this );
    for ( int i = 0; i < users->size(); i++ ) {
        QStandardItem *item1 = new QStandardItem( users->at( i ) );
        model->setItem( i, 0, item1 );
    }
    ui->usersTable->setModel( model );
}

void AddUser::editState() {
    ui->pushButton_save->setEnabled( true );
    ui->pushButton_create->setEnabled( false );

    ui->lineEdit_name->setEnabled( false );
}

void AddUser::createState() {
    ui->pushButton_save->setEnabled( false );
    ui->pushButton_create->setEnabled( true );

    ui->lineEdit_name->setEnabled( true );
    ui->lineEdit_name->setText( "" );
    ui->lineEdit_password->setText( "" );
    ui->lineEdit_realname->setText( "" );
}

AddUser::AddUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUser)
{
    ui->setupUi(this);
    QPixmap background(":/images/background.jpg");
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, background);
    this->setPalette(palette);

    updateUsers();
    createState();

    connect( ui->usersTable, SIGNAL( clicked( const QModelIndex & ) ), this, SLOT( onUserTableClicked( const QModelIndex & ) ) );
    connect( ui->pushButton_create, SIGNAL( pressed() ), this, SLOT( onCreateUserClicked() ) );
    connect( ui->pushButton_plus, SIGNAL( pressed() ), this, SLOT( onPlusClicked() ) );

}

AddUser::~AddUser()
{
    delete ui;
}

void AddUser::resizeEvent(QResizeEvent *event){
    QPixmap background(":/images/background.jpg");
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, background);
    this->setPalette(p);
}

void AddUser::onCreateUserClicked() {
    QString name,password, realname;
    name = ui->lineEdit_name->text();
    password = ui->lineEdit_password->text();
    realname = ui->lineEdit_realname->text();
    db->addUser( name, password, realname );
    updateUsers();
    editState();
}

void AddUser::onUserTableClicked( const QModelIndex &index ) {
	if ( index.isValid() ) {
		QString name = index.data().toString();
		UserData *userData = db->getUserData( index.data().toString() );
    		ui->lineEdit_name->setText( userData->name );
   		ui->lineEdit_password->setText( userData->password );
    		ui->lineEdit_realname->setText( userData->realname );
		editState();
	}
}

void AddUser::on_pushButton_save_clicked()
{
    QString name,password, realname;
    name = ui->lineEdit_name->text();
    password = ui->lineEdit_password->text();
    realname = ui->lineEdit_realname->text();
    db->modifyUser( name, password, realname );
    updateUsers();
    editState();
}


void AddUser::onPlusClicked() {
    createState();
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
