#include "handler/handlerloader.h"
#include "handler/hyphahandler.h"
#include "handlerdialog.h"
#include "ui_handlerdialog.h"

HandlerDialog::HandlerDialog(hypha::handler::HandlerLoader *handlerLoader, Database *database, QWidget *parent):
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
        ui->comboBox->addItem(handler->getName());
    }
}

void HandlerDialog::on_buttonBox_accepted()
{
    QSqlQuery query = database->getQuery();
    query.prepare("INSERT INTO handler(id,host,type) values(:id,:host,:type);");
    query.bindValue(":id",ui->idEdit->text());
    query.bindValue(":host", ui->hostEdit->text());
    query.bindValue(":type", ui->comboBox->currentText());
    query.exec();
    handlerLoader->loadInstances();
    init();
}
