#include "hyphamanager/hmplugin/unknownplugin.h"

using namespace hypha::plugin;

void UnknownPlugin::loadConfig(std::string json) {
    widget();
    unknownPluginWidget->loadConfig(json);
}

std::string UnknownPlugin::getConfig() {
    return unknownPluginWidget->getConfig();
}

HyphaPluginConfig *UnknownPlugin::getInstance(std::string id) {
    UnknownPlugin *instance = new UnknownPlugin();
    instance->setId(id);
    return instance;
}

QWidget *UnknownPlugin::widget() {
    if (!unknownPluginWidget)
        unknownPluginWidget = new UnknownPluginWidget();
    return unknownPluginWidget;
}
