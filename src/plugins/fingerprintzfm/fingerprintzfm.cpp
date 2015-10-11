#include <QtCore/QProcess>
#include <QtCore/QThread>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include <QtCore/QVariant>
#include <QtSerialPort/QSerialPortInfo>


#include "plugin/hyphaplugin.h"
#include "fingerprintzfm.h"
#include "../../database/database.h"
#include "fingerprintzfmwidget.h"

using namespace hypha::plugin::fingerprintzfm;

void FingerPrintZFM::loadConfig(QString json)
{
    QJsonDocument document = QJsonDocument::fromJson(json.toUtf8());
    QJsonObject object = document.object();
    if(object.contains("usbport")){
    }
}

QString FingerPrintZFM::getConfig()
{
    return "{}";
}

hypha::plugin::HyphaPlugin *FingerPrintZFM::getInstance(QString id, QObject *parent)
{
    FingerPrintZFM *instance = new FingerPrintZFM();
    instance->setParent(parent);
    instance->setId(id);
    return instance;
}

QWidget *FingerPrintZFM::widget()
{
    return new FingerPrintZFMWidget();
}
