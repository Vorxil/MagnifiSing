#include <QtSql>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QFileInfo>
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

bool Database::addModifyFile( const QString &filename, int lyrics, int melody ) {
	if ( !open() ) {
		return false;
	}
	QFileInfo file( filename );
	QSqlQuery q;
	q.prepare( "SELECT COUNT(*) FROM files where filename=:filename" );
	q.bindValue( ":filename", file.absoluteFilePath() );
	if ( !q.exec() ) {
		qDebug() << "Problem getting id from files table based on filename: " << filename;
		return false;
	}
	q.first();
	int size = q.value( 0 ).toInt();
	q.finish();
	if ( size == 0 ) {
		q.prepare( "INSERT INTO files ( filename, lyrics, melody ) values ( :filename, :lyrics, :melody )" );
	} else {
		q.prepare( "UPDATE files SET lyrics=:lyrics, melody=:melody WHERE filename=:filename" );
	}
	q.bindValue( ":lyrics", lyrics );
	q.bindValue( ":melody", melody );
	q.bindValue( ":filename", file.absoluteFilePath() );
	if ( !q.exec() ) {
		qDebug() << "Problem addmodifying files table";
		return false;
	}
	return true;
}

FileData *Database::getFileData( const QString &filename ) {
	FileData *fileData = new FileData;
	fileData->filename = filename;
	if ( !open() ) {
		return fileData;
	}
	QFileInfo file( filename );
	QSqlQuery q;
	q.prepare( "SELECT * FROM files WHERE filename=:filename" );
	q.bindValue( ":filename", file.absoluteFilePath() );
	if ( !q.exec() ) {
		qDebug() << "Problem getting file data for filename " << filename;
	}
	int melodyIndex = q.record().indexOf( "melody" );
	int lyricsIndex = q.record().indexOf( "lyrics" );
	if ( !q.next() ) {
		qDebug() << "No rows found in database contining filename " << filename;
	} else {
		fileData->melody = q.value( melodyIndex ).toInt();
		fileData->lyrics = q.value( lyricsIndex ).toInt();
	}
	return fileData;
}

Database::~Database() {
	close();
}

Database::Database( const QString &filename ) {
	db = QSqlDatabase::addDatabase( "QSQLITE" );
	db.setDatabaseName( filename );
}

