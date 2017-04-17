// Copyright (c) 2015-2017 Hypha
#ifndef AUTOPLUGINWIDGET_H
#define AUTOPLUGINWIDGET_H

#include <map>
#include <string>

#include <hypha/plugin/hyphabaseplugin.h>

#include <QWidget>

namespace Ui {
class AutoPluginWidget;
}

class AutoPluginWidget : public QWidget {
  Q_OBJECT

 public:
  explicit AutoPluginWidget(hypha::plugin::HyphaBasePlugin* plugin,
                            QWidget* parent = 0);
  ~AutoPluginWidget();
  void setupUi();
  void loadConfig(std::string json);
  std::string getConfig();

 protected:
  void addWidgets(QWidget* widget1, QWidget* widget2 = nullptr);

 private:
  hypha::plugin::HyphaBasePlugin* plugin;
  Ui::AutoPluginWidget* ui;
  std::map<std::string, QWidget*> items;
};

#endif  // AUTOPLUGINWIDGET_H
