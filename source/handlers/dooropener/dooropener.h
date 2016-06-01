#ifndef DOOROPENER_H
#define DOOROPENER_H

#include <QtCore/QObject>
#include "hyphamanager/hmhandler/hyphahandlerconfig.h"
#include "dooropenerwidget.h"

namespace hypha {
namespace handler {
namespace dooropener {
class DoorOpener : public HyphaHandlerConfig {
 public:
  explicit DoorOpener();
  ~DoorOpener();
  static DoorOpener *instance();
  const std::string name() { return "dooropener"; }
  const std::string getTitle() { return "DoorOpener"; }
  const std::string getVersion() { return "0.1"; }
  const std::string getDescription() { return "Handler to open doors."; }
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

#endif  // DOOROPENER_H
