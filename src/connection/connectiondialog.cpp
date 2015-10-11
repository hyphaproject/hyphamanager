#include <QtSql/QSqlQuery>
#include "plugin/pluginloader.h"
#include "handler/handlerloader.h"
#include "database/database.h"
#include "connectiondialog.h"
#include "connectionitem.h"
#include "ui_connectiondialog.h"

ConnectionDialog::ConnectionDialog(hypha::handler::HandlerLoader *handlerLoader, hypha::plugin::PluginLoader *pluginLoader, Database *database, QWidget *parent) :
QDialog(parent),
ui(new Ui::ConnectionDialog)
{
    ui->setupUi(this);
    this->handlerLoader = handlerLoader;
    this->pluginLoader = pluginLoader;
    this->database = database;
    init();
}

ConnectionDialog::~ConnectionDialog()
{
    delete ui;
}

void ConnectionDialog::init()
{
    ui->listWidget->clear();
    ui->handlerComboBox->clear();
    ui->pluginComboBox->clear();
    for(hypha::handler::HyphaHandler * handler: handlerLoader->getInstances()){
        ui->handlerComboBox->addItem(handler->getId());
    }
    for(hypha::plugin::HyphaPlugin * plugin: pluginLoader->getInstances()){
        ui->pluginComboBox->addItem(plugin->getId());
    }

    QString queryString = "SELECT id, handler_id, plugin_id FROM connection;";
    QSqlQuery query = database->getQuery();
    query.exec(queryString);
    while( query.next() ){
        QString id = query.value(0).toString();
        QString handlerId = query.value(1).toString();
        QString pluginId = query.value(2).toString();

        QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
        ui->listWidget->addItem(item);
        ConnectionItem *connectionItem = new ConnectionItem(id, handlerId, pluginId, database);
        item->setSizeHint(connectionItem->minimumSizeHint());
        ui->listWidget->setItemWidget(item, connectionItem);
    }
}

void ConnectionDialog::on_deleteButton_clicked()
{
    ConnectionItem *item = (ConnectionItem*) ui->listWidget->itemWidget(ui->listWidget->currentItem());
    if(item){
        item->deleteFromDatabase();
        init();
    }
}

void ConnectionDialog::on_addButton_clicked()
{
    QSqlQuery query = database->getQuery();
    query.prepare("INSERT INTO connection(handler_id,plugin_id) values(:handler_id,:plugin_id);");
    query.bindValue(":handler_id",ui->handlerComboBox->currentText());
    query.bindValue(":plugin_id", ui->pluginComboBox->currentText());
    query.exec();
    init();
}
