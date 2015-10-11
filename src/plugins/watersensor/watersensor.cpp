
#include <QtCore/QProcess>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include "plugin/hyphaplugin.h"
#include "watersensor.h"

using namespace hypha::plugin;
using namespace hypha::plugin::watersensor;

void WaterSensor::loadConfig(QString json)
{
    widget();
    waterSensorWidget->setHost(host);
    waterSensorWidget->loadConfig(json);
}

QString WaterSensor::getConfig()
{
    return waterSensorWidget->getConfig();
}

HyphaPlugin *WaterSensor::getInstance(QString id, QObject *parent)
{
    WaterSensor *instance = new WaterSensor();
    instance->setParent(parent);
    instance->setId(id);
    return instance;
}

QWidget *WaterSensor::widget()
{
    if(!waterSensorWidget)
        waterSensorWidget = new WaterSensorWidget();
    return waterSensorWidget;
}
