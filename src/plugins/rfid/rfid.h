#ifndef RFID_H
#define RFID_H
#include <QtCore/QObject>
#include <QtSerialPort/QSerialPort>
#include "plugin/hyphaplugin.h"
namespace hypha{
namespace plugin{
namespace rfid{
class RFID : public HyphaPlugin
{
Q_OBJECT
Q_PLUGIN_METADATA(IID "hypha.rfid" FILE "rfid.json")
Q_INTERFACES(hypha::plugin::HyphaPlugin)
public:
    QString getName(){ return "rfid"; }
    QString getTitle() { return "RFID"; }
    QString getVersion() { return "0.1"; }
    QString getDescription() { return "Plugin to detect rfid cards.";}
    void loadConfig(QString json);
    QString getConfig();
    HyphaPlugin *getInstance(QString id, QObject *parent);

    QWidget *widget();

private:
};
}
}
}
#endif // RFID_H
