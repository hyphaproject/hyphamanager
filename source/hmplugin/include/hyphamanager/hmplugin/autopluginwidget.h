// Copyright (c) 2015-2016 Hypha
#ifndef AUTOPLUGINWIDGET_H
#define AUTOPLUGINWIDGET_H

#include <hypha/plugin/hyphaplugin.h>
#include <hyphamanager/hmplugin/hmplugin_api.h>
#include <QWidget>
#include <map>
#include <string>

namespace Ui {
class AutoPluginWidget;
}

class HMPLUGIN_API AutoPluginWidget : public QWidget {
  Q_OBJECT

 public:
  explicit AutoPluginWidget(hypha::plugin::HyphaPlugin* plugin,
                            QWidget* parent = 0);
  ~AutoPluginWidget();
  void setupUi();
  void loadConfig(std::string json);
  std::string getConfig();

 protected:
  void addWidgets(QWidget* widget1, QWidget* widget2 = nullptr);

 private:
  hypha::plugin::HyphaPlugin* plugin;
  Ui::AutoPluginWidget* ui;
  std::map<std::string, QWidget*> items;
};

#endif  // AUTOPLUGINWIDGET_H
