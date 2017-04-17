// Copyright (c) 2015-2017 Hypha

#include "main/instance.h"
#include <hyphamanager/hmplugin/managerpluginloader.h>

#include <hypha/core/database/database.h>
#include <hypha/core/database/userdatabase.h>
#include <hypha/core/settings/databasesettings.h>
#include <hypha/core/settings/hyphasettings.h>
#include <hypha/core/settings/pluginsettings.h>
#include <hypha/plugin/pluginloader.h>

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
  pluginSettings = new hypha::settings::PluginSettings(database);
  initPluginLoader();
}

Instance::~Instance() {
  // delete clientSettings;
  // delete databaseSettings;
  // delete userDatabase;
}

void Instance::initPluginLoader() {
  pluginLoader = new hypha::plugin::PluginLoader(pluginSettings);
  pluginLoader->loadPlugins(
      hyphaSettings->getString("system.pluginspath", "plugins"));
  pluginLoader->loadPlugins("plugins");
#ifdef __linux__
  pluginLoader->loadPlugins("/usr/local/shared/hypha/plugins");
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

hypha::settings::PluginSettings *Instance::getPluginSettings() {
  return pluginSettings;
}

hypha::plugin::PluginLoader *Instance::getPluginLoader() {
  return pluginLoader;
}
