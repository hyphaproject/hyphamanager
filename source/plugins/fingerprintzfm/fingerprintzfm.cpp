#include "fingerprintzfm.h"
#include <Poco/ClassLibrary.h>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QProcess>
#include <QtCore/QThread>
#include <QtCore/QVariant>
#include <QtSerialPort/QSerialPortInfo>
#include "fingerprintzfmwidget.h"

using namespace hypha::plugin::fingerprintzfm;
using namespace hypha::plugin;

void FingerPrintZFM::loadConfig(std::string json) {}

std::string FingerPrintZFM::getConfig() { return "{}"; }

HyphaPluginConfig *FingerPrintZFM::getInstance(std::string id) {
  FingerPrintZFM *instance = new FingerPrintZFM();
  instance->setId(id);
  return instance;
}

QWidget *FingerPrintZFM::widget() { return new FingerPrintZFMWidget(); }

POCO_BEGIN_MANIFEST(HyphaPlugin)
POCO_EXPORT_CLASS(FingerPrintZFM)
POCO_END_MANIFEST
