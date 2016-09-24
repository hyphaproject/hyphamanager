// Copyright (c) 2015-2016 Hypha
#include "explorenfc.h"
#include <Poco/ClassLibrary.h>
#include <QtCore/QDebug>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QProcess>
#include <QtCore/QThread>
#include "explorenfcwidget.h"

using namespace hypha::plugin::explorenfc;
using namespace hypha::plugin;

void ExploreNFC::loadConfig(std::string json) {}

std::string ExploreNFC::getConfig() { return "{}"; }

HyphaPluginConfig *ExploreNFC::getInstance(std::string id) {
  ExploreNFC *instance = new ExploreNFC();
  instance->setId(id);
  return instance;
}

QWidget *ExploreNFC::widget() { return new ExploreNFCWidget(); }

POCO_BEGIN_MANIFEST(HyphaPlugin)
POCO_EXPORT_CLASS(ExploreNFC)
POCO_END_MANIFEST
