#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H
#include "plugin/hyphapluginconfig.h"
#include "lightsensorwidget.h"
namespace hypha {
namespace plugin {
namespace lightsensor {
class LightSensor : public HyphaPluginConfig {
 public:
  std::string name() {
    return "lightsensor";
  }
  std::string getTitle() {
    return "LightSensor";
  }
  std::string getVersion() {
    return "0.1";
  }
  std::string getDescription() {
    return "Read Light Sensor.";
  }
  void loadConfig(std::string json);
  std::string getConfig();
  HyphaPluginConfig *getInstance(std::string id);

  QWidget *widget();

 private:
  LightSensorWidget *lightSensorWidget = nullptr;
  std::string language;
};
}
}
}
#endif // LIGHTSENSOR_H
