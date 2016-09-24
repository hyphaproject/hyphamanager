// Copyright (c) 2015-2016 Hypha
#ifndef LIGHTSENSORWIDGET_H
#define LIGHTSENSORWIDGET_H

#include <QtWidgets/QWidget>

namespace Ui {
class LightSensorWidget;
}

class LightSensorWidget : public QWidget {
  Q_OBJECT

 public:
  explicit LightSensorWidget(QWidget *parent = 0);
  ~LightSensorWidget();
  void setHost(QString host);
  void loadConfig(QString json);
  QString getConfig();

 private:
  Ui::LightSensorWidget *ui;
  QString host;
};

#endif  // LIGHTSENSORWIDGET_H
