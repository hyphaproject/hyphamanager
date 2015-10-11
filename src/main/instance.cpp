
#include "instance.h"

Instance::Instance(QString filename, QObject *parent): QObject(parent)
{
    this->filename = filename;
    managerSettings = new HyphaManagerSettings(filename, this);
    managerSettings->load();
    databaseSettings = new DatabaseSettings(managerSettings, this);
    database = Database::instance(databaseSettings, this);
    userDatabaseSettings = new UserDatabaseSettings(managerSettings, this);
    userDatabase = UserDatabase::instance(userDatabaseSettings, this);
    //
    handlerSettings = new HandlerSettings(database);
    pluginSettings = new PluginSettings(database);
    handlerLoader = new hypha::handler::HandlerLoader(this);
    handlerLoader->loadInstances();
    pluginLoader = new hypha::plugin::PluginLoader(pluginSettings);
    pluginLoader->loadInstances();


}

Instance::~Instance()
{
    //delete clientSettings;
    //delete databaseSettings;
    //delete userDatabase;
}

HyphaManagerSettings *Instance::getClientSettings()
{
    return managerSettings;
}

DatabaseSettings *Instance::getDatabaseSettings()
{
    return databaseSettings;
}

UserDatabase *Instance::getUserDatabase()
{
    return userDatabase;
}

Database *Instance::getDatabase()
{
    return database;
}

HandlerSettings *Instance::getHandlerSettings()
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
