#include <QtCore/QMutex>
#include <QtCore/QDateTime>
#include <QtCore/QThread>
#include <QtCore/QDebug>
#include <QtCore/QTimer>
#include <Poco/ClassLibrary.h>
#include <hypha/database/database.h>
#include <hypha/database/userdatabase.h>
#include "alarm.h"


using namespace hypha::handler;
using namespace hypha::handler::alarm;
using namespace hypha::plugin;

Alarm::Alarm() {
  alarmWidget = new AlarmWidget();
}

Alarm::~Alarm() {

}

void Alarm::parse(std::string message) {

}

void Alarm::loadConfig(std::string config) {
  alarmWidget->loadConfig(QString::fromStdString(config));
}

std::string Alarm::getConfig() {
  return alarmWidget->getConfig().toStdString();
}

HyphaHandlerConfig *Alarm::getInstance(std::string id) {
  Alarm *instance = new Alarm();
  instance->setId(id);
  return instance;
}

QWidget *Alarm::widget() {
  return alarmWidget;
}

POCO_BEGIN_MANIFEST(HyphaHandler)
POCO_EXPORT_CLASS(Alarm)
POCO_END_MANIFEST
