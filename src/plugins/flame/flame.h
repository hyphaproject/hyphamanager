#ifndef FLAME_H
#define FLAME_H
#include "flamewidget.h"
#include "plugin/hyphapluginconfig.h"
namespace hypha {
namespace plugin {
namespace flame {
class Flame : public HyphaPluginConfig {
 public:
  const std::string name() { return "flame"; }
  const std::string getTitle() { return "Flame"; }
  const std::string getVersion() { return "0.1"; }
  const std::string getDescription() { return "Read Flame Sensor."; }
  void loadConfig(std::string json);
  std::string getConfig();
  HyphaPluginConfig *getInstance(std::string id);

  QWidget *widget();

 private:
  FlameWidget *flameWidget = nullptr;
  std::string language;
};
}
}
}
#endif  // FLAME_H
