#ifndef EXPLORENFC_H
#define EXPLORENFC_H

#include "plugin/hyphapluginconfig.h"

namespace hypha {
namespace plugin {
namespace explorenfc {
class ExploreNFC : public HyphaPluginConfig {
 public:
  std::string name() {
    return "explorenfc";
  }
  std::string getTitle() {
    return "ExploreNFC";
  }
  std::string getVersion() {
    return "0.1";
  }
  std::string getDescription() {
    return "Plugin to detect rfid cards.";
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
#endif // EXPLORENFC_H
