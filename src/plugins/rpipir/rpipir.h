#ifndef RPIPIR_H
#define RPIPIR_H
#include "plugin/hyphapluginconfig.h"
#include "rpipirwidget.h"
namespace hypha{
namespace plugin{
namespace rpipir{
class RpiPir : public HyphaPluginConfig
{
public:
    std::string name(){ return "rpipir"; }
    std::string getTitle() { return "RPI PIR"; }
    std::string getVersion() { return "0.1"; }
    std::string getDescription() { return "Plugin to detect motion with a motion sensor.";}
    void loadConfig(std::string json);
    std::string getConfig();
    HyphaPluginConfig *getInstance(std::string id);
    QWidget *widget();

private:
    RpiPirWidget * rpipirWidget = nullptr;
};
}
}
}
#endif // RPIPIR_H
