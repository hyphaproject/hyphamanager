#ifndef RFID_H
#define RFID_H
#include "hyphamanager/hmplugin/hyphapluginconfig.h"
namespace hypha {
namespace plugin {
namespace rfid {
class RFID : public HyphaPluginConfig {
 public:
  const std::string name() { return "rfid"; }
  const std::string getTitle() { return "RFID"; }
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
#endif  // RFID_H
