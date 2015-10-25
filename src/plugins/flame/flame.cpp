
#include <QtCore/QProcess>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <Poco/ClassLibrary.h>
#include "flame.h"

using namespace hypha::plugin;
using namespace hypha::plugin::flame;

void Flame::loadConfig(std::string json)
{
    widget();
    flameWidget->setHost(QString::fromStdString(host));
    flameWidget->loadConfig(QString::fromStdString(json));
}

std::string Flame::getConfig()
{
    return flameWidget->getConfig().toStdString();
}

HyphaPluginConfig *Flame::getInstance(std::string id)
{
    Flame *instance = new Flame();
    instance->setId(id);
    return instance;
}

QWidget *Flame::widget()
{
    if(!flameWidget)
        flameWidget = new FlameWidget();
    return flameWidget;
}

POCO_BEGIN_MANIFEST(HyphaPlugin)
POCO_EXPORT_CLASS(Flame)
POCO_END_MANIFEST
