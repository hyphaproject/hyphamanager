#ifndef RPILED_H
#define RPILED_H
#include "plugin/hyphapluginconfig.h"
#include "rpiledwidget.h"
namespace hypha{
namespace plugin{
namespace rpiled{
class RpiLed : public HyphaPluginConfig
{
public:
    std::string name(){ return "rpiled"; }
    std::string getTitle() { return "RpiLed"; }
    std::string getVersion() { return "0.1"; }
    std::string getDescription() { return "LED of raspberry pi";}
    void loadConfig(std::string json);
    std::string getConfig();
    HyphaPluginConfig *getInstance(std::string id);

    QWidget *widget();

private:
    RpiLedWidget * rpiledWidget = nullptr;
};
}
}
}
#endif // RPILED_H
