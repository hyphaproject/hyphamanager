#include <QtCore/QtAlgorithms>
#include <QtCore/QDebug>
#include <QtSql/QSqlError>
#include <QtWidgets/QFileDialog>
#include <QtPrintSupport/QPrinter>

#include "connectionwindow.h"
#include "ui_connectionwindow.h"
#include "../handler/handlerloader.h"
#include "../handler/hyphahandler.h"
#include "../plugin/pluginloader.h"
#include "../plugin/hyphaplugin.h"
#include "connectiondialog.h"
#include "handlerdialog.h"
#include "plugindialog.h"
#include "connectionline.h"

ConnectionWindow::ConnectionWindow(Instance *instance, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConnectionWindow)
{
    this->instance = instance;
    ui->setupUi(this);
    createPluginsTree();
    createPluginsTabs();
    scene = new QGraphicsScene(0,0,2048,2048);
    ui->graphicsView->setScene(scene);
    createHandlerItems();
    updatePluginItems();
    loadPositions();
    addLines();
    updateDesigner();
}

ConnectionWindow::~ConnectionWindow()
{
    //savePositions();
    ui->pluginsTreeWidget->clear();
    ui->tabWidget->clear();
    pluginTabs.clear();
    //qDeleteAll(pluginsTreeItems.begin(), pluginsTreeItems.end());
    pluginsTreeItems.clear();
    delete ui;
}

void ConnectionWindow::moveTab(QString name)
{
    ui->tabWidget->setCurrentWidget(this->pluginTabs[name]);
    this->pluginTabs[name]->setFocus();
}

void ConnectionWindow::createPluginsTree()
{
    QTreeWidgetItem *handlerWidget = new QTreeWidgetItem(ui->pluginsTreeWidget);
    handlerWidget->setText(0, "Handler");
    QTreeWidgetItem *pluginsWidget = new QTreeWidgetItem(ui->pluginsTreeWidget);
    pluginsWidget->setText(0, "Plugins");
    foreach(hypha::handler::HyphaHandler * handler, instance->getHandlerLoader()->getHandlers())
    {
        pluginsTreeItems.append(new QTreeWidgetItem(handlerWidget, QStringList(QString("%1").arg(handler->getName()))));
    }
    foreach(hypha::plugin::HyphaPlugin * plugin, instance->getPluginLoader()->getPlugins())
    {
        pluginsTreeItems.append(new QTreeWidgetItem(pluginsWidget, QStringList(QString("%1").arg(plugin->getName()))));
    }
    ui->pluginsTreeWidget->header()->resizeSection(0,250);
}

void ConnectionWindow::createPluginsTabs()
{
    foreach(hypha::handler::HyphaHandler *handler, instance->getHandlerLoader()->getInstances()){
        if(handler){
            this->pluginTabs.insert(handler->getId(), handler->widget());
            ui->tabWidget->addTab(handler->widget(), handler->getId() + " ("+handler->getName()+")");
        }
    }
    foreach(hypha::plugin::HyphaPlugin *plugin, instance->getPluginLoader()->getInstances()){
        if(plugin){
            this->pluginTabs.insert(plugin->getId(), plugin->widget());
            ui->tabWidget->addTab(plugin->widget(), plugin->getId() + " ("+plugin->getName()+")");
        }
    }
}

void ConnectionWindow::createHandlerItems()
{
    foreach(hypha::handler::HyphaHandler *handler, instance->getHandlerLoader()->getInstances()){
        if(handler){
            HandlerItem *item = new HandlerItem(handler, this);
            this->handlerItems.insert(handler->getId(), item);
            scene->addItem(item);
        }
    }
}

void ConnectionWindow::updatePluginItems()
{
    foreach(hypha::plugin::HyphaPlugin *plugin, instance->getPluginLoader()->getInstances()){
        if(plugin){
            HandlerItem *item = handlerItems[plugin->getId()];
            if(!item){
                PluginItem *item = new PluginItem(plugin, this);
                this->pluginItems.insert(plugin->getId(), item);
                scene->addItem(item);
            }
        }
    }
}

void ConnectionWindow::loadPositions()
{
    foreach(QString itemid, handlerItems.keys()){
        HandlerItem *item = handlerItems[itemid];
        if(item)
            loadPosition(itemid, item);
    }
    foreach(QString itemid, pluginItems.keys()){
        PluginItem *item = pluginItems[itemid];
        if(item)
            loadPosition(itemid, item);
    }
}

void ConnectionWindow::loadPosition(QString id, QGraphicsItem *item)
{
    QSqlQuery query = instance->getDatabase()->getQuery();
    query.exec("select x,y from designerpositions where id = '" + id + "'");
    while( query.next() ){
        item->setX(query.value(0).toReal());
        item->setY(query.value(1).toReal());
        return;
    }
    query.prepare("insert into designerpositions(id,x,y) values(:id, 0, 0);");
    query.bindValue(":id", id);
    query.exec();
}

