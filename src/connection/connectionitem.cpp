#include <hypha/database/database.h>
#include "connectionitem.h"
#include "ui_connectionitem.h"

ConnectionItem::ConnectionItem(QString id, QString handlerId, QString pluginId, hypha::database::Database *database, QWidget *parent):
    QWidget(parent),
    ui(new Ui::ConnectionItem)
{
    ui->setupUi(this);
    this->id = id;
    this->handlerId = handlerId;
    this->pluginId = pluginId;
    this->database = database;
    init();
}

ConnectionItem::~ConnectionItem()
{
    delete ui;
}

void ConnectionItem::init()
{
    ui->handlerEdit->setText(handlerId);
    ui->pluginEdit->setText(pluginId);
}

void ConnectionItem::deleteFromDatabase()
{
    Poco::Data::Statement statement = database->getStatement();
    statement << "delete from connection where id = ?;",
            Poco::Data::use(id.toStdString());
    statement.execute();
}
