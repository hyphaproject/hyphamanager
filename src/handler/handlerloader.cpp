#include <QtCore/QDir>
#include <QtCore/QPluginLoader>
#include <QtCore/QDebug>
#include <QtCore/QCoreApplication>
#include "../settings/handlersettings.h"
#include "main/instance.h"
#include "handlerloader.h"
#include "handlerfactory.h"
#include <iostream>

using namespace hypha::handler;

HandlerLoader::HandlerLoader(Instance *instance, QObject *parent) : QObject(parent)
{
    this->instance = instance;
    loadHandlers(QCoreApplication::applicationDirPath());
}

HandlerLoader::~HandlerLoader()
{

}

void HandlerLoader::loadLocalInstances()
{
    foreach(QString id, instance->getHandlerSettings()->getLocalHandlerIds()){
       getHandlerInstance(id);
    }
}

void HandlerLoader::loadInstances()
{
    foreach(QString id, instance->getHandlerSettings()->getAllHandlerIds()){
       getHandlerInstance(id);
    }
}

HyphaHandler *HandlerLoader::getHandler(QString name)
{
    foreach(HyphaHandler * plugin, handlers){
        if(plugin->getName() == name)
            return plugin;
    }
    return 0;
}

QList<HyphaHandler *> HandlerLoader::getHandlers()
{
    return handlers;
}

QList<HyphaHandler *> HandlerLoader::getInstances()
{
    return handlerInstances.values();
}

HyphaHandler *HandlerLoader::getHandlerInstance(QString id)
{
    HandlerFactory factory(instance);
    HyphaHandler * ret = 0;
    ret = this->handlerInstances[id];
    if(!ret){
        ret = factory.loadHandler(id, parent());
        if(ret)
            handlerInstances.insert(id, ret);
        else
            handlerInstances.remove(id);
    }
    return ret;
}

void HandlerLoader::loadHandlers(QString dir)
{
    QDir handlersDir(dir);

    if (handlersDir.exists(dir)) {
#ifdef Q_OS_WIN32
        if(!handlersDir.cd("plugins"))
            return;
#else
        if (!handlersDir.cd("../plugins"))
            return;
#endif
    }

    foreach (QString fileName, handlersDir.entryList(QDir::Files))
    {
        QPluginLoader handlerLoader(handlersDir.absoluteFilePath(fileName));
        QObject *plugin = handlerLoader.instance();
        if (plugin) {
            HyphaHandler *plugin_ = qobject_cast<
                    HyphaHandler *> (plugin);
            if (plugin_) {
                this->handlers.append(plugin_);
            } else {
                delete plugin_;
            }
        }else{
        }
    }
}
