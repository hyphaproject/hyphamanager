
#include <QtCore/QProcess>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <Poco/ClassLibrary.h>
#include "espeak.h"
#include "espeakwidget.h"

using namespace hypha::plugin;
using namespace hypha::plugin::espeak;

void ESpeak::loadConfig(std::string json)
{

}

std::string ESpeak::getConfig()
{
    return "{}";
}

HyphaPluginConfig *ESpeak::getInstance(std::string id)
{
    ESpeak *instance = new ESpeak();
    instance->setId(id);
    return instance;
}

QWidget *ESpeak::widget()
{
    return new ESpeakWidget();
}

POCO_BEGIN_MANIFEST(HyphaPlugin)
POCO_EXPORT_CLASS(ESpeak)
POCO_END_MANIFEST
