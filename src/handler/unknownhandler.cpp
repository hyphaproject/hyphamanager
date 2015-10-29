#include "unknownhandler.h"

using namespace hypha::handler;

void hypha::handler::UnknownHandler::loadConfig(std::string json)
{
    widget();
    unknownHandlerWidget->loadConfig(json);
}

std::string UnknownHandler::getConfig()
{
    return unknownHandlerWidget->getConfig();
}

HyphaHandlerConfig *UnknownHandler::getInstance(std::string id)
{
    UnknownHandler *instance = new UnknownHandler();
    instance->setId(id);
    return instance;
}

QWidget *UnknownHandler::widget()
{
    if (!unknownHandlerWidget)
        unknownHandlerWidget = new UnknownHandlerWidget();
    return unknownHandlerWidget;
}
