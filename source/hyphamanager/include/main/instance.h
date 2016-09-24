// Copyright (c) 2015-2016 Hypha
#ifndef INSTANCE_H
#define INSTANCE_H

#include <QtCore/QObject>

namespace hypha {
namespace database {
class Database;
class UserDatabase;
}
namespace settings {
class HyphaSettings;
class DatabaseSettings;
class UserDatabaseSettings;
class HandlerSettings;
class PluginSettings;
}
namespace handler {
class HandlerLoader;
class ManagerHandlerLoader;
}
namespace plugin {
class PluginLoader;
class ManagerPluginLoader;
}
}

class Instance : public QObject {
  Q_OBJECT
 public:
  explicit Instance(QString filename, QObject *parent = 0);
  ~Instance();

  hypha::settings::HyphaSettings *getClientSettings();
  hypha::settings::DatabaseSettings *getDatabaseSettings();
  hypha::database::UserDatabase *getUserDatabase();
  hypha::database::Database *getDatabase();
  hypha::settings::HandlerSettings *getHandlerSettings();
  hypha::settings::PluginSettings *getPluginSettings();
  hypha::handler::HandlerLoader *getHandlerLoader();
  hypha::plugin::PluginLoader *getPluginLoader();

 signals:

 public slots:

 protected:
  QString filename;
  hypha::settings::HyphaSettings *hyphaSettings;
  hypha::settings::DatabaseSettings *databaseSettings;
  hypha::database::Database *database;
  hypha::settings::UserDatabaseSettings *userDatabaseSettings;
  hypha::database::UserDatabase *userDatabase;

  hypha::settings::PluginSettings *pluginSettings;
  hypha::settings::HandlerSettings *handlerSettings;

  hypha::plugin::ManagerPluginLoader *pluginLoader;
  hypha::handler::ManagerHandlerLoader *handlerLoader;

  void initHandlerLoader();
  void initPluginLoader();
};

#endif  // INSTANCE_H
