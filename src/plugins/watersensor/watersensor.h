#ifndef WATERSENSOR_H
#define WATERSENSOR_H
#include <QtCore/QObject>
#include "plugin/hyphaplugin.h"
#include "watersensorwidget.h"
namespace hypha{
namespace plugin{
namespace watersensor{
class WaterSensor : public HyphaPlugin
{
Q_OBJECT
Q_PLUGIN_METADATA(IID "hypha.watersensor" FILE "watersensor.json")
Q_INTERFACES(hypha::plugin::HyphaPlugin)
public:
    QString getName(){ return "watersensor"; }
    QString getTitle() { return "WaterSensor"; }
    QString getVersion() { return "0.1"; }
    QString getDescription() { return "Read Water Sensor.";}
    void loadConfig(QString json);
    QString getConfig();
    HyphaPlugin *getInstance(QString id, QObject *parent);
    WaterSensorWidget * waterSensorWidget = 0;
    QWidget *widget();

private:
    QString language;
};
}
}
}
#endif // WATERSENSOR_H
