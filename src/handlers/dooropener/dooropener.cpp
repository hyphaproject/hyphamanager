#include <QtCore/QMutex>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include <QtCore/QDateTime>
#include <QtCore/QThread>
#include <QtCore/QDebug>
#include <QtCore/QTimer>
#include <Poco/ClassLibrary.h>
#include <hypha/database/database.h>
#include <hypha/database/userdatabase.h>
#include "dooropener.h"

using namespace hypha::handler;
using namespace hypha::handler::dooropener;
using namespace hypha::plugin;

DoorOpener::DoorOpener() {
    doorWidget = new DoorOpenerWidget();
}

DoorOpener::~DoorOpener() {

}

void DoorOpener::parse(std::string message) {

}

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

QWidget *DoorOpener::widget() {
    return doorWidget;
}

POCO_BEGIN_MANIFEST(HyphaHandler)
POCO_EXPORT_CLASS(DoorOpener)
POCO_END_MANIFEST
