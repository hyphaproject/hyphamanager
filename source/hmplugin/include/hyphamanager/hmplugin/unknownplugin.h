#ifndef UNKNOWNPLUGIN_H
#define UNKNOWNPLUGIN_H

#include <hyphamanager/hmplugin/hyphapluginconfig.h>
#include <hyphamanager/hmplugin/unknownpluginwidget.h>
namespace hypha {
namespace plugin {
class HMPLUGIN_API UnknownPlugin : public HyphaPluginConfig {
 public:
  const std::string name() { return "unknownplugin"; }
  const std::string getTitle() { return "Unknown Plugin"; }
  const std::string getVersion() { return "0.1"; }
  const std::string getDescription() { return ""; }
  const std::string getConfigDescription() { return "{}"; }
  void loadConfig(std::string json);
  std::string getConfig();
  HyphaPluginConfig *getInstance(std::string id);

  QWidget *widget();

 private:
  UnknownPluginWidget *unknownPluginWidget = nullptr;
};
}
}

#endif  // UNKNOWNPLUGIN_H
