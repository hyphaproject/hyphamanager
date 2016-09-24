
#include "video.h"
#include <Poco/ClassLibrary.h>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QProcess>

using namespace hypha::plugin;
using namespace hypha::plugin::video;

void Video::loadConfig(std::string json) {
  widget();
  videoWidget->setHost(QString::fromStdString(host));
  videoWidget->loadConfig(QString::fromStdString(json));
}

std::string Video::getConfig() {
  return videoWidget->getConfig().toStdString();
}

HyphaPluginConfig *Video::getInstance(std::string id) {
  Video *instance = new Video();
  instance->setId(id);
  return instance;
}

QWidget *Video::widget() {
  if (!videoWidget) videoWidget = new VideoWidget();
  return videoWidget;
}

POCO_BEGIN_MANIFEST(HyphaPlugin)
POCO_EXPORT_CLASS(Video)
POCO_END_MANIFEST
