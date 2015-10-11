#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H
#include <QtCore/QObject>
#include "plugin/hyphaplugin.h"
#include "lightsensorwidget.h"
namespace hypha{
namespace plugin{
namespace lightsensor{
class LightSensor : public HyphaPlugin
{
Q_OBJECT
Q_PLUGIN_METADATA(IID "hypha.lightsensor" FILE "lightsensor.json")
Q_INTERFACES(hypha::plugin::HyphaPlugin)
public:
    QString getName(){ return "lightsensor"; }
    QString getTitle() { return "LightSensor"; }
    QString getVersion() { return "0.1"; }
    QString getDescription() { return "Read Light Sensor.";}
    void loadConfig(QString json);
    QString getConfig();
    HyphaPlugin *getInstance(QString id, QObject *parent);
    LightSensorWidget * lightSensorWidget = 0;
    QWidget *widget();

private:
    QString language;
};
}
}
}
#endif // LIGHTSENSOR_H
