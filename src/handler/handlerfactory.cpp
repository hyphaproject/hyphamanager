#include <QtCore/QMutex>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include <QtCore/QDateTime>
#include <QtCore/QThread>
#include "handlerfactory.h"
#include "../settings/handlersettings.h"
#include "../handler/handlerloader.h"
#include "../main/instance.h"


using namespace hypha::handler;

HandlerFactory::HandlerFactory(Instance * instance, QObject *parent) : QObject(parent)
{
    this->instance = instance;
}

HandlerFactory::~HandlerFactory()
{

}

HyphaHandler *HandlerFactory::create()
{
    HandlerLoader handlerLoader(0);
    HyphaHandler * handler = handlerLoader.getHandler(instance->getHandlerSettings()->getName(id));
    if(handler){
        HyphaHandler *plugin = handler->getInstance(id, parent());
        plugin->setHost(instance->getHandlerSettings()->getHost(id));
        plugin->setDatabase(instance->getDatabase());
        plugin->setUserDatabase(instance->getUserDatabase());
        plugin->loadConfig(instance->getHandlerSettings()->getConfig(id));
        return plugin;
    }else{
        return 0;
    }
}

HyphaHandler *HandlerFactory::loadHandler(QString id, QObject *parent)
{
    if(!instance->getHandlerSettings()->exists(id))
        return 0;
    HandlerFactory factory(instance, parent);
    factory.setId(id);
    factory.setHost(instance->getHandlerSettings()->getHost(id));
    factory.setConfig(instance->getHandlerSettings()->getConfig(id));
    return factory.create();
}

void HandlerFactory::setId(QString id)
{
    this->id = id;
}

void HandlerFactory::setHost(QString host)
{
    this->host = host;
}

void HandlerFactory::setConfig(QString config)
{
    this->config = config;
}
