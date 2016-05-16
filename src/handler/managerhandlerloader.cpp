#include <hypha/handler/handlerfactory.h>
#include <hypha/core/settings/hyphasettings.h>
#include "handler/unknownhandler.h"

#include "managerhandlerloader.h"

using namespace hypha::handler;

ManagerHandlerLoader::ManagerHandlerLoader(hypha::settings::HandlerSettings *settings)
    :HandlerLoader(settings)
{
    unknownHandler = new UnknownHandler();
}

void ManagerHandlerLoader::loadAllInstances()
{
    for (std::string id : settings->getAllHandlerIds()) {
        if (getHandlerInstance(id) == 0) {
            HyphaHandler *handler = factory->loadHandler(id);
            if (handler)
                handlerInstances[id] = handler;
            else {
                handler = unknownHandler->getInstance(id);
                std::string host = settings->getHost(id);
                std::string config = settings->getConfig(id);
                handler->setHost(host);
                handler->loadConfig(config);
                handlerInstances[id] = handler;
            }
        }
    }
}
