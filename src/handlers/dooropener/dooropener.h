#ifndef DOOROPENER_H
#define DOOROPENER_H

#include <QtCore/QObject>
#include "../../handler/hyphahandlerconfig.h"
#include "dooropenerwidget.h"

namespace hypha {
namespace handler {
namespace dooropener {
class DoorOpener : public HyphaHandlerConfig {
 public:
  explicit DoorOpener();
  ~DoorOpener();
  static DoorOpener *instance();
  std::string name() {
    return "dooropener";
  }
  std::string getTitle() {
    return "DoorOpener";
  }
  std::string getVersion() {
    return "0.1";
  }
  std::string getDescription() {
    return "Handler to open doors.";
  }
  void parse(std::string message);
  void loadConfig(std::string config);
  std::string getConfig();
  HyphaHandlerConfig *getInstance(std::string id);

  QWidget *widget();

 protected:
  DoorOpenerWidget *doorWidget = nullptr;

};
}
}
}

#endif // DOOROPENER_H
