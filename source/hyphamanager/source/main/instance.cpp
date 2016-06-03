#include "main/instance.h"
#include <hypha/core/database/database.h>
#include <hypha/core/database/userdatabase.h>
#include <hypha/core/settings/databasesettings.h>
#include <hypha/core/settings/handlersettings.h>
#include <hypha/core/settings/hyphasettings.h>
#include <hypha/core/settings/pluginsettings.h>
#include <hypha/handler/handlerloader.h>
#include <hypha/plugin/pluginloader.h>
#include <hyphamanager/hmhandler/managerhandlerloader.h>
#include <hyphamanager/hmplugin/managerpluginloader.h>

Instance::Instance(QString filename, QObject *parent) : QObject(parent) {
  this->filename = filename;
  hyphaSettings = new hypha::settings::HyphaSettings(filename.toStdString());
  hyphaSettings->load();
  databaseSettings = new hypha::settings::DatabaseSettings(hyphaSettings);
  database = new hypha::database::Database(databaseSettings);
  database->connect();
  userDatabaseSettings =
      new hypha::settings::UserDatabaseSettings(hyphaSettings);
  userDatabase =
      hypha::database::UserDatabase::factoreInstance(userDatabaseSettings);
  //
  handlerSettings = new hypha::settings::HandlerSettings(database);
  pluginSettings = new hypha::settings::PluginSettings(database);
  initHandlerLoader();
  initPluginLoader();
}

Instance::~Instance() {
  // delete clientSettings;
  // delete databaseSettings;
  // delete userDatabase;
}

void Instance::initHandlerLoader() {
  handlerLoader = new hypha::handler::ManagerHandlerLoader(handlerSettings);
  handlerLoader->loadHandlers(
      hyphaSettings->getString("system.handlerspath", "handlers"));
  handlerLoader->loadHandlers("handlers");
#ifdef __linux__
  pluginLoader->loadPlugins("/usr/local/lib/hyphamanager/handlers");
#else
// on windows the plugins folder should be relative to executable
#endif
  handlerLoader->loadAllInstances();
}

void Instance::initPluginLoader() {
  pluginLoader = new hypha::plugin::ManagerPluginLoader(pluginSettings);
  pluginLoader->loadPlugins(
      hyphaSettings->getString("system.pluginspath", "plugins"));
  pluginLoader->loadPlugins("plugins");
#ifdef __linux__
  pluginLoader->loadPlugins("/usr/local/lib/hyphamanager/plugins");
#else
// on windows the plugins folder should be relative to executable
#endif
  pluginLoader->loadAllInstances();
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

hypha::database::Database *Instance::getDatabase() { return database; }

hypha::settings::HandlerSettings *Instance::getHandlerSettings() {
  return handlerSettings;
}

hypha::settings::PluginSettings *Instance::getPluginSettings() {
  return pluginSettings;
}

hypha::handler::HandlerLoader *Instance::getHandlerLoader() {
  return handlerLoader;
}

hypha::plugin::PluginLoader *Instance::getPluginLoader() {
  return pluginLoader;
}
