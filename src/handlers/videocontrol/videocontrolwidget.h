#ifndef DOOROPENERWIDGET_H
#define DOOROPENERWIDGET_H

#include <QtWidgets/QWidget>

namespace Ui {
class VideoControlWidget;
}

class VideoControlWidget : public QWidget {
  Q_OBJECT

 public:
  explicit VideoControlWidget(QWidget *parent = 0);
  ~VideoControlWidget();
  void loadConfig(QString config);
  QString getConfig();

 private:
  Ui::VideoControlWidget *ui;
};

#endif // VIDEOCONTROLWIDGET_H
