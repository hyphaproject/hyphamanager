#ifndef SERVERSTATUS_H
#define SERVERSTATUS_H

#include <QtCore/QObject>
#include "../../handler/hyphahandlerconfig.h"
#include "serverstatuswidget.h"

namespace hypha {
namespace handler {
namespace serverstatus {
class ServerStatus : public HyphaHandlerConfig {
  public:
    explicit ServerStatus();
    ~ServerStatus();
    static ServerStatus *instance();
    std::string name() {
        return "serverstatus";
    }
    std::string getTitle() {
        return "Server Status";
    }
    std::string getVersion() {
        return "0.1";
    }
    std::string getDescription() {
        return "Handler to send server status as email.";
    }
    void parse(std::string message);
    void loadConfig(std::string config);
    std::string getConfig();
    HyphaHandlerConfig *getInstance(std::string id);

    QWidget *widget();

  protected:
    ServerStatusWidget *serverStatusWidget = nullptr;

};
}
}
}

#endif // SERVERSTATUS_H
