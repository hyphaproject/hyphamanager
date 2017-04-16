// Copyright (c) 2015-2017 Hypha
#ifndef HYPHAPLUGINCONFIG_H
#define HYPHAPLUGINCONFIG_H

#include <hyphamanager/hmplugin/hmplugin_api.h>

#include <hypha/core/database/database.h>
#include <hypha/core/database/database.h>
#include <hypha/plugin/hyphabaseplugin.h>

#include <QtCore/QObject>
#include <QtCore/QThread>
#include <QtCore/QtPlugin>

namespace hypha {
namespace plugin {

class HMPLUGIN_API HyphaPluginConfig : public HyphaBasePlugin {
 public:
  void setup() {}
  void doWork() {}
  void receiveMessage(std::string message) { (void)message; }
  std::string communicate(std::string message) {
    (void)message;
    return "";
  }
  const std::string getConfigDescription() { return "{}"; }
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

#endif  // HYPHAPLUGINCONFIG_H
