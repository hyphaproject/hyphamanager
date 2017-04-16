// Copyright (c) 2015-2017 Hypha

#include "connection/connectiondialog.h"
#include "connection/connectionitem.h"
#include "ui_connectiondialog.h"

#include <hypha/controller/connection.h>
#include <hypha/core/database/database.h>
#include <hypha/plugin/pluginloader.h>
#include <hypha/plugin/pluginutil.h>

#include <Poco/Data/RecordSet.h>

ConnectionDialog::ConnectionDialog(hypha::plugin::PluginLoader *pluginLoader,
                                   hypha::database::Database *database,
                                   QWidget *parent)
    : QDialog(parent), ui(new Ui::ConnectionDialog) {
  ui->setupUi(this);
  this->pluginLoader = pluginLoader;
  this->database = database;
  init();
}

ConnectionDialog::~ConnectionDialog() { delete ui; }

void ConnectionDialog::init() {
  ui->listWidget->clear();
  ui->senderComboBox->clear();
  ui->receiverComboBox->clear();
  for (hypha::plugin::HyphaBasePlugin *plugin : pluginLoader->getInstances()) {
    if (hypha::plugin::PluginUtil::isSender(plugin))
      ui->senderComboBox->addItem(QString::fromStdString(plugin->getId()));
  }
  for (hypha::plugin::HyphaBasePlugin *plugin : pluginLoader->getInstances()) {
    if (hypha::plugin::PluginUtil::isReceiver(plugin))
      ui->receiverComboBox->addItem(QString::fromStdString(plugin->getId()));
  }

  hypha::controller::Connection con(this->database);
  for (std::tuple<std::string, std::string, std::string> t :
       con.getConnections()) {
    std::string id = std::get<0>(t);
    std::string senderId = std::get<1>(t);
    std::string receiverId = std::get<2>(t);
    QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
    ui->listWidget->addItem(item);
    ConnectionItem *connectionItem = new ConnectionItem(
        QString::fromStdString(id), QString::fromStdString(senderId),
        QString::fromStdString(receiverId), database);
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
  con.create(ui->senderComboBox->currentText().toStdString(),
             ui->receiverComboBox->currentText().toStdString());
  init();
}
