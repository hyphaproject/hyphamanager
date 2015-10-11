
#include <QtCore/QProcess>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include "plugin/hyphaplugin.h"
#include "flame.h"

using namespace hypha::plugin;
using namespace hypha::plugin::flame;

void Flame::loadConfig(QString json)
{
    widget();
    flameWidget->setHost(host);
    flameWidget->loadConfig(json);
}

QString Flame::getConfig()
{
    return flameWidget->getConfig();
}

HyphaPlugin *Flame::getInstance(QString id, QObject *parent)
{
    Flame *instance = new Flame();
    instance->setParent(parent);
    instance->setId(id);
    return instance;
}

QWidget *Flame::widget()
{
    if(!flameWidget)
        flameWidget = new FlameWidget();
    return flameWidget;
}
