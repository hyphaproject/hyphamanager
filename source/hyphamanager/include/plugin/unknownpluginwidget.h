// Copyright (c) 2015-2016 Hypha
#ifndef UNKNOWNPLUGINWIDGET_H
#define UNKNOWNPLUGINWIDGET_H

#include <string>

#include <hypha/plugin/hyphabaseplugin.h>
#include <QWidget>

namespace Ui {
class UnknownPluginWidget;
}

class UnknownPluginWidget : public QWidget {
  Q_OBJECT

 public:
  explicit UnknownPluginWidget(std::string pluginId, QWidget *parent = 0);
  ~UnknownPluginWidget();
  void loadConfig(std::string json);
  std::string getConfig();

 private:
  Ui::UnknownPluginWidget *ui;
  std::string pluginId;
};

#endif  // UNKNOWNPLUGINWIDGET_H
