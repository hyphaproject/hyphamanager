
#include "watersensor.h"
#include <Poco/ClassLibrary.h>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QProcess>

using namespace hypha::plugin;
using namespace hypha::plugin::watersensor;

void WaterSensor::loadConfig(std::string json) {
  widget();
  waterSensorWidget->setHost(QString::fromStdString(host));
  waterSensorWidget->loadConfig(QString::fromStdString(json));
}

std::string WaterSensor::getConfig() {
  return waterSensorWidget->getConfig().toStdString();
}

HyphaPluginConfig *WaterSensor::getInstance(std::string id) {
  WaterSensor *instance = new WaterSensor();
  instance->setId(id);
  return instance;
}

QWidget *WaterSensor::widget() {
  if (!waterSensorWidget) waterSensorWidget = new WaterSensorWidget();
  return waterSensorWidget;
}

POCO_BEGIN_MANIFEST(HyphaPlugin)
POCO_EXPORT_CLASS(WaterSensor)
POCO_END_MANIFEST
