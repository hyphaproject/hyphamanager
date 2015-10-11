#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

#include <QtCore/QObject>
#include <QtCore/QSettings>
#include <QtCore/QMutex>
#include <QtCore/QList>
#include <QtCore/QMap>
#include "hyphaplugin.h"
#include "../settings/pluginsettings.h"

namespace hypha{
namespace plugin{
class PluginLoader : public QObject
{
    Q_OBJECT
public:
    explicit PluginLoader(PluginSettings * pluginSettings, QObject *parent = 0);
    ~PluginLoader();

    void loadLocalInstances();
    void loadInstances();

    HyphaPlugin* getPlugin(QString name);
    QList<HyphaPlugin *> getPlugins();


    QList<HyphaPlugin *> getInstances();
    HyphaPlugin *getPluginInstance(QString id);

signals:

public slots:

private:
    PluginSettings *pluginSettings;

    QList<HyphaPlugin *> plugins;
    QMap<QString, HyphaPlugin *> pluginInstances;
    void loadPlugins(QString dir);

};
}
}

#endif // PLUGINLOADER_H
