// Copyright (c) 2015-2016 Hypha
#include "rpiled.h"
#include <Poco/ClassLibrary.h>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QProcess>

using namespace hypha::plugin;
using namespace hypha::plugin::rpiled;

void RpiLed::loadConfig(std::string json) {
  widget();
  rpiledWidget->setHost(QString::fromStdString(host));
  rpiledWidget->loadConfig(QString::fromStdString(json));
}

std::string RpiLed::getConfig() {
  return rpiledWidget->getConfig().toStdString();
}

HyphaPluginConfig *RpiLed::getInstance(std::string id) {
  RpiLed *instance = new RpiLed();
  instance->setId(id);
  return instance;
}

QWidget *RpiLed::widget() {
  if (!rpiledWidget) rpiledWidget = new RpiLedWidget();
  return rpiledWidget;
}

POCO_BEGIN_MANIFEST(HyphaPlugin)
POCO_EXPORT_CLASS(RpiLed)
POCO_END_MANIFEST
