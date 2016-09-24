// Copyright (c) 2015-2016 Hypha
#ifndef RPIGPIO_H
#define RPIGPIO_H
#include "hyphamanager/hmplugin/hyphapluginconfig.h"
namespace hypha {
namespace plugin {
namespace rpigpio {
class RpiGpio : public HyphaPluginConfig {
 public:
  const std::string name() { return "rpigpio"; }
  const std::string getTitle() { return "RPI GPIO"; }
  const std::string getVersion() { return "0.1"; }
  const std::string getDescription() {
    return "Plugin to access gpio of the raspberry pi";
  }
  void loadConfig(std::string json);
  std::string getConfig();
  HyphaPluginConfig *getInstance(std::string id);

  QWidget *widget();

 private:
};
}
}
}
#endif  // RPIGPIO_H
