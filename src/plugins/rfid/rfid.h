#ifndef RFID_H
#define RFID_H
#include <QtSerialPort/QSerialPort>
#include "plugin/hyphapluginconfig.h"
namespace hypha {
namespace plugin {
namespace rfid {
class RFID : public HyphaPluginConfig {
 public:
  std::string name() {
    return "rfid";
  }
  std::string getTitle() {
    return "RFID";
  }
  std::string getVersion() {
    return "0.1";
  }
  std::string getDescription() {
    return "Plugin to detect rfid cards.";
  }
  void loadConfig(std::string json);
  std::string getConfig();
  HyphaPluginConfig *getInstance(std::string id);

  QWidget *widget();

 private:
};
}
}
}
#endif // RFID_H
