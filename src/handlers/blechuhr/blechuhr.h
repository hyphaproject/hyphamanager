#ifndef BLECHUHR_H
#define BLECHUHR_H

#include "../../handler/hyphahandlerconfig.h"
#include "blechuhrwidget.h"

namespace hypha {
namespace handler {
namespace blechuhr {
class BlechUhr : public HyphaHandlerConfig {
 public:
  explicit BlechUhr();
  ~BlechUhr();
  static BlechUhr *instance();
  std::string name() {
    return "blechuhr";
  }
  std::string getTitle() {
    return "Blechuhr";
  }
  std::string getVersion() {
    return "0.1";
  }
  std::string getDescription() {
    return "Handler like a time recorder.";
  }
  void parse(std::string message);
  void loadConfig(std::string config);
  std::string getConfig();
  HyphaHandlerConfig *getInstance(std::string id);

  QWidget *widget();

 private:
 protected:
  BlechUhrWidget *buwidget = nullptr;


};
}
}
}

#endif // BLECHUHR_H
