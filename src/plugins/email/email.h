#ifndef EMAIL_H
#define EMAIL_H
#include "plugin/hyphapluginconfig.h"
#include "emailwidget.h"
namespace hypha{
namespace plugin{
namespace email{
class EMail : public HyphaPluginConfig
{
public:
    std::string name(){ return "email"; }
    std::string getTitle() { return "EMail"; }
    std::string getVersion() { return "0.1"; }
    std::string getDescription() { return "Plugin to send emails.";}
    void loadConfig(std::string json);
    std::string getConfig();
    HyphaPluginConfig *getInstance(std::string id);
    EMailWidget * emailWidget = 0;
    QWidget *widget();

private:
    QString language;
};
}
}
}
#endif // EMAIL_H
