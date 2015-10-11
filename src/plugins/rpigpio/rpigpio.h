#ifndef RPIGPIO_H
#define RPIGPIO_H
#include <QtCore/QObject>
#include "plugin/hyphaplugin.h"
namespace hypha{
namespace plugin{
namespace rpigpio{
class RpiGpio : public HyphaPlugin
{
Q_OBJECT
Q_PLUGIN_METADATA(IID "hypha.rpigpio" FILE "rpigpio.json")
Q_INTERFACES(hypha::plugin::HyphaPlugin)
public:
    QString getName(){ return "rpigpio"; }
    QString getTitle() { return "RPI GPIO"; }
    QString getVersion() { return "0.1"; }
    QString getDescription() { return "Plugin to access gpio of the raspberry pi";}
    void loadConfig(QString json);
    QString getConfig();
    HyphaPlugin *getInstance(QString id, QObject *parent);

    QWidget *widget();

private:
};
}
}
}
#endif // RPIGPIO_H
