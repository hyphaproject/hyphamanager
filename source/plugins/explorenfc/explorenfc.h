// Copyright (c) 2015-2016 Hypha
#ifndef EXPLORENFC_H
#define EXPLORENFC_H

#include "hyphamanager/hmplugin/hyphapluginconfig.h"

namespace hypha {
namespace plugin {
namespace explorenfc {
class ExploreNFC : public HyphaPluginConfig {
 public:
  const std::string name() { return "explorenfc"; }
  const std::string getTitle() { return "ExploreNFC"; }
  const std::string getVersion() { return "0.1"; }
  const std::string getDescription() { return "Plugin to detect rfid cards."; }
  void loadConfig(std::string json);
  std::string getConfig();
  HyphaPluginConfig *getInstance(std::string id);

  QWidget *widget();

 private:
};
}
}
}
#endif  // EXPLORENFC_H
