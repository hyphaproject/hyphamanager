// Copyright (c) 2015-2016 Hypha
#ifndef RPIANALOGSENSOR_H
#define RPIANALOGSENSOR_H
#include "hyphamanager/hmplugin/hyphapluginconfig.h"
#include "rpianalogsensorwidget.h"
namespace hypha {
namespace plugin {
namespace rpianalogsensor {
class RpiAnalogSensor : public HyphaPluginConfig {
 public:
  const std::string name() { return "rpianalogsensor"; }
  const std::string getTitle() { return "RpiAnalogSensor"; }
  const std::string getVersion() { return "0.1"; }
  const std::string getDescription() { return "Read Water Sensor."; }
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
#endif  // RPIANALOGSENSOR_H
