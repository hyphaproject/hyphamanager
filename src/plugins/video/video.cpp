
#include <QtCore/QProcess>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include "plugin/hyphaplugin.h"
#include "video.h"

using namespace hypha::plugin;
using namespace hypha::plugin::video;

void Video::loadConfig(QString json)
{
    widget();
    videoWidget->setHost(host);
    videoWidget->loadConfig(json);
}

QString Video::getConfig()
{
    return videoWidget->getConfig();
}

HyphaPlugin *Video::getInstance(QString id, QObject *parent)
{
    Video *instance = new Video();
    instance->setParent(parent);
    instance->setId(id);
    return instance;
}

QWidget *Video::widget()
{
    if(!videoWidget)
        videoWidget = new VideoWidget();
    return videoWidget;
}
