#ifndef EMAIL_H
#define EMAIL_H
#include "emailwidget.h"
#include "hyphamanager/hmplugin/hyphapluginconfig.h"
namespace hypha {
namespace plugin {
namespace email {
class EMail : public HyphaPluginConfig {
 public:
  const std::string name() { return "email"; }
  const std::string getTitle() { return "EMail"; }
  const std::string getVersion() { return "0.1"; }
  const std::string getDescription() { return "Plugin to send emails."; }
  void loadConfig(std::string json);
  std::string getConfig();
  HyphaPluginConfig *getInstance(std::string id);
  EMailWidget *emailWidget = 0;
  QWidget *widget();

 private:
  QString language;
};
}
}
}
#endif  // EMAIL_H
