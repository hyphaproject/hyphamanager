#ifndef PLUGINFACTORY_H
#define PLUGINFACTORY_H

#include <QtCore/QObject>
#include "hyphaplugin.h"

#include "../settings/pluginsettings.h"

namespace hypha{
namespace plugin{

class PluginFactory : public QObject
{
    Q_OBJECT
public:
    explicit PluginFactory(PluginSettings *pluginSettings, QObject *parent = 0);
    ~PluginFactory();

signals:

public slots:
public:
    HyphaPlugin *loadPlugin(QString id, QObject *parent);

    void setId(QString id);
    void setHost(QString host);
    void setConfig(QString config);

private:

    PluginSettings *pluginSettings;

    QString id;
    QString host;
    QString config;
    HyphaPlugin *create();

};
}
}

#endif // PLUGINFACTORY_H
