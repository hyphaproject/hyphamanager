
#include <QtCore/QProcess>
#include <QtCore/QThread>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include <QtCore/QDebug>
#include <Poco/ClassLibrary.h>
#include "rpigpio.h"
#include "rpigpiowidget.h"

using namespace hypha::plugin;
using namespace hypha::plugin::rpigpio;

void RpiGpio::loadConfig(std::string json) {

}

std::string RpiGpio::getConfig() {
    return "{}";
}

HyphaPluginConfig *RpiGpio::getInstance(std::string id) {
    RpiGpio *instance = new RpiGpio();
    instance->setId(id);
    return instance;
}

QWidget *RpiGpio::widget() {
    return new RpiGpioWidget();
}

POCO_BEGIN_MANIFEST(HyphaPlugin)
POCO_EXPORT_CLASS(RpiGpio)
POCO_END_MANIFEST