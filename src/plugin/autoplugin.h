#ifndef AUTOPLUGIN_H
#define AUTOPLUGIN_H

#include "plugin/hyphapluginconfig.h"
#include "plugin/autopluginwidget.h"

namespace hypha {
namespace plugin {
class AutoPlugin : public HyphaPluginConfig
{
public:
    const std::string name();
    const std::string getTitle();
    const std::string getVersion();
    const std::string getDescription();
    const std::string getConfigDescription();
    void loadConfig(std::string json);
    std::string getConfig();
    HyphaPluginConfig *getInstance(std::string id);
    static HyphaPluginConfig *getInstance(HyphaPlugin *plugin);

    QWidget *widget();

  private:
    HyphaPlugin *plugin = nullptr;
    AutoPluginWidget *pluginWidget = nullptr;
};
}
}

#endif // AUTOPLUGIN_H
