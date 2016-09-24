// Copyright (c) 2015-2016 Hypha
#include "serverstatus.h"
#include <Poco/ClassLibrary.h>
#include <hypha/core/database/database.h>
#include <hypha/core/database/userdatabase.h>
#include <QtCore/QDateTime>
#include <QtCore/QDebug>
#include <QtCore/QMutex>
#include <QtCore/QThread>
#include <QtCore/QTimer>

using namespace hypha::handler;
using namespace hypha::handler::serverstatus;
using namespace hypha::plugin;

ServerStatus::ServerStatus() { serverStatusWidget = new ServerStatusWidget(); }

ServerStatus::~ServerStatus() {}

void ServerStatus::parse(std::string message) {}

void ServerStatus::loadConfig(std::string config) {
  serverStatusWidget->loadConfig(QString::fromStdString(config));
}

std::string ServerStatus::getConfig() {
  return serverStatusWidget->getConfig().toStdString();
}

HyphaHandlerConfig *ServerStatus::getInstance(std::string id) {
  ServerStatus *instance = new ServerStatus();
  instance->setId(id);
  return instance;
}

QWidget *ServerStatus::widget() { return serverStatusWidget; }

POCO_BEGIN_MANIFEST(HyphaHandler)
POCO_EXPORT_CLASS(ServerStatus)
POCO_END_MANIFEST
