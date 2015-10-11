
#include <QtCore/QProcess>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include "plugin/hyphaplugin.h"
#include "lightsensor.h"

using namespace hypha::plugin;
using namespace hypha::plugin::lightsensor;

void LightSensor::loadConfig(QString json)
{
    widget();
    lightSensorWidget->setHost(host);
    lightSensorWidget->loadConfig(json);
}

QString LightSensor::getConfig()
{
    return lightSensorWidget->getConfig();
}

HyphaPlugin *LightSensor::getInstance(QString id, QObject *parent)
{
    LightSensor *instance = new LightSensor();
    instance->setParent(parent);
    instance->setId(id);
    return instance;
}

QWidget *LightSensor::widget()
{
    if(!lightSensorWidget)
        lightSensorWidget = new LightSensorWidget();
    return lightSensorWidget;
}
