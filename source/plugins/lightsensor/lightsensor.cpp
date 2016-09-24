// Copyright (c) 2015-2016 Hypha
#include "lightsensor.h"
#include <Poco/ClassLibrary.h>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QProcess>

using namespace hypha::plugin;
using namespace hypha::plugin::lightsensor;

void LightSensor::loadConfig(std::string json) {
  widget();
  lightSensorWidget->setHost(QString::fromStdString(host));
  lightSensorWidget->loadConfig(QString::fromStdString(json));
}

std::string LightSensor::getConfig() {
  return lightSensorWidget->getConfig().toStdString();
}

HyphaPluginConfig *LightSensor::getInstance(std::string id) {
  LightSensor *instance = new LightSensor();
  instance->setId(id);
  return instance;
}

QWidget *LightSensor::widget() {
  if (!lightSensorWidget) lightSensorWidget = new LightSensorWidget();
  return lightSensorWidget;
}

POCO_BEGIN_MANIFEST(HyphaPlugin)
POCO_EXPORT_CLASS(LightSensor)
POCO_END_MANIFEST
