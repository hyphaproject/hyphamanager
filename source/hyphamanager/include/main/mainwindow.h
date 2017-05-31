// Copyright (c) 2015-2016 Hypha
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <hyphamanager/core/instance.h>
#include <hyphamanager/user/userwindow.h>
#include <QtWidgets/QMainWindow>
#include "../connection/connectionwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

 private slots:
  void onLanguageChosen();
  void on_actionAbout_Hypha_Client_triggered();

  void on_actionOpen_triggered();

  void on_actionSettings_triggered();

  void closeEvent(QCloseEvent *event);

  void on_actionNew_triggered();

 private:
  Ui::MainWindow *ui;
  void createLanguageMenu();
  Instance *instance = nullptr;
  UserWindow *userWindow = nullptr;
  ConnectionWindow *connectionWindow = nullptr;
};

#endif  // MAINWINDOW_H
