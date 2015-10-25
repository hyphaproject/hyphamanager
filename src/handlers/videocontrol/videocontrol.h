#ifndef VIDEOCONTROL_H
#define VIDEOCONTROL_H

#include "../../handler/hyphahandlerconfig.h"
#include "videocontrolwidget.h"

namespace hypha {
namespace handler {
namespace videocontrol {
class VideoControl : public HyphaHandlerConfig {
  public:
    explicit VideoControl();
    ~VideoControl();
    static VideoControl * instance();
    std::string name() {
        return "videocontrol";
    }
    std::string getTitle() {
        return "VideoControl";
    }
    std::string getVersion() {
        return "0.1";
    }
    std::string getDescription() {
        return "Handler for Video Control.";
    }
    void parse(std::string message);
    void loadConfig(std::string config);
    std::string getConfig();
    HyphaHandlerConfig *getInstance(std::string id);

    QWidget *widget();

  protected:
    std::string mastercard;
    VideoControlWidget *vcwidget = nullptr;

};
}
}
}

#endif // VIDEOCONTROL_H
