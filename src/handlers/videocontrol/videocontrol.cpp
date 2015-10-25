#include <QtCore/QMutex>
#include <QtCore/QDateTime>
#include <QtCore/QThread>
#include <QtCore/QDebug>
#include <QtCore/QTimer>
#include <Poco/ClassLibrary.h>
#include <hypha/database/database.h>
#include <hypha/database/userdatabase.h>
#include "videocontrol.h"

using namespace hypha::handler;
using namespace hypha::handler::videocontrol;
using namespace hypha::plugin;

VideoControl::VideoControl() {
  vcwidget = new VideoControlWidget();
}

VideoControl::~VideoControl() {

}

void VideoControl::parse(std::string message) {

}

void VideoControl::loadConfig(std::string config) {
  vcwidget->loadConfig(QString::fromStdString(config));
}

std::string VideoControl::getConfig() {
  return vcwidget->getConfig().toStdString();
}

HyphaHandlerConfig *VideoControl::getInstance(std::string id) {
  VideoControl *instance = new VideoControl();
  instance->setId(id);
  return instance;
}

QWidget *VideoControl::widget() {
  return vcwidget;
}

POCO_BEGIN_MANIFEST(HyphaHandler)
POCO_EXPORT_CLASS(VideoControl)
POCO_END_MANIFEST
