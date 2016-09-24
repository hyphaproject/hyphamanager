// Copyright (c) 2015-2016 Hypha
#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QtWidgets/QSplashScreen>
#include <QtWidgets/QWidget>

class SplashScreen : public QSplashScreen {
  Q_OBJECT
 public:
  explicit SplashScreen(QWidget *parent = 0);

 signals:

 public slots:
  void setMessage(QString message);
};

#endif  // SPLASHSCREEN_H
