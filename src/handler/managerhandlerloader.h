#ifndef MANAGERHANDLERLOADER_H
#define MANAGERHANDLERLOADER_H

#include <hypha/handler/handlerloader.h>
#include "handler/unknownhandler.h"

namespace hypha {
namespace handler {
class ManagerHandlerLoader: public HandlerLoader
{
public:
    ManagerHandlerLoader(hypha::settings::HandlerSettings *settings);
    void loadAllInstances();
protected:
    UnknownHandler * unknownHandler;
};
}
}
#endif // MANAGERHANDLERLOADER_H
