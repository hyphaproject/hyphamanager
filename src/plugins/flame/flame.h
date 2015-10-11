#ifndef FLAME_H
#define FLAME_H
#include <QtCore/QObject>
#include "plugin/hyphaplugin.h"
#include "flamewidget.h"
namespace hypha{
namespace plugin{
namespace flame{
class Flame : public HyphaPlugin
{
Q_OBJECT
Q_PLUGIN_METADATA(IID "hypha.flame" FILE "flame.json")
Q_INTERFACES(hypha::plugin::HyphaPlugin)
public:
    QString getName(){ return "flame"; }
    QString getTitle() { return "Flame"; }
    QString getVersion() { return "0.1"; }
    QString getDescription() { return "Read Flame Sensor.";}
    void loadConfig(QString json);
    QString getConfig();
    HyphaPlugin *getInstance(QString id, QObject *parent);
    FlameWidget * flameWidget = 0;
    QWidget *widget();

private:
    QString language;
};
}
}
}
#endif // FLAME_H
