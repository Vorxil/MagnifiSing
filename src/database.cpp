#include <QtSql>
#include <QSqlQuery> #include <QSqlRecord>
#include <QDebug>
#include "database.h"

/**
 * Database is a class for managing database operations
 * @author Fredrik Byggmästar
 */

void Database::close() {
	db.close();
	db.removeDatabase( QSqlDatabase::defaultConnection );
}

bool Database::open() {
	if ( !db.open() ) {
		qDebug() << "Unable to open database: " << db.databaseName();
		return false;
	}
	qDebug() << "db was successfully opened";
	return true;
}

bool Database::addUser( const QString &name, const QString &realname ) {

	if ( name.isEmpty() || realname.isEmpty() ) {
		qDebug() << "name or realname can not be empty";
		return false;
	}
	if ( !open() ) {
		return false;
	}

	QSqlQuery q;
	q.prepare( "INSERT INTO users ( name, realname ) VALUES ( :name, :realname )");
	q.bindValue( ":name", name );
	q.bindValue( ":realname", realname );
	if ( !q.exec() ) {
		qDebug() << "Problem adding user: " << name << " " << realname;
		return false;
	}
	return true;
}

bool Database::removeUser( const QString &name ) {
	if ( name.isEmpty() ) {
		qDebug() << "name can not be empty";
		return false;
	}
	if ( !open() ) {
		return false;
	}
	QSqlQuery q;
	q.prepare( "DELETE FROM users where name=:name" );
	q.bindValue( ":name", name );
	if ( !q.exec() ) {
		qDebug() << "Problem removing user: " << name;
		return false;
	}
	return true;
}


QList<QString> *Database::getUsers() {
	QList<QString> *users = new QList<QString>();
	if ( !open() ) {
		return users;
	}
	QSqlQuery q( "SELECT name FROM users" );
	int i = q.record().indexOf( "name" );
	while ( q.next() ) {
		QString name = q.value( i ).toString();
		users->append( name );
	}
	return users;
}

Database::~Database() {
	close();
}

Database::Database( const QString &filename ) {
	db = QSqlDatabase::addDatabase( "QSQLITE" );
	db.setDatabaseName( filename );
}

