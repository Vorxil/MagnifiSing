#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>

class Database {

	private :
		QSqlDatabase db; // actual database

	public :
		void close(); // close connection to database
                bool open(); // open connection to database
                             // returns true on success and false on error
		~Database(); // destructor
		Database(); // constructor
};

#endif // DATABASE_H
