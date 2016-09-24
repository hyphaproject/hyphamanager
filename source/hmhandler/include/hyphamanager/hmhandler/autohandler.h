// Copyright (c) 2015-2016 Hypha
#ifndef AUTOHANDLER_H
#define AUTOHANDLER_H

#include <hyphamanager/hmhandler/autohandlerwidget.h>
#include <hyphamanager/hmhandler/hmhandler_api.h>
#include <hyphamanager/hmhandler/hyphahandlerconfig.h>

namespace hypha {
namespace handler {
class HMHANDLER_API AutoHandler : public HyphaHandlerConfig {
 public:
  const std::string name();
  const std::string getTitle();
  const std::string getVersion();
  const std::string getDescription();
  const std::string getConfigDescription();
  void loadConfig(std::string json);
  std::string getConfig();
  HyphaHandlerConfig *getInstance(std::string id);
  static HyphaHandlerConfig *getInstance(HyphaHandler *handler);

  QWidget *widget();

 private:
  HyphaHandler *handler = nullptr;
  AutoHandlerWidget *handlerWidget = nullptr;
};
}
}

#endif  // AUTOHANDLER_H
