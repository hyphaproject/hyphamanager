#ifndef FLAME_H
#define FLAME_H
#include "plugin/hyphapluginconfig.h"
#include "flamewidget.h"
namespace hypha{
namespace plugin{
namespace flame{
class Flame : public HyphaPluginConfig
{
public:
    std::string name(){ return "flame"; }
    std::string getTitle() { return "Flame"; }
    std::string getVersion() { return "0.1"; }
    std::string getDescription() { return "Read Flame Sensor.";}
    void loadConfig(std::string json);
    std::string getConfig();
    HyphaPluginConfig *getInstance(std::string id);

    QWidget *widget();

private:
    FlameWidget * flameWidget = nullptr;
    std::string language;
};
}
}
}
#endif // FLAME_H
