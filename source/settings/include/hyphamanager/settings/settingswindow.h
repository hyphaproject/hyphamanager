// Copyright (c) 2015-2016 Hypha
#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <hypha/core/settings/hyphasettings.h>
#include <QDialog>

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QDialog {
  Q_OBJECT

 public:
  explicit SettingsWindow(hypha::settings::HyphaSettings *settings,
                          QWidget *parent = 0);
  ~SettingsWindow();
  void load();

 private:
  Ui::SettingsWindow *ui;

 protected:
  hypha::settings::HyphaSettings *settings;
 private slots:
  void on_buttonBox_accepted();
  void on_pluginsButton_clicked();
};

#endif  // SETTINGSWINDOW_H
