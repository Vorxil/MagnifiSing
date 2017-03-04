#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>

#define DB_FILENAME "magnifising.db" // FIXME: later

struct FileData {
	QString filename;
	int lyrics = -1;
	int melody = -1;
};

class Database {

	private :
		QSqlDatabase db; // actual database
		void close(); // close connection to database
                bool open(); // open connection to database
                             // returns true on success and false on error
	public :
		bool addUser( const QString &name, const QString &realname );
                bool addModifyFile( const QString &filename, int lyrics, int melody );
		FileData *getFileData( const QString &filename );
		bool removeUser( const QString &name );
		QList<QString> *getUsers();
		~Database(); // destructor
		Database( const QString &filename ); // constructor
};

#endif // DATABASE_H

