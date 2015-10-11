#include <QtSql/QSqlQuery>
#include "plugin/pluginloader.h"
#include "plugindialog.h"
#include "ui_plugindialog.h"

PluginDialog::PluginDialog(hypha::plugin::PluginLoader *pluginLoader, Database *database, QWidget *parent) :
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
        ui->comboBox->addItem(plugin->getName());
    }
}

void PluginDialog::on_buttonBox_accepted()
{
    QSqlQuery query = database->getQuery();
    query.prepare("INSERT INTO plugins(id,host,type) values(:id,:host,:type);");
    query.bindValue(":id",ui->idEdit->text());
    query.bindValue(":host", ui->hostEdit->text());
    query.bindValue(":type", ui->comboBox->currentText());
    query.exec();
    pluginLoader->loadInstances();
    init();
}
