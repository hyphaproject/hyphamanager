#include <hypha/database/database.h>
#include <hypha/database/userdatabase.h>
#include <hypha/settings/hyphasettings.h>
#include <hypha/settings/databasesettings.h>
#include <hypha/settings/handlersettings.h>
#include <hypha/settings/pluginsettings.h>
#include <hypha/handler/handlerloader.h>
#include <hypha/plugin/pluginloader.h>
#include "instance.h"

Instance::Instance(QString filename, QObject *parent): QObject(parent)
{
    this->filename = filename;
    managerSettings = new hypha::settings::HyphaSettings(filename.toStdString());
    managerSettings->load();
    databaseSettings = new hypha::settings::DatabaseSettings(managerSettings);
    database = new hypha::database::Database(databaseSettings);
    database->connect();
    userDatabaseSettings = new hypha::settings::UserDatabaseSettings(managerSettings);
    userDatabase = hypha::database::UserDatabase::factoreInstance(userDatabaseSettings);
    //
    handlerSettings = new hypha::settings::HandlerSettings(database);
    pluginSettings = new hypha::settings::PluginSettings(database);
    handlerLoader = new hypha::handler::HandlerLoader(handlerSettings);
    handlerLoader->loadAllInstances();
    pluginLoader = new hypha::plugin::PluginLoader(pluginSettings);
    pluginLoader->loadAllInstances();

}

Instance::~Instance()
{
    //delete clientSettings;
    //delete databaseSettings;
    //delete userDatabase;
}

hypha::settings::HyphaSettings *Instance::getClientSettings()
{
    return managerSettings;
}

hypha::settings::DatabaseSettings *Instance::getDatabaseSettings()
{
    return databaseSettings;
}

hypha::database::UserDatabase *Instance::getUserDatabase()
{
    return userDatabase;
}

hypha::database::Database *Instance::getDatabase()
{
    return database;
}

hypha::settings::HandlerSettings *Instance::getHandlerSettings()
{
    return handlerSettings;
}

hypha::handler::HandlerLoader *Instance::getHandlerLoader()
{
    return handlerLoader;
}

hypha::plugin::PluginLoader *Instance::getPluginLoader()
{
    return pluginLoader;
}
