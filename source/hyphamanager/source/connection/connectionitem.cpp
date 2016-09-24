// Copyright (c) 2015-2016 Hypha
#include "connection/connectionitem.h"
#include <hypha/controller/connection.h>
#include <hypha/core/database/database.h>
#include "ui_connectionitem.h"

using namespace Poco::Data::Keywords;

ConnectionItem::ConnectionItem(QString id, QString handlerId, QString pluginId,
                               hypha::database::Database *database,
                               QWidget *parent)
    : QWidget(parent), ui(new Ui::ConnectionItem) {
  ui->setupUi(this);
  this->id = id;
  this->handlerId = handlerId;
  this->pluginId = pluginId;
  this->database = database;
  init();
}

ConnectionItem::~ConnectionItem() { delete ui; }

void ConnectionItem::init() {
  ui->handlerEdit->setText(handlerId);
  ui->pluginEdit->setText(pluginId);
}

void ConnectionItem::deleteFromDatabase() {
  hypha::controller::Connection con(this->database);
  con.remove(id.toStdString());
}
