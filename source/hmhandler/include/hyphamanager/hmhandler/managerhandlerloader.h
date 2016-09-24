// Copyright (c) 2015-2016 Hypha
#ifndef MANAGERHANDLERLOADER_H
#define MANAGERHANDLERLOADER_H

#include <hypha/handler/handlerloader.h>
#include <hyphamanager/hmhandler/hmhandler_api.h>
#include <hyphamanager/hmhandler/unknownhandler.h>

namespace hypha {
namespace handler {
class HMHANDLER_API ManagerHandlerLoader : public HandlerLoader {
 public:
  ManagerHandlerLoader(hypha::settings::HandlerSettings *settings);
  void loadAllInstances();

 protected:
  UnknownHandler *unknownHandler;
};
}
}
#endif  // MANAGERHANDLERLOADER_H
