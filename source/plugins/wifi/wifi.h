// Copyright (c) 2015-2016 Hypha
#ifndef WIFI_H
#define WIFI_H
#include "hyphamanager/hmplugin/hyphapluginconfig.h"
namespace hypha {
namespace plugin {
namespace wifi {
class Wifi : public HyphaPluginConfig {
 public:
  const std::string name() { return "wifi"; }
  const std::string getTitle() { return "Wifi"; }
  const std::string getVersion() { return "0.1"; }
  const std::string getDescription() {
    return "Plugin to scan for mac adresses in the network.";
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
#endif  // WIFI_H
