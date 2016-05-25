#include <hypha/core/settings/pluginsettings.h>
#include <hypha/plugin/pluginfactory.h>
#include "plugin/autoplugin.h"

#include "managerpluginloader.h"

using namespace hypha::plugin;

ManagerPluginLoader::ManagerPluginLoader(
    hypha::settings::PluginSettings *settings)
    : PluginLoader(settings) {
  unknownPlugin = new UnknownPlugin();
}

void hypha::plugin::ManagerPluginLoader::loadAllInstances() {
  for (std::string id : settings->getAllPluginIds()) {
    if (getPluginInstance(id) == 0) {
      HyphaPlugin *plugin = factory->loadPlugin(id);
      if (plugin) {
        if (dynamic_cast<HyphaPluginConfig *>(plugin) == nullptr)
          plugin = AutoPlugin::getInstance(plugin);
      }
      if (plugin){}
      else {
        plugin = unknownPlugin->getInstance(id);

      }
      std::string host = settings->getHost(id);
      std::string config = settings->getConfig(id);
      plugin->setHost(host);
      plugin->loadConfig(config);
      pluginInstances[id] = plugin;
    }
  }
}
