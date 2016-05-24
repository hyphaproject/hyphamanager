#ifndef MANAGERPLUGINLOADER_H
#define MANAGERPLUGINLOADER_H

#include <hypha/plugin/pluginloader.h>
#include "plugin/unknownplugin.h"
#include "plugin/autoplugin.h"

namespace hypha {
namespace plugin {
class ManagerPluginLoader: public PluginLoader
{
public:
    ManagerPluginLoader(hypha::settings::PluginSettings *settings);
    void loadAllInstances();
protected:
    UnknownPlugin * unknownPlugin;
};
}
}

#endif // MANAGERPLUGINLOADER_H
