#ifndef RPIPIR_H
#define RPIPIR_H
#include <QtCore/QObject>
#include "plugin/hyphaplugin.h"
#include "rpipirwidget.h"
namespace hypha{
namespace plugin{
namespace rpipir{
class RpiPir : public HyphaPlugin
{
Q_OBJECT
Q_PLUGIN_METADATA(IID "hypha.rpipir" FILE "rpipir.json")
Q_INTERFACES(hypha::plugin::HyphaPlugin)
public:
    QString getName(){ return "rpipir"; }
    QString getTitle() { return "RPI PIR"; }
    QString getVersion() { return "0.1"; }
    QString getDescription() { return "Plugin to detect motion with a motion sensor.";}
    void loadConfig(QString json);
    QString getConfig();
    HyphaPlugin *getInstance(QString id, QObject *parent);
    QWidget *widget();

private:
    RpiPirWidget * rpipirWidget = 0;
};
}
}
}
#endif // RPIPIR_H
