// Copyright (c) 2015-2016 Hypha
#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QtWidgets/QWidget>

namespace Ui {
class VideoWidget;
}

class VideoWidget : public QWidget {
  Q_OBJECT

 public:
  explicit VideoWidget(QWidget *parent = 0);
  ~VideoWidget();
  void setHost(QString host);
  void loadConfig(QString json);
  QString getConfig();

 private:
  Ui::VideoWidget *ui;
  QString host;
};

#endif  // VIDEOWIDGET_H
