#ifndef UNKNOWNHANDLER_H
#define UNKNOWNHANDLER_H

#include "handler/hyphahandlerconfig.h"
#include "handler/unknownhandlerwidget.h"
namespace hypha {
namespace handler {
class UnknownHandler: public HyphaHandlerConfig {
public:
    const std::string name() {
        return "unknownhandler";
    }
    const std::string getTitle() {
        return "Unknown Handler";
    }
    const std::string getVersion() {
        return "0.1";
    }
    const std::string getDescription() {
        return "";
    }
    void loadConfig(std::string json);
    std::string getConfig();
    HyphaHandlerConfig *getInstance(std::string id);

    QWidget *widget();

  private:
    UnknownHandlerWidget *unknownHandlerWidget = nullptr;

};
}
}
#endif // UNKNOWNHANDLER_H
