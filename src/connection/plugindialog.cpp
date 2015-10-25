#include <QtSql/QSqlQuery>
#include <hypha/plugin/pluginloader.h>
#include "plugindialog.h"
#include "ui_plugindialog.h"

PluginDialog::PluginDialog(hypha::plugin::PluginLoader *pluginLoader, hypha::database::Database *database, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PluginDialog)
{
    ui->setupUi(this);
    this->pluginLoader = pluginLoader;
    this->database = database;
    init();
}

PluginDialog::~PluginDialog()
{
    delete ui;
}

void PluginDialog::init()
{
    ui->comboBox->clear();
    for(hypha::plugin::HyphaPlugin * plugin: pluginLoader->getPlugins()){
        ui->comboBox->addItem(QString::fromStdString(plugin->name()));
    }
}

void PluginDialog::on_buttonBox_accepted()
{
    Poco::Data::Statement statement = database->getStatement();
    statement << "INSERT INTO plugins(id,host,type) values(:id,:host,:type);",
            Poco::Data::use(ui->idEdit->text().toStdString()),
            Poco::Data::use(ui->hostEdit->text().toStdString()),
            Poco::Data::use(ui->comboBox->currentText().toStdString());
    statement.execute();
    pluginLoader->loadAllInstances();
    init();
}
