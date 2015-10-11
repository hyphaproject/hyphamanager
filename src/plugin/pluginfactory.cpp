#include <QtCore/QMutex>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include <QtCore/QDateTime>
#include <QtCore/QThread>
#include "pluginfactory.h"
#include "pluginloader.h"


using namespace hypha::plugin;

PluginFactory::PluginFactory(PluginSettings * pluginSettings, QObject *parent) : QObject(parent)
{
    this->pluginSettings = pluginSettings;
}

PluginFactory::~PluginFactory()
{

}

HyphaPlugin *PluginFactory::create()
{
    PluginLoader pluginLoader(pluginSettings);
    HyphaPlugin * p = pluginLoader.getPlugin(pluginSettings->getName(id));
    if(p){
        HyphaPlugin *plugin = p->getInstance(id, parent());
        plugin->setHost(pluginSettings->getHost(id));
        plugin->loadConfig(config);
        return plugin;
    }else{
        return 0;
    }
}

HyphaPlugin *PluginFactory::loadPlugin(QString id, QObject *parent)
{
    if(!pluginSettings->exists(id))
        return 0;
    PluginFactory factory(pluginSettings, parent);
    factory.setId(id);
    factory.setHost(pluginSettings->getHost(id));
    factory.setConfig(pluginSettings->getConfig(id));
    return factory.create();
}

void PluginFactory::setId(QString id)
{
    this->id = id;
}

void PluginFactory::setHost(QString host)
{
    this->host = host;
}

void PluginFactory::setConfig(QString config)
{
    this->config = config;
}
