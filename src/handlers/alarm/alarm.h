#ifndef ALARM_H
#define ALARM_H

#include "../../handler/hyphahandlerconfig.h"
#include "alarmwidget.h"

namespace hypha {
namespace handler {
namespace alarm {
class Alarm : public HyphaHandlerConfig {
 public:
  explicit Alarm();
  ~Alarm();
  static Alarm *instance();
  const std::string name() { return "alarm"; }
  const std::string getTitle() { return "Alarm"; }
  const std::string getVersion() { return "0.1"; }
  const std::string getDescription() { return "Handler for Alarm Control."; }
  void parse(std::string message);
  void loadConfig(std::string config);
  std::string getConfig();
  HyphaHandlerConfig *getInstance(std::string id);

  QWidget *widget();

 protected:
  AlarmWidget *alarmWidget = nullptr;
};
}
}
}

#endif  // ALARM_H
