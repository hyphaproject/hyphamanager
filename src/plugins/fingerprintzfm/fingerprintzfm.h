#ifndef FINGERPRINTZFM_H
#define FINGERPRINTZFM_H
#include <iostream>
#include "plugin/hyphapluginconfig.h"
namespace hypha {
namespace plugin {
namespace fingerprintzfm {
class FingerPrintZFM : public HyphaPluginConfig {
 public:
  std::string name() {
    return "fingerprintzfm";
  }
  std::string getTitle() {
    return "FingerprintZFM";
  }
  std::string getVersion() {
    return "0.1";
  }
  std::string getDescription() {
    return "Plugin to detect fingerprint with adafruit zfm.";
  }
  void loadConfig(std::string json);
  std::string getConfig();
  HyphaPluginConfig *getInstance(std::string id);

  QWidget *widget();

 private:
};
}
}
}
#endif // FINGERPRINTZFM_H
