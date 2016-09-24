// Copyright (c) 2015-2016 Hypha
#include "connection/connectionwindow.h"
#include <Poco/Data/RecordSet.h>
#include <hypha/controller/handler.h>
#include <hypha/controller/plugin.h>
#include <hypha/core/database/database.h>
#include <hypha/core/database/userdatabase.h>
#include <hypha/handler/handlerloader.h>
#include <hypha/handler/hyphahandler.h>
#include <hypha/plugin/hyphaplugin.h>
#include <hypha/plugin/pluginloader.h>
#include <QtCore/QDebug>
#include <QtCore/QtAlgorithms>
#include <QtPrintSupport/QPrinter>
#include <QtSql/QSqlError>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include "connection/connectiondialog.h"
#include "connection/connectionline.h"
#include "connection/handlerdialog.h"
#include "connection/plugindialog.h"
#include "hyphamanager/hmhandler/hyphahandlerconfig.h"
#include "hyphamanager/hmplugin/unknownplugin.h"
#include "ui_connectionwindow.h"

using namespace Poco::Data::Keywords;

ConnectionWindow::ConnectionWindow(Instance *instance, QWidget *parent)
    : QWidget(parent), ui(new Ui::ConnectionWindow) {
  this->instance = instance;
  ui->setupUi(this);
  createPluginsTree();
  createPluginsTabs();
  scene = new QGraphicsScene(0, 0, 2048, 2048);
  ui->graphicsView->setScene(scene);
  createHandlerItems();
  updatePluginItems();
  loadPositions();
  addLines();
  updateDesigner();
}

ConnectionWindow::~ConnectionWindow() {
  // savePositions();
  ui->pluginsTreeWidget->clear();
  ui->tabWidget->clear();
  pluginTabs.clear();
  // qDeleteAll(pluginsTreeItems.begin(), pluginsTreeItems.end());
  pluginsTreeItems.clear();
  delete ui;
}

void ConnectionWindow::moveTab(QString name) {
  ui->tabWidget->setCurrentWidget(this->pluginTabs[name]);
  this->pluginTabs[name]->setFocus();
}

void ConnectionWindow::createPluginsTree() {
  QTreeWidgetItem *handlerWidget = new QTreeWidgetItem(ui->pluginsTreeWidget);
  handlerWidget->setText(0, "Handler");
  QTreeWidgetItem *pluginsWidget = new QTreeWidgetItem(ui->pluginsTreeWidget);
  pluginsWidget->setText(0, "Plugins");
  for (hypha::handler::HyphaHandler *handler :
       instance->getHandlerLoader()->getHandlers()) {
    pluginsTreeItems.append(new QTreeWidgetItem(
        handlerWidget, QStringList(QString("%1").arg(
                           QString::fromStdString(handler->name())))));
  }
  for (hypha::plugin::HyphaPlugin *plugin :
       instance->getPluginLoader()->getPlugins()) {
    pluginsTreeItems.append(new QTreeWidgetItem(
        pluginsWidget, QStringList(QString("%1").arg(
                           QString::fromStdString(plugin->name())))));
  }
  ui->pluginsTreeWidget->header()->resizeSection(0, 250);
}

void ConnectionWindow::createPluginsTabs() {
  for (hypha::handler::HyphaHandler *handler :
       instance->getHandlerLoader()->getInstances()) {
    if (handler) {
      this->pluginTabs.insert(
          QString::fromStdString(handler->getId()),
          ((hypha::handler::HyphaHandlerConfig *)handler)->widget());
      ui->tabWidget->addTab(
          ((hypha::handler::HyphaHandlerConfig *)handler)->widget(),
          QString::fromStdString(handler->getId() + " (" + handler->name() +
                                 ")"));
    }
  }
  for (hypha::plugin::HyphaPlugin *plugin :
       instance->getPluginLoader()->getInstances()) {
    if (plugin) {
      this->pluginTabs.insert(
          QString::fromStdString(plugin->getId()),
          ((hypha::plugin::HyphaPluginConfig *)plugin)->widget());
      ui->tabWidget->addTab(
          ((hypha::plugin::HyphaPluginConfig *)plugin)->widget(),
          QString::fromStdString(plugin->getId() + " (" + plugin->name() +
                                 ")"));
    }
  }
}

void ConnectionWindow::createHandlerItems() {
  for (hypha::handler::HyphaHandler *handler :
       instance->getHandlerLoader()->getInstances()) {
    if (handler) {
      HandlerItem *item = new HandlerItem(handler, this);
      this->handlerItems.insert(QString::fromStdString(handler->getId()), item);
      scene->addItem(item);
    }
  }
}

void ConnectionWindow::updatePluginItems() {
  for (hypha::plugin::HyphaPlugin *plugin :
       instance->getPluginLoader()->getInstances()) {
    if (plugin) {
      HandlerItem *item = handlerItems[QString::fromStdString(plugin->getId())];
      if (!item) {
        PluginItem *item = new PluginItem(plugin, this);
        this->pluginItems.insert(QString::fromStdString(plugin->getId()), item);
        scene->addItem(item);
      }
    }
  }
}

void ConnectionWindow::loadPositions() {
  for (QString itemid : handlerItems.keys()) {
    HandlerItem *item = handlerItems[itemid];
    if (item) loadPosition(itemid.toStdString(), item);
  }
  for (QString itemid : pluginItems.keys()) {
    PluginItem *item = pluginItems[itemid];
    if (item) loadPosition(itemid.toStdString(), item);
  }
}

