#include <QtSql>
#include <QSqlQuery>
#include <QSqlRecord>
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
	q.prepare( "INSERT INTO users ( name, realname ) VALUES (:name,:realname)");
	q.bindValue( ":name", name );
	q.bindValue( ":realname", realname );
	if ( !q.exec() ) {
		qDebug() << "Problem adding user: " << name << " " << realname;
		return false;
	}
	return true;
}


Database::~Database() {
	close();
}

Database::Database( const QString &filename ) {
	db = QSqlDatabase::addDatabase( "QSQLITE" );
	db.setDatabaseName( filename );
}

