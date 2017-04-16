// Copyright (c) 2015-2017 Hypha

#include "rpigpio.h"
#include "rpigpiowidget.h"

#include <Poco/ClassLibrary.h>
#include <QtCore/QDebug>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QProcess>
#include <QtCore/QThread>

using namespace hypha::plugin;
using namespace hypha::plugin::rpigpio;

void RpiGpio::loadConfig(std::string json) {}

std::string RpiGpio::getConfig() { return "{}"; }

HyphaPluginConfig *RpiGpio::getInstance(std::string id) {
  RpiGpio *instance = new RpiGpio();
  instance->setId(id);
  return instance;
}

QWidget *RpiGpio::widget() { return new RpiGpioWidget(); }

POCO_BEGIN_MANIFEST(HyphaBasePlugin)
POCO_EXPORT_CLASS(RpiGpio)
POCO_END_MANIFEST
