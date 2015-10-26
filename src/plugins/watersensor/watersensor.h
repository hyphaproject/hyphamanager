#ifndef WATERSENSOR_H
#define WATERSENSOR_H
#include "plugin/hyphapluginconfig.h"
#include "watersensorwidget.h"
namespace hypha {
namespace plugin {
namespace watersensor {
class WaterSensor : public HyphaPluginConfig {
  public:
    std::string name() {
        return "watersensor";
    }
    std::string getTitle() {
        return "WaterSensor";
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
    WaterSensorWidget *waterSensorWidget = nullptr;
    std::string language;
};
}
}
}
#endif // WATERSENSOR_H
