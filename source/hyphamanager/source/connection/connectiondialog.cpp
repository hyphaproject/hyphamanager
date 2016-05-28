#include <Poco/Data/RecordSet.h>
#include <hypha/plugin/pluginloader.h>
#include <hypha/handler/handlerloader.h>
#include <hypha/core/database/database.h>
#include "connection/connectiondialog.h"
#include "connection/connectionitem.h"
#include "ui_connectiondialog.h"

ConnectionDialog::ConnectionDialog(hypha::handler::HandlerLoader *handlerLoader, hypha::plugin::PluginLoader *pluginLoader, hypha::database::Database *database, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionDialog) {
    ui->setupUi(this);
    this->handlerLoader = handlerLoader;
    this->pluginLoader = pluginLoader;
    this->database = database;
    init();
}

ConnectionDialog::~ConnectionDialog() {
    delete ui;
}

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

    Poco::Data::Statement statement = database->getStatement();
    statement << "SELECT `id`, `handler_id`, `plugin_id` FROM `connection`;";
    statement.execute();
    Poco::Data::RecordSet rs(statement);
    bool more = rs.moveFirst();
    while (more) {
        std::string id = rs[0].convert<std::string>();
        std::string handlerId = rs[1].convert<std::string>();
        std::string pluginId = rs[2].convert<std::string>();

        QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
        ui->listWidget->addItem(item);
        ConnectionItem *connectionItem = new ConnectionItem(
            QString::fromStdString(id),
            QString::fromStdString(handlerId),
            QString::fromStdString(pluginId), database);
        item->setSizeHint(connectionItem->minimumSizeHint());
        ui->listWidget->setItemWidget(item, connectionItem);

        more = rs.moveNext();
    }
}

void ConnectionDialog::on_deleteButton_clicked() {
    ConnectionItem *item = (ConnectionItem *) ui->listWidget->itemWidget(ui->listWidget->currentItem());
    if (item) {
        item->deleteFromDatabase();
        init();
    }
}

void ConnectionDialog::on_addButton_clicked() {
    database->getSession() << "INSERT INTO `connection`(`handler_id`,`plugin_id`) VALUES('"
                           + ui->handlerComboBox->currentText().toStdString() + "','"
                           + ui->pluginComboBox->currentText().toStdString() + "');", Poco::Data::Keywords::now;
    init();
}
