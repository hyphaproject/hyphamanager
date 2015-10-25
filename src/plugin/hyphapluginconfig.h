#ifndef HYPHAPLUGINCONFIG_H
#define HYPHAPLUGINCONFIG_H

#include <QtCore/QObject>
#include <QtCore/QtPlugin>
#include <QtCore/QThread>
#include <hypha/database/database.h>
#include <hypha/plugin/hyphaplugin.h>
#include <hypha/database/database.h>

namespace hypha {
namespace plugin {

class HyphaPluginConfig: public HyphaPlugin {
 public:
  void setup() {}
  void doWork() {}
  void receiveMessage(std::string message) {}
  std::string communicate(std::string message) {
    return "";
  }
  virtual HyphaPluginConfig *getInstance(std::string id) = 0;
  void setDatabase(hypha::database::Database *database) {
    this->database = database;
  }
  virtual QWidget *widget() = 0;
 protected:
  hypha::database::Database *database;
};
}
}

#endif // HYPHAPLUGINCONFIG_H
