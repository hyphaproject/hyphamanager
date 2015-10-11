#include <QtCore/QDir>
#include <QtCore/QPluginLoader>
#include <QtCore/QDebug>
#include <QtCore/QCoreApplication>
#include "pluginloader.h"
#include "pluginfactory.h"

using namespace hypha::plugin;


PluginLoader::PluginLoader(PluginSettings * pluginSettings, QObject *parent) : QObject(parent)
{
    this->pluginSettings = pluginSettings;
    loadPlugins(QCoreApplication::applicationDirPath());
}

PluginLoader::~PluginLoader()
{

}

void PluginLoader::loadLocalInstances()
{
    foreach(QString id, pluginSettings->getLocalPluginIds()){
        getPluginInstance(id);
    }
}

void PluginLoader::loadInstances()
{
    foreach(QString id, pluginSettings->getAllPluginIds()){
        getPluginInstance(id);
    }
}

HyphaPlugin *PluginLoader::getPlugin(QString name)
{
    foreach(HyphaPlugin * plugin, plugins){
        if(plugin->getName() == name)
            return plugin;
    }

    return 0;
}

QList<HyphaPlugin *> PluginLoader::getPlugins()
{
    return plugins;
}

QList<HyphaPlugin *> PluginLoader::getInstances()
{
    return this->pluginInstances.values();
}

HyphaPlugin *PluginLoader::getPluginInstance(QString id)
{
    PluginFactory factory(pluginSettings);
    HyphaPlugin * ret = 0;
    ret = this->pluginInstances[id];
    if(!ret){
        ret = factory.loadPlugin(id, parent());
        if(ret)
            pluginInstances.insert(id, ret);
        else
            pluginInstances.remove(id);
    }
    return ret;
}

void PluginLoader::loadPlugins(QString dir)
{
    QDir pluginsDir(dir);
    if (pluginsDir.exists(dir)) {
#ifdef Q_OS_WIN32
        if(!pluginsDir.cd("plugins"))
            return;
#else
        if (!pluginsDir.cd("../plugins")){
            if(!pluginsDir.cd("../bin"))
                return;
        }
#endif
    }
    foreach (QString fileName, pluginsDir.entryList(QDir::Files))
    {
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader.instance();
        if (plugin) {
            HyphaPlugin *plugin_ = qobject_cast<
                    HyphaPlugin *> (plugin);
            if (plugin_) {
                this->plugins.append(plugin_);
            } else {

                delete plugin_;
            }
        }else{
        }
    }
}
