#ifndef WIFI_H
#define WIFI_H
#include "plugin/hyphapluginconfig.h"
namespace hypha {
namespace plugin {
namespace wifi {
class Wifi : public HyphaPluginConfig {
  public:
    std::string name() {
        return "wifi";
    }
    std::string getTitle() {
        return "Wifi";
    }
    std::string getVersion() {
        return "0.1";
    }
    std::string getDescription() {
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
#endif // WIFI_H
