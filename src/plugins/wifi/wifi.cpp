
#include <QtCore/QProcess>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include "plugin/hyphaplugin.h"
#include "wifi.h"
#include "wifiwidget.h"

using namespace hypha::plugin::wifi;

void Wifi::loadConfig(QString json)
{

}

QString Wifi::getConfig()
{
    return "{}";
}

hypha::plugin::HyphaPlugin *Wifi::getInstance(QString id, QObject *parent)
{
    Wifi *instance = new Wifi();
    instance->setParent(parent);
    instance->setId(id);
    return instance;
}

QWidget *Wifi::widget()
{
    return new WifiWidget();
}
