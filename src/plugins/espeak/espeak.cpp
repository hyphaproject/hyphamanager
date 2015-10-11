
#include <QtCore/QProcess>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include "plugin/hyphaplugin.h"
#include "espeak.h"
#include "espeakwidget.h"

using namespace hypha::plugin;
using namespace hypha::plugin::espeak;

void ESpeak::loadConfig(QString json)
{

}

QString ESpeak::getConfig()
{
    return "{}";
}

HyphaPlugin *ESpeak::getInstance(QString id, QObject *parent)
{
    ESpeak *instance = new ESpeak();
    instance->setParent(parent);
    instance->setId(id);
    return instance;
}

QWidget *ESpeak::widget()
{
    return new ESpeakWidget();
}
