#ifndef EMAIL_H
#define EMAIL_H
#include <QtCore/QObject>
#include "plugin/hyphaplugin.h"
#include "dht11widget.h"
namespace hypha{
namespace plugin{
namespace dht11{
class Dht11 : public HyphaPlugin
{
Q_OBJECT
Q_PLUGIN_METADATA(IID "hypha.dht11" FILE "dht11.json")
Q_INTERFACES(hypha::plugin::HyphaPlugin)
public:
    QString getName(){ return "dht11"; }
    QString getTitle() { return "Dht11"; }
    QString getVersion() { return "0.1"; }
    QString getDescription() { return "Read Temperature and Humidity.";}
    void loadConfig(QString json);
    QString getConfig();
    HyphaPlugin *getInstance(QString id, QObject *parent);
    Dht11Widget * dht11Widget = 0;
    QWidget *widget();

private:
    QString language;
};
}
}
}
#endif // EMAIL_H
