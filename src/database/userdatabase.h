#ifndef USERDATABASE_H
#define USERDATABASE_H

#include <QtCore/QObject>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtCore/QList>

#include "../settings/userdatabasesettings.h"

class UserDatabase : public QObject
{
    Q_OBJECT
public:
    explicit UserDatabase(UserDatabaseSettings *settings, QObject *parent = 0);
    ~UserDatabase();
    static UserDatabase *instance(UserDatabaseSettings *settings, QObject *parent);
    virtual bool connect() = 0;
    virtual QList<QString> getUsers() = 0;
    virtual QString getFirstname(QString username) = 0;
    virtual QString getLastname(QString username) = 0;
    virtual QString getMail(QString username) = 0;
    virtual QList<QString> getDevices(QString username) = 0;
    virtual QString getOwnerOfDevice(QString device) = 0;
    virtual bool createUser(QString username, QString firstname, QString lastname, QString mail) = 0;
    virtual bool updateUser(QString username, QString firstname, QString lastname, QString mail, QString devices) = 0;


signals:

public slots:
protected:

    UserDatabaseSettings *settings;
	
};

#endif // USERDATABASE_H
