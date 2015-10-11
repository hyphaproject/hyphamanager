#include <QtCore/QFileInfo>
#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtNetwork/QHostInfo>

#include "pluginsettings.h"

PluginSettings::PluginSettings(Database * database, QObject *parent) : QObject(parent)
{
    this->database = database;
}

PluginSettings::~PluginSettings()
{

}

QList<QString> PluginSettings::getAllPluginIds()
{
    QList<QString> plugins;
    QSqlQuery query = database->getQuery();
    query.exec("SELECT id FROM plugins");
    while( query.next() ){
        plugins.append(query.value(0).toString());
    }
    return plugins;
}

QList<QString> PluginSettings::getLocalPluginIds()
{
    QList<QString> plugins;
    QSqlQuery query = database->getQuery();
    query.exec("SELECT id FROM plugins WHERE host='" + QHostInfo::localHostName() + "'");
    while( query.next() ){
        plugins.append(query.value(0).toString());
    }
    return plugins;
}

QString PluginSettings::getName(QString id)
{
    QSqlQuery query = database->getQuery();
    query.exec("SELECT type FROM plugins WHERE id='" + id + "'");
    while( query.next() ){
        return query.value(0).toString();
    }
    return "";
}

QString PluginSettings::getHost(QString id)
{
    QSqlQuery query = database->getQuery();
    query.exec("SELECT host FROM plugins WHERE id='" + id + "'");
    while( query.next() ){
        return query.value(0).toString();
    }
    return "";
}

QString PluginSettings::getConfig(QString id)
{
    QSqlQuery query = database->getQuery();
    query.exec("SELECT config FROM plugins WHERE id='" + id + "'");
    while( query.next() ){
        return query.value(0).toString();
    }
    return "";
}

bool PluginSettings::exists(QString id)
{
    return getName(id) != "";
}

