// Copyright (c) 2015-2016 Hypha
#ifndef FINGERPRINTZFM_H
#define FINGERPRINTZFM_H
#include <iostream>
#include "hyphamanager/hmplugin/hyphapluginconfig.h"
namespace hypha {
namespace plugin {
namespace fingerprintzfm {
class FingerPrintZFM : public HyphaPluginConfig {
 public:
  const std::string name() { return "fingerprintzfm"; }
  const std::string getTitle() { return "FingerprintZFM"; }
  const std::string getVersion() { return "0.1"; }
  const std::string getDescription() {
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
#endif  // FINGERPRINTZFM_H
