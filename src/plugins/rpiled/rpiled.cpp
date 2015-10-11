
#include <QtCore/QProcess>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include "plugin/hyphaplugin.h"
#include "rpiled.h"

using namespace hypha::plugin;
using namespace hypha::plugin::rpiled;

void RpiLed::loadConfig(QString json)
{
    widget();
    rpiledWidget->setHost(host);
    rpiledWidget->loadConfig(json);
}

QString RpiLed::getConfig()
{
    return rpiledWidget->getConfig();
}

HyphaPlugin *RpiLed::getInstance(QString id, QObject *parent)
{
    RpiLed *instance = new RpiLed();
    instance->setParent(parent);
    instance->setId(id);
    return instance;
}

QWidget *RpiLed::widget()
{
    if(!rpiledWidget)
        rpiledWidget = new RpiLedWidget();
    return rpiledWidget;
}
