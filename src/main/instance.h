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
}
namespace plugin {
    class PluginLoader;
}
}

class Instance : public QObject
{
    Q_OBJECT
public:
    explicit Instance(QString filename, QObject *parent = 0);
    ~Instance();

    hypha::settings::HyphaSettings * getClientSettings();
    hypha::settings::DatabaseSettings * getDatabaseSettings();
    hypha::database::UserDatabase * getUserDatabase();
    hypha::database::Database *getDatabase();
    hypha::settings::HandlerSettings * getHandlerSettings();
    hypha::handler::HandlerLoader * getHandlerLoader();
    hypha::plugin::PluginLoader * getPluginLoader();

signals:

public slots:

protected:
    QString filename;
    hypha::settings::HyphaSettings *managerSettings;
    hypha::settings::DatabaseSettings * databaseSettings;
    hypha::database::Database * database;
    hypha::settings::UserDatabaseSettings * userDatabaseSettings;
    hypha::database::UserDatabase * userDatabase;

    hypha::settings::PluginSettings * pluginSettings;
    hypha::settings::HandlerSettings * handlerSettings;

    hypha::plugin::PluginLoader * pluginLoader;
    hypha::handler::HandlerLoader * handlerLoader;

};

#endif // INSTANCE_H
