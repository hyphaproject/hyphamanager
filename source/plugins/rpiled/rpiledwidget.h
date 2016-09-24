#ifndef RPILEDWIDGET_H
#define RPILEDWIDGET_H

#include <QtWidgets/QWidget>

namespace Ui {
class RpiLedWidget;
}

class RpiLedWidget : public QWidget {
  Q_OBJECT

 public:
  explicit RpiLedWidget(QWidget *parent = 0);
  ~RpiLedWidget();
  void setHost(QString host);
  void loadConfig(QString json);
  QString getConfig();

 private:
  Ui::RpiLedWidget *ui;
  QString host;
};

#endif  // RPILEDWIDGET_H
