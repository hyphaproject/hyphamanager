// Copyright (c) 2015-2016 Hypha
#ifndef BLECHUHR_H
#define BLECHUHR_H

#include "blechuhrwidget.h"
#include "hyphamanager/hmhandler/hyphahandlerconfig.h"

namespace hypha {
namespace handler {
namespace blechuhr {
class BlechUhr : public HyphaHandlerConfig {
 public:
  explicit BlechUhr();
  ~BlechUhr();
  static BlechUhr *instance();
  const std::string name() { return "blechuhr"; }
  const std::string getTitle() { return "Blechuhr"; }
  const std::string getVersion() { return "0.1"; }
  const std::string getDescription() { return "Handler like a time recorder."; }
  void parse(std::string message);
  void loadConfig(std::string config);
  std::string getConfig();
  HyphaHandlerConfig *getInstance(std::string id);

  QWidget *widget();

 private:
 protected:
  BlechUhrWidget *buwidget = nullptr;
};
}
}
}

#endif  // BLECHUHR_H
