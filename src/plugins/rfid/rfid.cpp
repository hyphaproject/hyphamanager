
#include <QtCore/QProcess>
#include <QtCore/QThread>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>

#include "plugin/hyphaplugin.h"
#include "rfid.h"
#include "rfidwidget.h"

using namespace hypha::plugin::rfid;

void RFID::loadConfig(QString json)
{
}

QString RFID::getConfig()
{
    return "{}";
}

hypha::plugin::HyphaPlugin *RFID::getInstance(QString id, QObject *parent)
{
    RFID *instance = new RFID();
    instance->setParent(parent);
    instance->setId(id);
    return instance;
}

QWidget *RFID::widget()
{
    return new RFIDWidget();
}
