#include <QtCore/QMutex>
#include <QtCore/QDateTime>
#include <QtCore/QThread>
#include <QtCore/QDebug>
#include <QtCore/QTimer>
#include "../../plugin/hyphaplugin.h"
#include "../../plugin/pluginloader.h"
#include "videocontrol.h"
#include "../../database/database.h"
#include "../../database/userdatabase.h"


using namespace hypha::handler;
using namespace hypha::handler::videocontrol;
using namespace hypha::plugin;

VideoControl::VideoControl()
{
    vcwidget = new VideoControlWidget();
}

VideoControl::~VideoControl()
{

}

void VideoControl::parse(QString message){

}

void VideoControl::loadConfig(QString config)
{
    vcwidget->loadConfig(config);
}

QString VideoControl::getConfig()
{
    return vcwidget->getConfig();
}

HyphaHandler *VideoControl::getInstance(QString id, QObject *parent)
{
    VideoControl *instance = new VideoControl();
    instance->setParent(parent);
    instance->setId(id);
    return instance;
}

QWidget *VideoControl::widget()
{
    return vcwidget;
}
