#include "dooropener.h"
#include <Poco/ClassLibrary.h>
#include <hypha/core/database/database.h>
#include <hypha/core/database/userdatabase.h>
#include <QtCore/QDateTime>
#include <QtCore/QDebug>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QMutex>
#include <QtCore/QThread>
#include <QtCore/QTimer>

using namespace hypha::handler;
using namespace hypha::handler::dooropener;
using namespace hypha::plugin;

DoorOpener::DoorOpener() { doorWidget = new DoorOpenerWidget(); }

DoorOpener::~DoorOpener() {}

void DoorOpener::parse(std::string message) {}

void DoorOpener::loadConfig(std::string config) {
  doorWidget->setId(QString::fromStdString(id));
  doorWidget->setDatabase(database);
  doorWidget->setUserDatabase(userDatabase);
  doorWidget->loadConfig(QString::fromStdString(config));
}

std::string DoorOpener::getConfig() {
  return doorWidget->getConfig().toStdString();
}

HyphaHandlerConfig *DoorOpener::getInstance(std::string id) {
  DoorOpener *dooropener = new DoorOpener();
  dooropener->setId(id);
  return dooropener;
}

QWidget *DoorOpener::widget() { return doorWidget; }

POCO_BEGIN_MANIFEST(HyphaHandler)
POCO_EXPORT_CLASS(DoorOpener)
POCO_END_MANIFEST
