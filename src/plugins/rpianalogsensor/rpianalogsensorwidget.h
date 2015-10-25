#ifndef RPIANALOGSENSORWIDGET_H
#define RPIANALOGSENSORWIDGET_H

#include <QtWidgets/QWidget>

namespace Ui {
class RpiAnalogSensorWidget;
}

class RpiAnalogSensorWidget : public QWidget {
  Q_OBJECT

 public:
  explicit RpiAnalogSensorWidget(QWidget *parent = 0);
  ~RpiAnalogSensorWidget();
  void setHost(QString host);
  void loadConfig(QString json);
  QString getConfig();
 private:
  Ui::RpiAnalogSensorWidget *ui;
  QString host;
};

#endif // RPIANALOGSENSORWIDGET_H
