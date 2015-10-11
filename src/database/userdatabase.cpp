#include <QtCore/QMutex>
#include "userdatabase.h"
#include "userdbsql.h"
#ifdef WITH_LDAP
	#include "ldap/userdbldap.h"
#endif


UserDatabase::UserDatabase(UserDatabaseSettings *settings, QObject *parent) : QObject(parent)
{
    this->settings = settings;

}

UserDatabase::~UserDatabase()
{
}

UserDatabase *UserDatabase::instance(UserDatabaseSettings *settings, QObject *parent)
{
    UserDatabase * instance;
    if(settings->getDriver() == "LDAP")
    {
#ifdef WITH_LDAP
        instance = new UserDBLDAP(settings, parent);
        instance->connect();
#else
        throw "LDAP not supported";
#endif
    } else {
        instance = new UserDBSql(settings, parent);
        instance->connect();
    }
    return instance;
}
