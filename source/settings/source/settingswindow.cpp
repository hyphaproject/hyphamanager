// Copyright (c) 2015-2017 Hypha

#include <hyphamanager/settings/settingswindow.h>
#include "ui_settingswindow.h"

#include <QFileDialog>

SettingsWindow::SettingsWindow(hypha::settings::HyphaSettings *settings,
                               QWidget *parent)
    : QDialog(parent), ui(new Ui::SettingsWindow) {
  this->settings = settings;
  ui->setupUi(this);
  load();
}

SettingsWindow::~SettingsWindow() { delete ui; }

void SettingsWindow::load() {
  ui->serverLineEdit->setText(
      QString::fromStdString(settings->getString("email.host", "localhost")));
  ui->usernameLineEdit->setText(
      QString::fromStdString(settings->getString("email.user", "")));
  ui->passwordLineEdit->setText(
      QString::fromStdString(settings->getString("email.password", "")));
  ui->pluginsPathEdit->setText(QString::fromStdString(
      settings->getString("system.pluginspath", "hyphaplugins/")));
}

void SettingsWindow::on_buttonBox_accepted() {
  std::string host = ui->serverLineEdit->text().toStdString();
  settings->setString("email.host", host);
  std::string user = ui->usernameLineEdit->text().toStdString();
  settings->setString("email.user", user);
  std::string password = ui->passwordLineEdit->text().toStdString();
  settings->setString("email.password", password);

  std::string pluginspath = ui->pluginsPathEdit->text().toStdString();
  settings->setString("system.pluginspath", pluginspath);

  settings->save();
}

void SettingsWindow::on_pluginsButton_clicked() {
  QString path = QFileDialog::getExistingDirectory(this, "select plugins path",
                                                   ui->pluginsPathEdit->text());
  ui->pluginsPathEdit->setText(path);
}
