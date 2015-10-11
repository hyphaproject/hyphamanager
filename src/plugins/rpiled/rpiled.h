#ifndef RPILED_H
#define RPILED_H
#include <QtCore/QObject>
#include "plugin/hyphaplugin.h"
#include "rpiledwidget.h"
namespace hypha{
namespace plugin{
namespace rpiled{
class RpiLed : public HyphaPlugin
{
Q_OBJECT
Q_PLUGIN_METADATA(IID "hypha.rpiled" FILE "rpiled.json")
Q_INTERFACES(hypha::plugin::HyphaPlugin)
public:
    QString getName(){ return "rpiled"; }
    QString getTitle() { return "RpiLed"; }
    QString getVersion() { return "0.1"; }
    QString getDescription() { return "LED of raspberry pi";}
    void loadConfig(QString json);
    QString getConfig();
    HyphaPlugin *getInstance(QString id, QObject *parent);
    RpiLedWidget * rpiledWidget = 0;
    QWidget *widget();

private:
};
}
}
}
#endif // RPILED_H
