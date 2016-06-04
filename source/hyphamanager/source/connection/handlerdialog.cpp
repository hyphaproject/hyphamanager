#include <QtWidgets/QMessageBox>
#include <Poco/Data/MySQL/MySQLException.h>
#include <hypha/handler/handlerloader.h>
#include <hypha/handler/hyphahandler.h>
#include <hypha/controller/handler.h>
#include "connection/handlerdialog.h"
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
    hypha::controller::Handler handler(this->database);
    try {
        handler.add(ui->idEdit->text().toStdString(), ui->hostEdit->text().toStdString(), ui->comboBox->currentText().toStdString(), "{}");
    } catch (Poco::Exception &e) {
        QMessageBox::critical(0, "", QString::fromStdString(e.message()) );
    }

    handlerLoader->loadAllInstances();
    init();
}
