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
  std::string name() {
    return "alarm";
  }
  std::string getTitle() {
    return "Alarm";
  }
  std::string getVersion() {
    return "0.1";
  }
  std::string getDescription() {
    return "Handler for Alarm Control.";
  }
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

#endif // ALARM_H
