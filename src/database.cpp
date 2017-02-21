#include <QtSql>
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

Database::~Database() {
	close();
}

Database::Database() {
	db = QSqlDatabase::addDatabase( "QSQLITE" );
	db.setDatabaseName( "magnifising.sqlite" );
}