void ConnectionWindow::loadPosition(std::string id, QGraphicsItem *item) {
  Poco::Data::Statement statement = instance->getDatabase()->getStatement();
  statement << "SELECT x,y FROM designerpositions WHERE id = '" + id + "';";
  statement.execute();
  Poco::Data::RecordSet rs(statement);
  bool more = rs.moveFirst();
  while (more) {
    float x = rs[0].convert<float>();
    float y = rs[1].convert<float>();
    item->setX(x);
    item->setY(y);
    return;
    more = rs.moveNext();
  }
}

void ConnectionWindow::savePositions() {
  for (QString itemid : handlerItems.keys()) {
    HandlerItem *item = handlerItems[itemid];
    if (item) savePosition(itemid.toStdString(), item->x(), item->y());
  }
  for (QString itemid : pluginItems.keys()) {
    PluginItem *item = pluginItems[itemid];
    if (item) savePosition(itemid.toStdString(), item->x(), item->y());
  }
}

void ConnectionWindow::saveConfig() {
  hypha::controller::Handler handlerController(instance->getDatabase());
  hypha::controller::Plugin pluginController(instance->getDatabase());
  for (hypha::handler::HyphaHandler *handler :
       instance->getHandlerLoader()->getInstances()) {
    if (handler) {
      handlerController.updateConfig(handler->getId(), handler->getConfig());
    }
  }
  for (hypha::plugin::HyphaPlugin *plugin :
       instance->getPluginLoader()->getInstances()) {
    if (plugin) {
      pluginController.updateConfig(plugin->getId(), plugin->getConfig());
    }
  }
}

void ConnectionWindow::savePosition(std::string id, int x, int y) {
  instance->getDatabase()->getSession()
      << "UPDATE `designerpositions` SET `x`=?, `y`=? WHERE `id`=?",
      use(x), use(y), use(id), now;
}

void ConnectionWindow::addLines() {
  Poco::Data::Statement statement = instance->getDatabase()->getStatement();
  try {
    statement << "SELECT `id`, `handler_id`, `plugin_id` FROM `connection`;";

    statement.execute();
  } catch (Poco::Exception &e) {
    QMessageBox::critical(0, "error", QString::fromStdString(e.what()));
  }

  Poco::Data::RecordSet rs(statement);
  bool more = rs.moveFirst();
  while (more) {
    std::string id = rs[0].convert<std::string>();
    std::string handlerId = rs[1].convert<std::string>();
    std::string pluginId = rs[2].convert<std::string>();
    ConnectionLine *line = new ConnectionLine(
        this->handlerItems[QString::fromStdString(handlerId)],
        this->pluginItems[QString::fromStdString(pluginId)]);
    scene->addItem(line);
    more = rs.moveNext();
  }
}

void ConnectionWindow::updateDesigner() { scene->update(); }

void ConnectionWindow::setStatusMessageUrl(QString url) {
  ui->statusMessageWebView->load(QUrl(url));
}

void ConnectionWindow::on_pluginsTreeWidget_currentItemChanged(
    QTreeWidgetItem *current, QTreeWidgetItem *previous) {
  if (current == nullptr || current->columnCount() < 1) return;
  QString name = current->text(0);
  if (name == "Handler" || name == "Plugins") {
    ui->descriptionBox->setTitle("");
    ui->descriptionLineEdit->setText("");
  } else {
    ui->descriptionBox->setTitle(name);
    hypha::handler::HyphaHandler *handler =
        instance->getHandlerLoader()->getHandler(name.toStdString());
    if (handler) {
      ui->descriptionLineEdit->setText(
          QString::fromStdString(handler->getDescription()));
    }
    hypha::plugin::HyphaPlugin *plugin =
        instance->getPluginLoader()->getPlugin(name.toStdString());
    if (plugin) {
      ui->descriptionLineEdit->setText(
          QString::fromStdString(plugin->getDescription()));
    }
  }
}

void ConnectionWindow::on_connectionsButton_clicked() {
  saveConfig();
  ConnectionDialog dialog(instance->getHandlerLoader(),
                          instance->getPluginLoader(), instance->getDatabase(),
                          this);
  dialog.exec();
  updatePluginItems();
  loadPositions();
  updateDesigner();
}

void ConnectionWindow::on_handlerButton_clicked() {
  saveConfig();
  HandlerDialog dialog(instance->getHandlerLoader(), instance->getDatabase(),
                       this);
  dialog.exec();
  updatePluginItems();
  loadPositions();
  updateDesigner();
}

void ConnectionWindow::on_pluginButton_clicked() {
  saveConfig();
  PluginDialog dialog(instance->getPluginLoader(), instance->getDatabase(),
                      this);
  dialog.exec();
  updatePluginItems();
  loadPositions();
  updateDesigner();
}

void ConnectionWindow::on_printButton_clicked() {
  saveConfig();
  QFileDialog fileDialog(this);
  fileDialog.setNameFilter(tr("Portable Document Format (*.pdf)"));
  QStringList fileNames;
  if (fileDialog.exec()) fileNames = fileDialog.selectedFiles();
  for (QString file : fileNames) {
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
