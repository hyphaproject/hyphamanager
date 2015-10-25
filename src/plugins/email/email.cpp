
#include <QtCore/QProcess>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <Poco/ClassLibrary.h>
#include "email.h"

using namespace hypha::plugin;
using namespace hypha::plugin::email;

void EMail::loadConfig(std::string json) {
  widget();
  emailWidget->setHost(QString::fromStdString(host));
  emailWidget->loadConfig(QString::fromStdString(json));
}

std::string EMail::getConfig() {
  return emailWidget->getConfig().toStdString();
}

HyphaPluginConfig *EMail::getInstance(std::string id) {
  EMail *instance = new EMail();
  instance->setId(id);
  return instance;
}

QWidget *EMail::widget() {
  if (!emailWidget)
    emailWidget = new EMailWidget();
  return emailWidget;
}

POCO_BEGIN_MANIFEST(HyphaPlugin)
POCO_EXPORT_CLASS(EMail)
POCO_END_MANIFEST
