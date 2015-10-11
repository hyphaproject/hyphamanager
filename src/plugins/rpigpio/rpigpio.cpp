
#include <QtCore/QProcess>
#include <QtCore/QThread>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include <QtCore/QDebug>
#include "plugin/hyphaplugin.h"
#include "rpigpio.h"
#include "rpigpiowidget.h"

using namespace hypha::plugin::rpigpio;

void RpiGpio::loadConfig(QString json)
{

}

QString RpiGpio::getConfig()
{
    return "{}";
}

hypha::plugin::HyphaPlugin *RpiGpio::getInstance(QString id, QObject *parent)
{
    RpiGpio *instance = new RpiGpio();
    instance->setParent(parent);
    instance->setId(id);
    return instance;
}

QWidget *RpiGpio::widget()
{
    return new RpiGpioWidget();
}
