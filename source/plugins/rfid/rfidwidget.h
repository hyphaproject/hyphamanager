// Copyright (c) 2015-2016 Hypha
#ifndef RFIDWIDGET_H
#define RFIDWIDGET_H

#include <QtWidgets/QWidget>

namespace Ui {
class RFIDWidget;
}

class RFIDWidget : public QWidget {
  Q_OBJECT

 public:
  explicit RFIDWidget(QWidget *parent = 0);
  ~RFIDWidget();

 private:
  Ui::RFIDWidget *ui;
};

#endif  // RFIDWIDGET_H
