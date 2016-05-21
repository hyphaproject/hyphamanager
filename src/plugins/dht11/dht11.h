#ifndef EMAIL_H
#define EMAIL_H
#include "dht11widget.h"
#include "plugin/hyphapluginconfig.h"
namespace hypha {
namespace plugin {
namespace dht11 {
class Dht11 : public HyphaPluginConfig {
 public:
  const std::string name() { return "dht11"; }
  const std::string getTitle() { return "Dht11"; }
  const std::string getVersion() { return "0.1"; }
  const std::string getDescription() {
    return "Read Temperature and Humidity.";
  }
  void loadConfig(std::string json);
  std::string getConfig();
  HyphaPluginConfig *getInstance(std::string id);

  QWidget *widget();

 private:
  Dht11Widget *dht11Widget = nullptr;
  std::string language;
};
}
}
}
#endif  // EMAIL_H
