#ifndef USERDBSQL_H
#define USERDBSQL_H

#include <QtCore/QObject>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

#include "userdatabase.h"

class UserDBSql : public UserDatabase
{
public:
    UserDBSql(UserDatabaseSettings *settings, QObject *parent = 0);
    ~UserDBSql();
    static UserDBSql* instance();
    QSqlQuery getQuery();
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

    QSqlDatabase database;
    QString host;

};

#endif // USERDBSQL_H
