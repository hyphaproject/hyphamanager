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
  hypha::settings::PluginSettings *getPluginSettings();
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
  hypha::plugin::PluginLoader *pluginLoader;

  void initPluginLoader();
};

#endif  // INSTANCE_H
