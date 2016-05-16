#include <QtWidgets/QMessageBox>
#include <Poco/Data/MySQL/MySQLException.h>
#include <hypha/handler/handlerloader.h>
#include <hypha/handler/hyphahandler.h>
#include "handlerdialog.h"
#include "ui_handlerdialog.h"

HandlerDialog::HandlerDialog(hypha::handler::HandlerLoader *handlerLoader, hypha::database::Database *database, QWidget *parent):
    QDialog(parent),
    ui(new Ui::HandlerDialog) {
    ui->setupUi(this);
    this->handlerLoader = handlerLoader;
    this->database = database;
    init();
}

HandlerDialog::~HandlerDialog() {
    delete ui;
}

void HandlerDialog::init() {
    ui->comboBox->clear();
    for (hypha::handler::HyphaHandler *handler : handlerLoader->getHandlers()) {
        ui->comboBox->addItem(QString::fromStdString(handler->name()));
    }
}

void HandlerDialog::on_buttonBox_accepted() {
    try {
        database->getSession() << "INSERT INTO `handler`(`id`,`host`,`type`,`config`) values('"
                               + ui->idEdit->text().toStdString() + "','"
                               + ui->hostEdit->text().toStdString() + "','"
                               + ui->comboBox->currentText().toStdString() + "','');", Poco::Data::Keywords::now;
    } catch (Poco::Exception &e) {
        QMessageBox::critical(0, "", QString::fromStdString(e.message()) );
    }

    handlerLoader->loadAllInstances();
    init();
}
