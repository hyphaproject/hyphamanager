#ifndef INSTANCE_H
#define INSTANCE_H

#include <QtCore/QObject>

#include "../settings/hyphamanagersettings.h"
#include "../database/database.h"
#include "../database/userdatabase.h"
#include "../handler/handlerloader.h"
#include "../plugin/pluginloader.h"

class HandlerSettings;

class Instance : public QObject
{
    Q_OBJECT
public:
    explicit Instance(QString filename, QObject *parent = 0);
    ~Instance();

    HyphaManagerSettings * getClientSettings();
    DatabaseSettings * getDatabaseSettings();
    UserDatabase * getUserDatabase();
    Database *getDatabase();
    HandlerSettings * getHandlerSettings();
    hypha::handler::HandlerLoader * getHandlerLoader();
    hypha::plugin::PluginLoader * getPluginLoader();

signals:

public slots:

protected:
    QString filename;
    HyphaManagerSettings *managerSettings;
    DatabaseSettings * databaseSettings;
    Database * database;
    UserDatabaseSettings * userDatabaseSettings;
    UserDatabase * userDatabase;

    PluginSettings * pluginSettings;
    HandlerSettings * handlerSettings;

    hypha::plugin::PluginLoader * pluginLoader;
    hypha::handler::HandlerLoader * handlerLoader;

};

#endif // INSTANCE_H
