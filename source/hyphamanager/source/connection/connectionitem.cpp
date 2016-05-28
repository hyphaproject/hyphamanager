#include <hypha/core/database/database.h>
#include "connection/connectionitem.h"
#include "ui_connectionitem.h"

using namespace Poco::Data::Keywords;

ConnectionItem::ConnectionItem(QString id, QString handlerId, QString pluginId, hypha::database::Database *database, QWidget *parent):
    QWidget(parent),
    ui(new Ui::ConnectionItem) {
    ui->setupUi(this);
    this->id = id;
    this->handlerId = handlerId;
    this->pluginId = pluginId;
    this->database = database;
    init();
}

ConnectionItem::~ConnectionItem() {
    delete ui;
}

void ConnectionItem::init() {
    ui->handlerEdit->setText(handlerId);
    ui->pluginEdit->setText(pluginId);
}

void ConnectionItem::deleteFromDatabase() {
    std::string idStr = id.toStdString();
    Poco::Data::Statement statement = database->getStatement();
    statement << "delete from connection where id = ?;",
              use(idStr);
    statement.execute();
}
