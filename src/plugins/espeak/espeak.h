#ifndef ESPEAK_H
#define ESPEAK_H
#include <QtCore/QObject>
#include "plugin/hyphapluginconfig.h"
namespace hypha{
namespace plugin{
namespace espeak{
class ESpeak : public HyphaPluginConfig
{
public:
    std::string name(){ return "espeak"; }
    std::string getTitle() { return "ESpeak"; }
    std::string getVersion() { return "0.1"; }
    std::string getDescription() { return "Plugin to speak text with espeak.";}
    void loadConfig(std::string json);
    std::string getConfig();
    HyphaPluginConfig *getInstance(std::string id);

    QWidget *widget();

private:
    std::string language;
};
}
}
}
#endif // ESPEAK_H
