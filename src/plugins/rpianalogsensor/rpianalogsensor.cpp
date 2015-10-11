
#include <QtCore/QProcess>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include "plugin/hyphaplugin.h"
#include "rpianalogsensor.h"

using namespace hypha::plugin;
using namespace hypha::plugin::rpianalogsensor;

void RpiAnalogSensor::loadConfig(QString json)
{
    widget();
    rpiAnalogSensorWidget->setHost(host);
    rpiAnalogSensorWidget->loadConfig(json);
}

QString RpiAnalogSensor::getConfig()
{
    return rpiAnalogSensorWidget->getConfig();
}

HyphaPlugin *RpiAnalogSensor::getInstance(QString id, QObject *parent)
{
    RpiAnalogSensor *instance = new RpiAnalogSensor();
    instance->setParent(parent);
    instance->setId(id);
    return instance;
}

QWidget *RpiAnalogSensor::widget()
{
    if(!rpiAnalogSensorWidget)
        rpiAnalogSensorWidget = new RpiAnalogSensorWidget();
    return rpiAnalogSensorWidget;
}
