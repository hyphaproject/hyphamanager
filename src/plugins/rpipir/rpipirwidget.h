#ifndef RPIPIRWIDGET_H
#define RPIPIRWIDGET_H

#include <QtWidgets/QWidget>

namespace Ui {
class RpiPirWidget;
}

class RpiPirWidget : public QWidget {
  Q_OBJECT

 public:
  explicit RpiPirWidget(QWidget *parent = 0);
  ~RpiPirWidget();
  void loadConfig(QString json);
  QString getConfig();

 private:
  Ui::RpiPirWidget *ui;
};

#endif // RPIPIRWIDGET_H
