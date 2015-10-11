#include <QtCore/QMutex>
#include <QtCore/QDebug>
#include <QtSql/QSqlError>
#include "../settings/databasesettings.h"

#include "userdbsql.h"

UserDBSql::UserDBSql(UserDatabaseSettings *settings, QObject *parent) : UserDatabase(settings, parent)
{
    this->settings = settings;

}

UserDBSql::~UserDBSql()
{
}

bool UserDBSql::connect()
{

    UserDatabaseSettings *dbs = settings;
    database = QSqlDatabase::addDatabase(dbs->getDriver(), "userdb");
    database.setDatabaseName(dbs->getDatabase());
    database.setHostName(dbs->getHost());
    database.setUserName(dbs->getUser());
    database.setPassword(dbs->getPassword());
    if(!database.open())
        return false;
    return true;
}

QSqlQuery UserDBSql::getQuery()
{
    QSqlQuery query(database);
    return query;
}

QList<QString> UserDBSql::getUsers()
{
    UserDatabaseSettings *dbs = settings;
    QSqlQuery query(database);
    query.exec("select " + dbs->getAttributeUsername() + " from "+dbs->getTable());
    QList<QString> userlist;
    while( query.next() ){
        userlist.append(query.value(0).toString());
    }
    return userlist;
}

QString UserDBSql::getFirstname(QString username)
{
    UserDatabaseSettings *dbs = settings;
    QSqlQuery query(database);
    query.exec("select " + dbs->getAttributeFirstname() + " from "+dbs->getTable() + " where " + dbs->getAttributeUsername() + " = '" + username + "'");
    while( query.next() ){
        return query.value(0).toString();
    }
    return QString();
}

QString UserDBSql::getLastname(QString username)
{
    UserDatabaseSettings *dbs = settings;
    QSqlQuery query(database);
    query.exec("select " + dbs->getAttributeLastname() + " from "+dbs->getTable() + " where " + dbs->getAttributeUsername() + " = '" + username + "'");
    while( query.next() ){
        return query.value(0).toString();
    }
    return QString();
}

QString UserDBSql::getMail(QString username)
{
    UserDatabaseSettings *dbs = settings;
    QSqlQuery query(database);
    query.exec("select " + dbs->getAttributeMail() + " from "+dbs->getTable() + " where " + dbs->getAttributeUsername() + " = '" + username + "'");
    while( query.next() ){
        return query.value(0).toString();
    }
    return QString();
}

QList<QString> UserDBSql::getDevices(QString username)
{
    UserDatabaseSettings *dbs = settings;
    QSqlQuery query(database);
    query.exec("select " + dbs->getAttributeDevices() + " from "+dbs->getTable() +" where "+ dbs->getAttributeUsername() + " = '" + username + "'");
    QList<QString> devicelist;
    while( query.next() ){
        QString devices = query.value(0).toString();
        foreach(QString device, devices.split(",")){
            devicelist.append(device);
        }
    }
    return devicelist;
}

QString UserDBSql::getOwnerOfDevice(QString device)
{
    UserDatabaseSettings *dbs = settings;
    QSqlQuery query(database);
    query.exec("select " + dbs->getAttributeUsername() + " from "+dbs->getTable() + " where " + dbs->getAttributeDevices() + " like '%" + device + "%'");
    while( query.next() ){
        return query.value(0).toString();
    }
    return QString();
}

bool UserDBSql::createUser(QString username, QString firstname, QString lastname, QString mail)
{
    UserDatabaseSettings *dbs = settings;
    QSqlQuery query(database);
    query.prepare("insert into " + dbs->getTable() + "(" + dbs->getAttributeUsername() + ", " + dbs->getAttributeFirstname() + ", " + dbs->getAttributeLastname() + ", " + dbs->getAttributeMail() + ") values(:username, :firstname, :lastname, :mail);");
    query.bindValue(":username",username);
    query.bindValue(":firstname",firstname);
    query.bindValue(":lastname",lastname);
    query.bindValue(":mail",mail);
    bool success = query.exec();
    qDebug() << query.lastError();
    return success;
}

bool UserDBSql::updateUser(QString username, QString firstname, QString lastname, QString mail, QString devices)
{
    UserDatabaseSettings *dbs = settings;
    QSqlQuery query(database);
    query.prepare("update " + dbs->getTable() + " set " + dbs->getAttributeFirstname() + "=:firstname, " +  dbs->getAttributeLastname() + "=:lastname, " + dbs->getAttributeMail() + "=:mail, "+ dbs->getAttributeDevices() + "=:devices where "+dbs->getAttributeUsername() + " = :username");
    query.bindValue(":username",username);
    query.bindValue(":firstname",firstname);
    query.bindValue(":lastname",lastname);
    query.bindValue(":mail",mail);
    query.bindValue(":devices",devices);
    bool success = query.exec();
    qDebug() << query.lastError();
    return success;
}
