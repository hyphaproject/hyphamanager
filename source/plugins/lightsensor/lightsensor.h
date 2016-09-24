#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H
#include "hyphamanager/hmplugin/hyphapluginconfig.h"
#include "lightsensorwidget.h"
namespace hypha {
namespace plugin {
namespace lightsensor {
class LightSensor : public HyphaPluginConfig {
 public:
  const std::string name() { return "lightsensor"; }
  const std::string getTitle() { return "LightSensor"; }
  const std::string getVersion() { return "0.1"; }
  const std::string getDescription() { return "Read Light Sensor."; }
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
#endif  // LIGHTSENSOR_H
