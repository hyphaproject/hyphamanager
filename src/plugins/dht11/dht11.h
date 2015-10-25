#ifndef EMAIL_H
#define EMAIL_H
#include "plugin/hyphapluginconfig.h"
#include "dht11widget.h"
namespace hypha {
namespace plugin {
namespace dht11 {
class Dht11 : public HyphaPluginConfig {
 public:
  std::string name() {
    return "dht11";
  }
  std::string getTitle() {
    return "Dht11";
  }
  std::string getVersion() {
    return "0.1";
  }
  std::string getDescription() {
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
#endif // EMAIL_H
