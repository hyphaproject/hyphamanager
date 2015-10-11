#include "summary.h"

Summary::Summary(Database *database, UserDatabase *userDatabase)
{
    this->database = database;
    this->userDatabase = userDatabase;
}

Summary::~Summary()
{

}

void Summary::setUsername(QString username)
{
    this->username = username;
}

void Summary::setDate(QDate date)
{
    this->date = date;
}
