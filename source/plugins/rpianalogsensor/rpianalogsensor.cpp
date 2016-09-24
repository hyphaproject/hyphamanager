// Copyright (c) 2015-2016 Hypha
#include "rpianalogsensor.h"
#include <Poco/ClassLibrary.h>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QProcess>

using namespace hypha::plugin;
using namespace hypha::plugin::rpianalogsensor;

void RpiAnalogSensor::loadConfig(std::string json) {
  widget();
  rpiAnalogSensorWidget->setHost(QString::fromStdString(host));
  rpiAnalogSensorWidget->loadConfig(QString::fromStdString(json));
}

std::string RpiAnalogSensor::getConfig() {
  return rpiAnalogSensorWidget->getConfig().toStdString();
}

HyphaPluginConfig *RpiAnalogSensor::getInstance(std::string id) {
  RpiAnalogSensor *instance = new RpiAnalogSensor();
  instance->setId(id);
  return instance;
}

QWidget *RpiAnalogSensor::widget() {
  if (!rpiAnalogSensorWidget)
    rpiAnalogSensorWidget = new RpiAnalogSensorWidget();
  return rpiAnalogSensorWidget;
}

POCO_BEGIN_MANIFEST(HyphaPlugin)
POCO_EXPORT_CLASS(RpiAnalogSensor)
POCO_END_MANIFEST
