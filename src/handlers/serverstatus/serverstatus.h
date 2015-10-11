#ifndef SERVERSTATUS_H
#define SERVERSTATUS_H

#include <QtCore/QObject>
#include "../../handler/hyphahandler.h"
#include "serverstatuswidget.h"

namespace hypha{
namespace handler{
namespace serverstatus{
class ServerStatus : public HyphaHandler
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "hypha.serverstatus" FILE "serverstatus.json")
    Q_INTERFACES(hypha::handler::HyphaHandler)
public:
    explicit ServerStatus();
    ~ServerStatus();
    static ServerStatus * instance();
    QString getName(){ return "serverstatus"; }
    QString getTitle() { return "Server Status"; }
    QString getVersion() { return "0.1"; }
    QString getDescription() { return "Handler to send server status as email.";}
    void parse(QString message);
    void loadConfig(QString config);
    QString getConfig();
    HyphaHandler *getInstance(QString id, QObject *parent);

    QWidget *widget();

protected:
    ServerStatusWidget *serverStatusWidget = 0;

};
}
}
}

#endif // SERVERSTATUS_H
