#ifndef EXPLORENFC_H
#define EXPLORENFC_H
#include <QtCore/QObject>
#include "plugin/hyphaplugin.h"
namespace hypha{
namespace plugin{
namespace explorenfc{
class ExploreNFC : public HyphaPlugin
{
Q_OBJECT
Q_PLUGIN_METADATA(IID "hypha.explorenfc" FILE "explorenfc.json")
Q_INTERFACES(hypha::plugin::HyphaPlugin)
public:
    QString getName(){ return "explorenfc"; }
    QString getTitle() { return "ExploreNFC"; }
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
#endif // EXPLORENFC_H
