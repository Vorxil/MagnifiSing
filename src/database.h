#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>

#define DB_FILENAME "magnifising.db" // FIXME: later

class Database {

	private :
		QSqlDatabase db; // actual database
		void close(); // close connection to database
                bool open(); // open connection to database
                             // returns true on success and false on error
	public :
		bool addUser( const QString &name, const QString &realname );
		bool removeUser( const QString &name );
		~Database(); // destructor
		Database( const QString &filename ); // constructor
};

#endif // DATABASE_H

