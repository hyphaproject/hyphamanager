#ifndef AUTOPLUGIN_H
#define AUTOPLUGIN_H

#include <hyphamanager/hmplugin/autopluginwidget.h>
#include <hyphamanager/hmplugin/hmplugin_api.h>
#include <hyphamanager/hmplugin/hyphapluginconfig.h>

namespace hypha {
namespace plugin {
class HMPLUGIN_API AutoPlugin : public HyphaPluginConfig {
 public:
  const std::string name();
  const std::string getTitle();
  const std::string getVersion();
  const std::string getDescription();
  const std::string getConfigDescription();
  void loadConfig(std::string json);
  std::string getConfig();
  HyphaPluginConfig *getInstance(std::string id);
  static HyphaPluginConfig *getInstance(HyphaPlugin *plugin);

  QWidget *widget();

 private:
  HyphaPlugin *plugin = nullptr;
  AutoPluginWidget *pluginWidget = nullptr;
};
}
}

#endif  // AUTOPLUGIN_H
