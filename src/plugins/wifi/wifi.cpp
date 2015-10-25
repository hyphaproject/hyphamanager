
#include <QtCore/QProcess>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include <Poco/ClassLibrary.h>
#include "wifi.h"
#include "wifiwidget.h"

using namespace hypha::plugin;
using namespace hypha::plugin::wifi;

void Wifi::loadConfig(std::string json) {

}

std::string Wifi::getConfig() {
  return "{}";
}

HyphaPluginConfig *Wifi::getInstance(std::string id) {
  Wifi *instance = new Wifi();
  instance->setId(id);
  return instance;
}

QWidget *Wifi::widget() {
  return new WifiWidget();
}

POCO_BEGIN_MANIFEST(HyphaPlugin)
POCO_EXPORT_CLASS(Wifi)
POCO_END_MANIFEST
