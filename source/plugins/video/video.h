// Copyright (c) 2015-2016 Hypha
#ifndef VIDEO_H
#define VIDEO_H
#include "hyphamanager/hmplugin/hyphapluginconfig.h"
#include "videowidget.h"
namespace hypha {
namespace plugin {
namespace video {
class Video : public HyphaPluginConfig {
 public:
  const std::string name() { return "video"; }
  const std::string getTitle() { return "Video"; }
  const std::string getVersion() { return "0.1"; }
  const std::string getDescription() {
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
#endif  // VIDEO_H
