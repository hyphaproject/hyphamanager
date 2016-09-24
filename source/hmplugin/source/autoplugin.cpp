// Copyright (c) 2015-2016 Hypha
#include "hyphamanager/hmplugin/autoplugin.h"
#include <hypha/plugin/pluginfactory.h>

using namespace hypha::plugin;

const std::string AutoPlugin::name() { return plugin->name(); }

const std::string AutoPlugin::getTitle() { return plugin->getTitle(); }

const std::string AutoPlugin::getVersion() { return plugin->getVersion(); }

const std::string AutoPlugin::getDescription() {
  return plugin->getDescription();
}

const std::string AutoPlugin::getConfigDescription() {
  return plugin->getConfigDescription();
}

void AutoPlugin::loadConfig(std::string json) {
  widget();
  pluginWidget->loadConfig(json);
}

std::string AutoPlugin::getConfig() { return pluginWidget->getConfig(); }

HyphaPluginConfig *AutoPlugin::getInstance(std::string id) { return nullptr; }

HyphaPluginConfig *AutoPlugin::getInstance(HyphaPlugin *plugin) {
  AutoPlugin *instance = new AutoPlugin();
  instance->plugin = plugin;
  instance->setId(plugin->getId());
  return instance;
}

QWidget *AutoPlugin::widget() {
  if (!pluginWidget) pluginWidget = new AutoPluginWidget(plugin);
  return pluginWidget;
}
