#ifndef RPIANALOGSENSOR_H
#define RPIANALOGSENSOR_H
#include <QtCore/QObject>
#include "plugin/hyphaplugin.h"
#include "rpianalogsensorwidget.h"
namespace hypha{
namespace plugin{
namespace rpianalogsensor{
class RpiAnalogSensor : public HyphaPlugin
{
Q_OBJECT
Q_PLUGIN_METADATA(IID "hypha.rpianalogsensor" FILE "rpianalogsensor.json")
Q_INTERFACES(hypha::plugin::HyphaPlugin)
public:
    QString getName(){ return "rpianalogsensor"; }
    QString getTitle() { return "RpiAnalogSensor"; }
    QString getVersion() { return "0.1"; }
    QString getDescription() { return "Read Water Sensor.";}
    void loadConfig(QString json);
    QString getConfig();
    HyphaPlugin *getInstance(QString id, QObject *parent);
    RpiAnalogSensorWidget * rpiAnalogSensorWidget = 0;
    QWidget *widget();

private:
    QString language;
};
}
}
}
#endif // RPIANALOGSENSOR_H
