// Copyright (c) 2015-2016 Hypha
#ifndef RPIPIR_H
#define RPIPIR_H
#include "hyphamanager/hmplugin/hyphapluginconfig.h"
#include "rpipirwidget.h"
namespace hypha {
namespace plugin {
namespace rpipir {
class RpiPir : public HyphaPluginConfig {
 public:
  const std::string name() { return "rpipir"; }
  const std::string getTitle() { return "RPI PIR"; }
  const std::string getVersion() { return "0.1"; }
  const std::string getDescription() {
    return "Plugin to detect motion with a motion sensor.";
  }
  void loadConfig(std::string json);
  std::string getConfig();
  HyphaPluginConfig *getInstance(std::string id);
  QWidget *widget();

 private:
  RpiPirWidget *rpipirWidget = nullptr;
};
}
}
}
#endif  // RPIPIR_H
