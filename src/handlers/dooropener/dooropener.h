#ifndef DOOROPENER_H
#define DOOROPENER_H

#include <QtCore/QObject>
#include "../../handler/hyphahandler.h"
#include "dooropenerwidget.h"

namespace hypha{
namespace handler{
namespace dooropener{
class DoorOpener : public HyphaHandler
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "hypha.dooropener" FILE "dooropener.json")
    Q_INTERFACES(hypha::handler::HyphaHandler)
public:
    explicit DoorOpener();
    ~DoorOpener();
    static DoorOpener * instance();
    QString getName(){ return "dooropener"; }
    QString getTitle() { return "DoorOpener"; }
    QString getVersion() { return "0.1"; }
    QString getDescription() { return "Handler to open doors.";}
    void parse(QString message);
    void loadConfig(QString config);
    QString getConfig();
    HyphaHandler *getInstance(QString id, QObject *parent);

    QWidget *widget();

protected:
    DoorOpenerWidget * doorWidget = 0;

};
}
}
}

#endif // DOOROPENER_H
