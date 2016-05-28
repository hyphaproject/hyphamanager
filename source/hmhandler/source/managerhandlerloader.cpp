#include <hypha/handler/handlerfactory.h>
#include <hypha/core/settings/hyphasettings.h>
#include "hyphamanager/hmhandler/autohandler.h"

#include "hyphamanager/hmhandler/managerhandlerloader.h"

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
            if (handler) {
              if (dynamic_cast<const HyphaHandlerConfig *>(handler) == nullptr)
                handler = AutoHandler::getInstance(handler);
            }
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
