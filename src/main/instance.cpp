#include <hypha/core/database/database.h>
#include <hypha/core/database/userdatabase.h>
#include <hypha/core/settings/hyphasettings.h>
#include <hypha/core/settings/databasesettings.h>
#include <hypha/core/settings/handlersettings.h>
#include <hypha/core/settings/pluginsettings.h>
#include <hypha/handler/handlerloader.h>
#include <hypha/plugin/pluginloader.h>
#include "handler/managerhandlerloader.h"
#include "plugin/managerpluginloader.h"
#include "instance.h"

Instance::Instance(QString filename, QObject *parent): QObject(parent) {
    this->filename = filename;
    hyphaSettings = new hypha::settings::HyphaSettings(filename.toStdString());
    hyphaSettings->load();
    databaseSettings = new hypha::settings::DatabaseSettings(hyphaSettings);
    database = new hypha::database::Database(databaseSettings);
    database->connect();
    userDatabaseSettings = new hypha::settings::UserDatabaseSettings(hyphaSettings);
    userDatabase = hypha::database::UserDatabase::factoreInstance(userDatabaseSettings);
    //
    handlerSettings = new hypha::settings::HandlerSettings(database);
    pluginSettings = new hypha::settings::PluginSettings(database);
    handlerLoader = new hypha::handler::ManagerHandlerLoader(handlerSettings);
    handlerLoader->loadHandlers(hyphaSettings->getString("system.handlerspath", "plugins"));
    handlerLoader->loadAllInstances();
    pluginLoader = new hypha::plugin::ManagerPluginLoader(pluginSettings);
    std::string pluginspath = hyphaSettings->getString("system.pluginspath", "plugins");
    pluginLoader->loadPlugins(pluginspath);
    pluginLoader->loadAllInstances();

}

Instance::~Instance() {
    //delete clientSettings;
    //delete databaseSettings;
    //delete userDatabase;
}

hypha::settings::HyphaSettings *Instance::getClientSettings() {
    return hyphaSettings;
}

hypha::settings::DatabaseSettings *Instance::getDatabaseSettings() {
    return databaseSettings;
}

hypha::database::UserDatabase *Instance::getUserDatabase() {
    return userDatabase;
}

hypha::database::Database *Instance::getDatabase() {
    return database;
}

hypha::settings::HandlerSettings *Instance::getHandlerSettings() {
    return handlerSettings;
}

hypha::settings::PluginSettings *Instance::getPluginSettings()
{
    return pluginSettings;
}

hypha::handler::HandlerLoader *Instance::getHandlerLoader() {
    return handlerLoader;
}

hypha::plugin::PluginLoader *Instance::getPluginLoader() {
    return pluginLoader;
}
