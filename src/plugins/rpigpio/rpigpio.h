#ifndef RPIGPIO_H
#define RPIGPIO_H
#include "plugin/hyphapluginconfig.h"
namespace hypha {
namespace plugin {
namespace rpigpio {
class RpiGpio : public HyphaPluginConfig {
 public:
  std::string getName() {
    return "rpigpio";
  }
  std::string getTitle() {
    return "RPI GPIO";
  }
  std::string getVersion() {
    return "0.1";
  }
  std::string getDescription() {
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
#endif // RPIGPIO_H
