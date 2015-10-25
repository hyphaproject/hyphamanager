#include <hypha/database/database.h>
#include <hypha/database/userdatabase.h>
#include "summary.h"

Summary::Summary(hypha::database::Database *database, hypha::database::UserDatabase *userDatabase)
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
