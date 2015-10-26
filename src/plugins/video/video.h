#ifndef VIDEO_H
#define VIDEO_H
#include "plugin/hyphapluginconfig.h"
#include "videowidget.h"
namespace hypha {
namespace plugin {
namespace video {
class Video : public HyphaPluginConfig {
  public:
    std::string name() {
        return "video";
    }
    std::string getTitle() {
        return "Video";
    }
    std::string getVersion() {
        return "0.1";
    }
    std::string getDescription() {
        return "Plugin to capture videos from webcam.";
    }
    void loadConfig(std::string json);
    std::string getConfig();
    HyphaPluginConfig *getInstance(std::string id);

    QWidget *widget();
  private:
    VideoWidget *videoWidget = nullptr;
    std::string language;
};
}
}
}
#endif // VIDEO_H
