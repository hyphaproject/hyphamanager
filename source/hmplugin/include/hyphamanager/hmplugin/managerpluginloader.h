#ifndef MANAGERPLUGINLOADER_H
#define MANAGERPLUGINLOADER_H

#include <hypha/plugin/pluginloader.h>
#include <hyphamanager/hmplugin/unknownplugin.h>
#include <hyphamanager/hmplugin/hmplugin_api.h>

namespace hypha {
namespace plugin {
class HMPLUGIN_API ManagerPluginLoader: public PluginLoader
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
