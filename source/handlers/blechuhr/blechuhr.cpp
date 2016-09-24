#include "blechuhr.h"
#include <Poco/ClassLibrary.h>
#include <QtCore/QDateTime>
#include <QtCore/QDebug>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QMutex>
#include <QtCore/QThread>

using namespace hypha::handler;
using namespace hypha::handler::blechuhr;
using namespace hypha::plugin;

BlechUhr::BlechUhr() { buwidget = new BlechUhrWidget(); }

BlechUhr::~BlechUhr() {}

void BlechUhr::parse(std::string message) {}

void BlechUhr::loadConfig(std::string config) {}

std::string BlechUhr::getConfig() { return "{\"name\":\"blechuhr\"}"; }

HyphaHandlerConfig *BlechUhr::getInstance(std::string id) {
  BlechUhr *blechuhr = new BlechUhr();
  blechuhr->setId(id);
  return blechuhr;
}

QWidget *BlechUhr::widget() { return buwidget; }

POCO_BEGIN_MANIFEST(HyphaHandler)
POCO_EXPORT_CLASS(BlechUhr)
POCO_END_MANIFEST
