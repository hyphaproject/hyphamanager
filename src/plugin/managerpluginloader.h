#ifndef MANAGERPLUGINLOADER_H
#define MANAGERPLUGINLOADER_H

#include <hypha/plugin/pluginloader.h>
#include "plugin/unknownplugin.h"

namespace hypha {
namespace plugin {
class ManagerPluginLoader: public PluginLoader
{
public:
    ManagerPluginLoader(hypha::settings::PluginSettings *settings);
    void loadAllInstances();
protected:
    hypha::plugin::UnknownPlugin * unknownPlugin;
};
}
}

#endif // MANAGERPLUGINLOADER_H
