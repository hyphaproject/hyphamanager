// Copyright (c) 2015-2016 Hypha
#include <Poco/ClassLibrary.h>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QProcess>
#include <QtCore/QThread>

#include "rfid.h"
#include "rfidwidget.h"

using namespace hypha::plugin;
using namespace hypha::plugin::rfid;

void RFID::loadConfig(std::string json) {}

std::string RFID::getConfig() { return "{}"; }

HyphaPluginConfig *RFID::getInstance(std::string id) {
  RFID *instance = new RFID();
  instance->setId(id);
  return instance;
}

QWidget *RFID::widget() { return new RFIDWidget(); }

POCO_BEGIN_MANIFEST(HyphaBasePlugin)
POCO_EXPORT_CLASS(RFID)
POCO_END_MANIFEST
