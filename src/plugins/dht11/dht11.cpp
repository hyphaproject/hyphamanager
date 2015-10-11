
#include <QtCore/QProcess>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include "plugin/hyphaplugin.h"
#include "dht11.h"

using namespace hypha::plugin;
using namespace hypha::plugin::dht11;

void Dht11::loadConfig(QString json)
{
    widget();
    dht11Widget->setHost(host);
    dht11Widget->loadConfig(json);
}

QString Dht11::getConfig()
{
    return dht11Widget->getConfig();
}

HyphaPlugin *Dht11::getInstance(QString id, QObject *parent)
{
    Dht11 *instance = new Dht11();
    instance->setParent(parent);
    instance->setId(id);
    return instance;
}

QWidget *Dht11::widget()
{
    if(!dht11Widget)
        dht11Widget = new Dht11Widget();
    return dht11Widget;
}
