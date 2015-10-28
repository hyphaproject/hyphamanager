#include <Poco/ClassLibrary.h>
#include "dht11.h"

using namespace hypha::plugin;
using namespace hypha::plugin::dht11;

void Dht11::loadConfig(std::string json) {
    widget();
    dht11Widget->setHost(QString::fromStdString(host));
    dht11Widget->loadConfig(QString::fromStdString(json));
}

std::string Dht11::getConfig() {
    return dht11Widget->getConfig().toStdString();
}

HyphaPluginConfig *Dht11::getInstance(std::string id) {
    Dht11 *instance = new Dht11();
    instance->setId(id);
    return instance;
}

QWidget *Dht11::widget() {
    if (!dht11Widget)
        dht11Widget = new Dht11Widget();
    return dht11Widget;
}

POCO_BEGIN_MANIFEST(HyphaPlugin)
POCO_EXPORT_CLASS(Dht11)
POCO_END_MANIFEST
