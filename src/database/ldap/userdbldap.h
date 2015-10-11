#ifndef USERDBLDAP_H
#define USERDBLDAP_H

#include <QtCore/QObject>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

#include "../userdatabase.h"
#include <ldap.h>

class UserDBLDAP : public UserDatabase
{
public:
    UserDBLDAP(UserDatabaseSettings *settings, QObject *parent = 0);
    ~UserDBLDAP();
    bool connect();
    QList<QString> getUsers();
    QString getFirstname(QString username);
    QString getLastname(QString username);
    QString getMail(QString username);
    QList<QString> getDevices(QString username);
    QString getOwnerOfDevice(QString device);
    bool createUser(QString username, QString firstname, QString lastname, QString mail);
    bool updateUser(QString username, QString firstname, QString lastname, QString mail, QString devices);


signals:

public slots:
protected:
    LDAP *ld;

};

#endif // USERDBLDAP_H
