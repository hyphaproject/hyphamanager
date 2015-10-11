#include <QtCore/QFileInfo>
#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtNetwork/QHostInfo>

#include "handlersettings.h"

HandlerSettings::HandlerSettings(Database * database, QObject *parent) : QObject(parent)
{
    this->database = database;
}

HandlerSettings::~HandlerSettings()
{

}

QList<QString> HandlerSettings::getAllHandlerIds()
{
    QList<QString> plugins;
    QSqlQuery query = database->getQuery();
    query.exec("SELECT id FROM handler");
    while( query.next() ){
        plugins.append(query.value(0).toString());
    }
    return plugins;
}

QList<QString> HandlerSettings::getLocalHandlerIds()
{
    QList<QString> plugins;
    QSqlQuery query = database->getQuery();
    query.exec("SELECT id FROM handler WHERE host='" + QHostInfo::localHostName() + "'");
    while( query.next() ){
        plugins.append(query.value(0).toString());
    }
    return plugins;
}

QString HandlerSettings::getName(QString id)
{
    QSqlQuery query = database->getQuery();
    query.exec("SELECT type FROM handler WHERE id='" + id + "'");
    while( query.next() ){
        return query.value(0).toString();
    }
    return "";
}

QString HandlerSettings::getHost(QString id)
{
    QSqlQuery query = database->getQuery();
    query.exec("SELECT host FROM handler WHERE id='" + id + "'");
    while( query.next() ){
        return query.value(0).toString();
    }
    return "";
}

QString HandlerSettings::getConfig(QString id)
{
    QSqlQuery query = database->getQuery();
    query.exec("SELECT config FROM handler WHERE id='" + id + "'");
    while( query.next() ){
        return query.value(0).toString();
    }
    return "";
}

bool HandlerSettings::exists(QString id)
{
    return getName(id) != "";
}

