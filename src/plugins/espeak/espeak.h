#ifndef ESPEAK_H
#define ESPEAK_H
#include <QtCore/QObject>
#include "plugin/hyphaplugin.h"
namespace hypha{
namespace plugin{
namespace espeak{
class ESpeak : public HyphaPlugin
{
Q_OBJECT
Q_PLUGIN_METADATA(IID "hypha.espeak" FILE "espeak.json")
Q_INTERFACES(hypha::plugin::HyphaPlugin)
public:
    QString getName(){ return "espeak"; }
    QString getTitle() { return "ESpeak"; }
    QString getVersion() { return "0.1"; }
    QString getDescription() { return "Plugin to speak text with espeak.";}
    void loadConfig(QString json);
    QString getConfig();
    HyphaPlugin *getInstance(QString id, QObject *parent);

    QWidget *widget();

private:
    QString language;
};
}
}
}
#endif // ESPEAK_H
