#include "connectionitem.h"
#include "database/database.h"
#include "ui_connectionitem.h"

ConnectionItem::ConnectionItem(QString id, QString handlerId, QString pluginId, Database *database, QWidget *parent):
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
    QSqlQuery query = database->getQuery();
    query.prepare("delete from connection where id = :id;");
    query.bindValue(":id", this->id);query.bindValue(":id", this->id);
    query.exec();
}
