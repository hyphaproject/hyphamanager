#include "autohandler.h"
#include <hypha/plugin/pluginfactory.h>

using namespace hypha::handler;

const std::string AutoHandler::name()
{
    return handler->name();
}

const std::string AutoHandler::getTitle()
{
    return handler->getTitle();
}

const std::string AutoHandler::getVersion()
{
    return handler->getVersion();
}

const std::string AutoHandler::getDescription()
{
    return handler->getDescription();
}

const std::string AutoHandler::getConfigDescription()
{
    return handler->getConfigDescription();
}

void AutoHandler::loadConfig(std::string json)
{
    widget();
    handlerWidget->loadConfig(json);
}

std::string AutoHandler::getConfig()
{
    return handlerWidget->getConfig();
}

HyphaHandlerConfig *AutoHandler::getInstance(std::string id)
{
    return nullptr;
}

HyphaHandlerConfig *AutoHandler::getInstance(HyphaHandler *handler)
{
    AutoHandler *instance = new AutoHandler();
    instance->handler = handler;
    instance->setId(handler->getId());
    return instance;
}

QWidget *AutoHandler::widget()
{
    if (!handlerWidget)
        handlerWidget = new AutoHandlerWidget(handler);
    return handlerWidget;
}
