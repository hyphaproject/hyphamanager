// Copyright (c) 2015-2016 Hypha
#include "videocontrol.h"
#include <Poco/ClassLibrary.h>
#include <hypha/core/database/database.h>
#include <hypha/core/database/userdatabase.h>
#include <QtCore/QDateTime>
#include <QtCore/QDebug>
#include <QtCore/QMutex>
#include <QtCore/QThread>
#include <QtCore/QTimer>

using namespace hypha::handler;
using namespace hypha::handler::videocontrol;
using namespace hypha::plugin;

VideoControl::VideoControl() { vcwidget = new VideoControlWidget(); }

VideoControl::~VideoControl() {}

void VideoControl::parse(std::string message) {}

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

QWidget *VideoControl::widget() { return vcwidget; }

POCO_BEGIN_MANIFEST(HyphaHandler)
POCO_EXPORT_CLASS(VideoControl)
POCO_END_MANIFEST