void ConnectionWindow::savePositions()
{
    foreach(QString itemid, handlerItems.keys()){
        HandlerItem *item = handlerItems[itemid];
        if(item)
            savePosition(itemid, item->x(), item->y());
    }
    foreach(QString itemid, pluginItems.keys()){
        PluginItem *item = pluginItems[itemid];
        if(item)
            savePosition(itemid, item->x(), item->y());
    }
}

void ConnectionWindow::saveConfig()
{
    foreach(hypha::handler::HyphaHandler *handler, instance->getHandlerLoader()->getInstances()){
        if(handler){
            saveHandlerConfig(handler->getId(), handler->getConfig());
        }
    }
    foreach(hypha::plugin::HyphaPlugin *plugin, instance->getPluginLoader()->getInstances()){
        if(plugin){
            savePluginConfig(plugin->getId(), plugin->getConfig());
        }
    }
}

void ConnectionWindow::savePosition(QString id, int x, int y)
{
    QSqlQuery query = instance->getDatabase()->getQuery();
    query.prepare("update designerpositions set x=:x, y=:y where id=:id");
    query.bindValue(":id",id);
    query.bindValue(":x",x);
    query.bindValue(":y",y);
    query.exec();
}

void ConnectionWindow::saveHandlerConfig(QString id, QString config)
{
    QSqlQuery query = instance->getDatabase()->getQuery();
    query.prepare("update handler set config=:config where id=:id");
    query.bindValue(":id",id);
    query.bindValue(":config",config);
    query.exec();
}

void ConnectionWindow::savePluginConfig(QString id, QString config)
{
    QSqlQuery query = instance->getDatabase()->getQuery();
    query.prepare("update plugins set config=:config where id=:id");
    query.bindValue(":id",id);
    query.bindValue(":config",config);
    query.exec();
}

void ConnectionWindow::addLines()
{
    QString queryString = "SELECT id, handler_id, plugin_id FROM connection;";
    QSqlQuery query = instance->getDatabase()->getQuery();
    query.exec(queryString);
    while( query.next() ){
        QString id = query.value(0).toString();
        QString handlerId = query.value(1).toString();
        QString pluginId = query.value(2).toString();
        ConnectionLine * line = new ConnectionLine(this->handlerItems[handlerId], this->pluginItems[pluginId]);
        scene->addItem(line);
    }
}

void ConnectionWindow::updateDesigner()
{
    scene->update();
}

void ConnectionWindow::setStatusMessageUrl(QString url)
{
    ui->statusMessageWebView->load(QUrl(url));
}

void ConnectionWindow::on_pluginsTreeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    QString name = current->text(0);
    if(name == "Handler" || name == "Plugins"){
        ui->descriptionBox->setTitle("");
        ui->descriptionLineEdit->setText("");
    }else{
        ui->descriptionBox->setTitle(name);
        hypha::handler::HyphaHandler * handler = instance->getHandlerLoader()->getHandler(name);
        if(handler){
            ui->descriptionLineEdit->setText(handler->getDescription());
        }
        hypha::plugin::HyphaPlugin * plugin = instance->getPluginLoader()->getPlugin(name);
        if(plugin){
            ui->descriptionLineEdit->setText(plugin->getDescription());
        }
    }
}

void ConnectionWindow::on_connectionsButton_clicked()
{
    saveConfig();
    ConnectionDialog dialog(instance->getHandlerLoader(), instance->getPluginLoader(), instance->getDatabase(), this);
    dialog.exec();
    updatePluginItems();
    loadPositions();
    updateDesigner();
}

void ConnectionWindow::on_handlerButton_clicked()
{
    saveConfig();
    HandlerDialog dialog(instance->getHandlerLoader(), instance->getDatabase(), this);
    dialog.exec();
    updatePluginItems();
    loadPositions();
    updateDesigner();
}

void ConnectionWindow::on_pluginButton_clicked()
{
    saveConfig();
    PluginDialog dialog(instance->getPluginLoader(), instance->getDatabase(), this);
    dialog.exec();
    updatePluginItems();
    loadPositions();
    updateDesigner();
}

void ConnectionWindow::on_printButton_clicked()
{
    saveConfig();
    QFileDialog fileDialog(this);
    fileDialog.setNameFilter(tr("Portable Document Format (*.pdf)"));
    QStringList fileNames;
    if (fileDialog.exec())
        fileNames = fileDialog.selectedFiles();
    foreach(QString file, fileNames){
        QApplication::setOverrideCursor(Qt::WaitCursor);
        QPrinter printer(QPrinter::HighResolution);
        printer.setPaperSize(QPrinter::A4);
        printer.setOrientation(QPrinter::Portrait);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(file);
        QPainter painter(&printer);
        QFont font = painter.font();
        font.setPixelSize(20);
        painter.setFont(font);
        scene->render(&painter);
        painter.end();
        QApplication::restoreOverrideCursor();
    }
}
