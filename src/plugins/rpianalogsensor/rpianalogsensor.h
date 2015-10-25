#ifndef RPIANALOGSENSOR_H
#define RPIANALOGSENSOR_H
#include "plugin/hyphapluginconfig.h"
#include "rpianalogsensorwidget.h"
namespace hypha {
namespace plugin {
namespace rpianalogsensor {
class RpiAnalogSensor : public HyphaPluginConfig {
 public:
  std::string name() {
    return "rpianalogsensor";
  }
  std::string getTitle() {
    return "RpiAnalogSensor";
  }
  std::string getVersion() {
    return "0.1";
  }
  std::string getDescription() {
    return "Read Water Sensor.";
  }
  void loadConfig(std::string json);
  std::string getConfig();
  HyphaPluginConfig *getInstance(std::string id);

  QWidget *widget();

 private:
  RpiAnalogSensorWidget *rpiAnalogSensorWidget = nullptr;
  QString language;
};
}
}
}
#endif // RPIANALOGSENSOR_H
