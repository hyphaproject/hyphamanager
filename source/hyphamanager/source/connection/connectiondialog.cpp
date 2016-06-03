// Copyright (c) 2015-2016 Hypha

#include <hypha/controller/connection.h>
#include <hypha/core/database/database.h>
#include <hypha/handler/handlerloader.h>
#include <hypha/plugin/pluginloader.h>

#include "connection/connectiondialog.h"
#include "connection/connectionitem.h"
#include "ui_connectiondialog.h"

#include <Poco/Data/RecordSet.h>

ConnectionDialog::ConnectionDialog(hypha::handler::HandlerLoader *handlerLoader,
                                   hypha::plugin::PluginLoader *pluginLoader,
                                   hypha::database::Database *database,
                                   QWidget *parent)
    : QDialog(parent), ui(new Ui::ConnectionDialog) {
  ui->setupUi(this);
  this->handlerLoader = handlerLoader;
  this->pluginLoader = pluginLoader;
  this->database = database;
  init();
}

ConnectionDialog::~ConnectionDialog() { delete ui; }

void ConnectionDialog::init() {
  ui->listWidget->clear();
  ui->handlerComboBox->clear();
  ui->pluginComboBox->clear();
  for (hypha::handler::HyphaHandler *handler : handlerLoader->getInstances()) {
    ui->handlerComboBox->addItem(QString::fromStdString(handler->getId()));
  }
  for (hypha::plugin::HyphaPlugin *plugin : pluginLoader->getInstances()) {
    ui->pluginComboBox->addItem(QString::fromStdString(plugin->getId()));
  }

  hypha::controller::Connection con(this->database);
  for (std::tuple<std::string, std::string, std::string> t :
       con.getConnections()) {
    std::string id = std::get<0>(t);
    std::string handlerId = std::get<1>(t);
    std::string pluginId = std::get<2>(t);
    QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
    ui->listWidget->addItem(item);
    ConnectionItem *connectionItem = new ConnectionItem(
        QString::fromStdString(id), QString::fromStdString(handlerId),
        QString::fromStdString(pluginId), database);
    item->setSizeHint(connectionItem->minimumSizeHint());
    ui->listWidget->setItemWidget(item, connectionItem);
  }
}

void ConnectionDialog::on_deleteButton_clicked() {
  ConnectionItem *item = (ConnectionItem *)ui->listWidget->itemWidget(
      ui->listWidget->currentItem());
  if (item) {
    item->deleteFromDatabase();
    init();
  }
}

void ConnectionDialog::on_addButton_clicked() {
  hypha::controller::Connection con(this->database);
  con.create(ui->handlerComboBox->currentText().toStdString(),
             ui->pluginComboBox->currentText().toStdString());
  init();
}
