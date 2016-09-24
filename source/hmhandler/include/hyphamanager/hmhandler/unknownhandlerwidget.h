// Copyright (c) 2015-2016 Hypha
#ifndef UNKNOWNHANDLERWIDGET_H
#define UNKNOWNHANDLERWIDGET_H

#include <hyphamanager/hmhandler/hmhandler_api.h>
#include <QWidget>

namespace Ui {
class UnknownHandlerWidget;
}

class HMHANDLER_API UnknownHandlerWidget : public QWidget {
  Q_OBJECT

 public:
  explicit UnknownHandlerWidget(QWidget *parent = 0);
  ~UnknownHandlerWidget();
  void loadConfig(std::string json);
  std::string getConfig();

 private:
  Ui::UnknownHandlerWidget *ui;
};

#endif  // UNKNOWNHANDLERWIDGET_H
