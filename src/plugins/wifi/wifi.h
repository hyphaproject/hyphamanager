#ifndef WIFI_H
#define WIFI_H
#include <QtCore/QObject>
#include "plugin/hyphaplugin.h"
namespace hypha{
namespace plugin{
namespace wifi{
class Wifi : public HyphaPlugin
{
Q_OBJECT
Q_PLUGIN_METADATA(IID "hypha.wifi" FILE "wifi.json")
Q_INTERFACES(hypha::plugin::HyphaPlugin)
public:
    QString getName(){ return "wifi"; }
    QString getTitle() { return "Wifi"; }
    QString getVersion() { return "0.1"; }
    QString getDescription() { return "Plugin to scan for mac adresses in the network.";}
    void loadConfig(QString json);
    QString getConfig();
    HyphaPlugin *getInstance(QString id, QObject *parent);

    QWidget *widget();
private:
};
}
}
}
#endif // WIFI_H
