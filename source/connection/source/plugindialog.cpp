// Copyright (c) 2015-2017 Hypha

#include "hyphamanager/connection/plugindialog.h"
#include "ui_plugindialog.h"

#include <hypha/controller/plugin.h>
#include <hypha/plugin/pluginloader.h>
#include <QtWidgets/QMessageBox>

PluginDialog::PluginDialog(hypha::plugin::PluginLoader *pluginLoader,
                           hypha::database::Database *database, QWidget *parent)
    : QDialog(parent), ui(new Ui::PluginDialog) {
  ui->setupUi(this);
  this->pluginLoader = pluginLoader;
  this->database = database;
  init();
}

PluginDialog::~PluginDialog() { delete ui; }

void PluginDialog::init() {
  ui->comboBox->clear();
  for (hypha::plugin::HyphaBasePlugin *plugin : pluginLoader->getPlugins()) {
    ui->comboBox->addItem(QString::fromStdString(plugin->name()));
  }
}

void PluginDialog::on_buttonBox_accepted() {
  hypha::controller::Plugin plugin(this->database);
  try {
    plugin.add(ui->idEdit->text().toStdString(),
               ui->hostEdit->text().toStdString(),
               ui->comboBox->currentText().toStdString(), "{}");
  } catch (Poco::Exception &e) {
    QMessageBox::critical(0, "", QString::fromStdString(e.message()));
  }
  pluginLoader->loadAllInstances();
  init();
}
