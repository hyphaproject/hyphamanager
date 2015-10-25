#include <hypha/handler/handlerloader.h>
#include <hypha/handler/hyphahandler.h>
#include "handlerdialog.h"
#include "ui_handlerdialog.h"

HandlerDialog::HandlerDialog(hypha::handler::HandlerLoader *handlerLoader, hypha::database::Database *database, QWidget *parent):
QDialog(parent),
ui(new Ui::HandlerDialog)
{
    ui->setupUi(this);
    this->handlerLoader = handlerLoader;
    this->database = database;
    init();
}

HandlerDialog::~HandlerDialog()
{
    delete ui;
}

void HandlerDialog::init()
{
    ui->comboBox->clear();
    for(hypha::handler::HyphaHandler * handler: handlerLoader->getHandlers()){
        ui->comboBox->addItem(QString::fromStdString(handler->name()));
    }
}

void HandlerDialog::on_buttonBox_accepted()
{
    Poco::Data::Statement statement = database->getStatement();
    statement << "INSERT INTO handler(id,host,type) values(?,?,?);",
            Poco::Data::use(ui->idEdit->text().toStdString()),
            Poco::Data::use(ui->hostEdit->text().toStdString()),
            Poco::Data::use(ui->comboBox->currentText().toStdString());
    statement.execute();
    handlerLoader->loadAllInstances();
    init();
}
