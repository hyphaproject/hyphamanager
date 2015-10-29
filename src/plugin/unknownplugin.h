#ifndef UNKNOWNPLUGIN_H
#define UNKNOWNPLUGIN_H

#include "plugin/hyphapluginconfig.h"
#include "plugin/unknownpluginwidget.h"
namespace hypha {
namespace plugin {
class UnknownPlugin: public HyphaPluginConfig {
public:
    std::string name() {
        return "unknownplugin";
    }
    std::string getTitle() {
        return "Unknown Plugin";
    }
    std::string getVersion() {
        return "0.1";
    }
    std::string getDescription() {
        return "";
    }
    void loadConfig(std::string json);
    std::string getConfig();
    HyphaPluginConfig *getInstance(std::string id);

    QWidget *widget();

  private:
    UnknownPluginWidget *unknownPluginWidget = nullptr;
};
}
}

#endif // UNKNOWNPLUGIN_H
