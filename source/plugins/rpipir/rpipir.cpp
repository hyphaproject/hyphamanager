
#include "rpipir.h"
#include <Poco/ClassLibrary.h>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QProcess>
#include "rpipirwidget.h"

using namespace hypha::plugin;
using namespace hypha::plugin::rpipir;

void RpiPir::loadConfig(std::string json) {
  widget();
  rpipirWidget->loadConfig(QString::fromStdString(json));
}

std::string RpiPir::getConfig() {
  return rpipirWidget->getConfig().toStdString();
}

HyphaPluginConfig *RpiPir::getInstance(std::string id) {
  RpiPir *instance = new RpiPir();
  instance->setId(id);
  return instance;
}

QWidget *RpiPir::widget() {
  if (!rpipirWidget) rpipirWidget = new RpiPirWidget();
  return rpipirWidget;
}

POCO_BEGIN_MANIFEST(HyphaPlugin)
POCO_EXPORT_CLASS(RpiPir)
POCO_END_MANIFEST
