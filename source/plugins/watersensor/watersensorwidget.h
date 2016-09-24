// Copyright (c) 2015-2016 Hypha
#ifndef WATERSENSORWIDGET_H
#define WATERSENSORWIDGET_H

#include <QtWidgets/QWidget>

namespace Ui {
class WaterSensorWidget;
}

class WaterSensorWidget : public QWidget {
  Q_OBJECT

 public:
  explicit WaterSensorWidget(QWidget *parent = 0);
  ~WaterSensorWidget();
  void setHost(QString host);
  void loadConfig(QString json);
  QString getConfig();

 private:
  Ui::WaterSensorWidget *ui;
  QString host;
};

#endif  // WATERSENSORWIDGET_H
