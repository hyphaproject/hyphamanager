#include <QtCore/QMutex>
#include "../settings/databasesettings.h"
#include "database.h"
#include "blechuhr/model/type.h"


Database::Database(DatabaseSettings * settings, QObject *parent) : QObject(parent)
{
    this->settings = settings;
}

Database::~Database()
{
}

Database *Database::instance(DatabaseSettings *settings, QObject *parent)
{
    Database * instance;
    instance = new Database(settings, parent);
    instance->connect();
    return instance;
}


void Database::createTables()
{
    QSqlQuery query(database);
    query.exec("CREATE TABLE IF NOT EXISTS `deviceonline` ("
               "`id` int(11) NOT NULL AUTO_INCREMENT,"
               "`deviceid` varchar(45) DEFAULT NULL,"
               "`time` datetime NOT NULL,"
               "PRIMARY KEY (`id`)"
               ") DEFAULT CHARSET=utf8;");

    query.exec("CREATE TABLE IF NOT EXISTS handler ("
               "id varchar(32) NOT NULL,"
               "host varchar(128) NOT NULL DEFAULT 'localhost',"
               "type varchar(32) NOT NULL,"
               "config varchar(1024) NOT NULL,"
               "PRIMARY KEY (id)"
               ") DEFAULT CHARSET=utf8;");

    query.exec("CREATE TABLE IF NOT EXISTS `plugins` ("
               "`id` varchar(32) NOT NULL,"
               "`host` varchar(128) NOT NULL DEFAULT 'localhost',"
               "type varchar(32) NOT NULL,"
               "`config` varchar(1024) NOT NULL,"
               "PRIMARY KEY (`id`)"
               ") DEFAULT CHARSET=utf8;");

    query.exec("CREATE TABLE IF NOT EXISTS connection ("
               "`id` int(11) NOT NULL AUTO_INCREMENT,"
               "handler_id varchar(32) NOT NULL,"
               "plugin_id varchar(32) NOT NULL,"
               "PRIMARY KEY (id)"
               ") DEFAULT CHARSET=utf8;");

    std::string types = "";
    for(const auto& t : hypha::blechuhr::TYPE()) {
        types += "'" + hypha::blechuhr::TypeToString(t) + "'";
        if(t != hypha::blechuhr::TYPE::LAST)
            types += ",";
    }

    query.exec("CREATE TABLE IF NOT EXISTS `workingtime` ("
               "`id` int(11) NOT NULL AUTO_INCREMENT, "
               "`username` varchar(45) DEFAULT NULL, "
               "`type` ENUM("+QString::fromStdString(types)+
               ") DEFAULT 'working', "
               "`start` datetime NOT NULL, "
               "`end` datetime NOT NULL, "
               "PRIMARY KEY (`id`) "
               ") DEFAULT CHARSET=utf8;");

    query.exec("CREATE TABLE IF NOT EXISTS `account` ("
               "`id` int(11) NOT NULL AUTO_INCREMENT, "
               "`username` varchar(45) DEFAULT NULL, "
               "`type` ENUM("+QString::fromStdString(types)+
               ") DEFAULT 'working', "
               "`start` datetime NOT NULL, "
               "`end` datetime NOT NULL, "
               "`amount` float NOT NULL, "
               "`name` varchar(128), "
               "PRIMARY KEY (`id`) "
               ") DEFAULT CHARSET=utf8;");

    std::string itypes = "";
    for(const auto& t : hypha::blechuhr::ITYPE()) {
        itypes += "'" + hypha::blechuhr::ITypeToString(t) + "'";
        if(t != hypha::blechuhr::ITYPE::LAST)
            itypes += ",";
    }

    query.exec("CREATE TABLE IF NOT EXISTS `iterativeaccount` ("
               "`id` int(11) NOT NULL AUTO_INCREMENT, "
               "`username` varchar(45) DEFAULT NULL, "
               "`type` ENUM("+QString::fromStdString(itypes)+
               ") DEFAULT 'workingsun', "
               "`start` datetime NOT NULL, "
               "`end` datetime NOT NULL, "
               "`starttime` time NOT NULL, "
               "`endtime` time NOT NULL, "
               "PRIMARY KEY (`id`) "
               ") DEFAULT CHARSET=utf8;");

    std::string rtypes = "";
    for(const auto& t : hypha::blechuhr::RTYPE()) {
        rtypes += "'" + hypha::blechuhr::RTypeToString(t) + "'";
        if(t != hypha::blechuhr::RTYPE::LAST)
            rtypes += ",";
    }

    query.exec("CREATE TABLE IF NOT EXISTS `rules` ("
               "`id` int(11) NOT NULL AUTO_INCREMENT, "
               "`username` varchar(45) DEFAULT NULL, "
               "`type` ENUM("+QString::fromStdString(rtypes)+
               ") DEFAULT 'working', "
               "`start` datetime NOT NULL, "
               "`end` datetime NOT NULL, "
               "PRIMARY KEY (`id`) "
               ") DEFAULT CHARSET=utf8;");

    query.exec("CREATE TABLE IF NOT EXISTS `designerpositions` ("
               "`id` varchar(32) NOT NULL, "
               "`x` int(11) DEFAULT 0, "
               "`y` int(11) DEFAULT 0, "
               "PRIMARY KEY (`id`) "
               ") DEFAULT CHARSET=utf8;");
}


bool Database::connect()
{
    DatabaseSettings *dbs = settings;
    database = QSqlDatabase::addDatabase(dbs->getDriver(), "hypha");
    database.setDatabaseName(dbs->getDatabase());
    if(dbs->getDriver() != "QSQLITE")
    {
        database.setHostName(dbs->getHost());
        database.setUserName(dbs->getUser());
        database.setPassword(dbs->getPassword());
    }
    if(!database.open())
        return false;
    createTables();
    return true;
}

QSqlQuery Database::getQuery()
{
    QSqlQuery query(database);
    return query;
}

