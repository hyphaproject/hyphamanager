#ifndef FINGERPRINTZFM_H
#define FINGERPRINTZFM_H
#include <QtCore/QObject>
#include <iostream>
#include "plugin/hyphaplugin.h"
namespace hypha{
namespace plugin{
namespace fingerprintzfm{
class FingerPrintZFM : public HyphaPlugin
{
Q_OBJECT
Q_PLUGIN_METADATA(IID "hypha.fingerprintzfm" FILE "fingerprintzfm.json")
Q_INTERFACES(hypha::plugin::HyphaPlugin)
public:
    QString getName(){ return "fingerprintzfm"; }
    QString getTitle() { return "FingerprintZFM"; }
    QString getVersion() { return "0.1"; }
    QString getDescription() { return "Plugin to detect fingerprint with adafruit zfm.";}
    void loadConfig(QString json);
    QString getConfig();
    HyphaPlugin *getInstance(QString id, QObject *parent);

    QWidget *widget();

private:
};
}
}
}
#endif // FINGERPRINTZFM_H
