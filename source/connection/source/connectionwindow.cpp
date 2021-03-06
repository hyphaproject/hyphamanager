// Copyright (c) 2015-2017 Hypha

#include "hyphamanager/connection/connectionwindow.h"
#include "hyphamanager/connection/connectiondialog.h"
#include "hyphamanager/connection/connectionline.h"
#include "hyphamanager/connection/plugindialog.h"
#include "hyphamanager/plugin/autopluginwidget.h"
#include "hyphamanager/plugin/unknownpluginwidget.h"
#include "ui_connectionwindow.h"

#include <hypha/controller/plugin.h>
#include <hypha/core/database/database.h>
#include <hypha/core/database/userdatabase.h>
#include <hypha/plugin/hyphabaseplugin.h>
#include <hypha/plugin/pluginloader.h>
#include <hypha/plugin/pluginutil.h>

#include <Poco/Data/RecordSet.h>
#include <QtCore/QDebug>
#include <QtCore/QtAlgorithms>
#include <QtPrintSupport/QPrinter>
#include <QtSql/QSqlError>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>

using namespace Poco::Data::Keywords;

ConnectionWindow::ConnectionWindow(Instance *instance, QWidget *parent)
    : QWidget(parent), ui(new Ui::ConnectionWindow) {
  this->instance = instance;
  ui->setupUi(this);
  scene = new QGraphicsScene(0, 0, 2048, 2048);
  ui->graphicsView->setScene(scene);
  reload();
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

void ConnectionWindow::reload() {
  ui->pluginsTreeWidget->clear();
  pluginTabs.clear();
  pluginsTreeItems.clear();
  pluginItems.clear();

  scene->clear();
  ui->graphicsView->setScene(scene);

  while (ui->tabWidget->count() > 1) {
    ui->tabWidget->removeTab(1);
  }

  createPluginsTree();
  createPluginsTabs();
  updatePluginItems();
  loadPositions();
  addLines();
  updateDesigner();
}

void ConnectionWindow::moveTab(QString name) {
  ui->tabWidget->setCurrentWidget(this->pluginTabs[name]);
  if (this->pluginTabs[name]) this->pluginTabs[name]->setFocus();
}

void ConnectionWindow::createPluginsTree() {
  QTreeWidgetItem *pluginsWidget = new QTreeWidgetItem(ui->pluginsTreeWidget);
  pluginsWidget->setText(0, "Plugins");
  QTreeWidgetItem *handlerWidget = new QTreeWidgetItem(ui->pluginsTreeWidget);
  handlerWidget->setText(0, "Handler");
  QTreeWidgetItem *actorsWidget = new QTreeWidgetItem(ui->pluginsTreeWidget);
  actorsWidget->setText(0, "Actors");
  QTreeWidgetItem *sensorsWidget = new QTreeWidgetItem(ui->pluginsTreeWidget);
  sensorsWidget->setText(0, "Sensors");

  for (hypha::plugin::HyphaBasePlugin *plugin :
       instance->getPluginLoader()->getPlugins()) {
    pluginsTreeItems.append(new QTreeWidgetItem(
        handlerWidget, QStringList(QString("%1").arg(
                           QString::fromStdString(plugin->name())))));
  }
  for (hypha::plugin::HyphaBasePlugin *plugin :
       instance->getPluginLoader()->getPlugins()) {
    pluginsTreeItems.append(new QTreeWidgetItem(
        pluginsWidget, QStringList(QString("%1").arg(
                           QString::fromStdString(plugin->name())))));
    if (hypha::plugin::PluginUtil::isHandler(plugin))
      pluginsTreeItems.append(new QTreeWidgetItem(
          handlerWidget, QStringList(QString("%1").arg(
                             QString::fromStdString(plugin->name())))));
    if (hypha::plugin::PluginUtil::isActor(plugin))
      pluginsTreeItems.append(new QTreeWidgetItem(
          actorsWidget, QStringList(QString("%1").arg(
                            QString::fromStdString(plugin->name())))));
    if (hypha::plugin::PluginUtil::isSensor(plugin))
      pluginsTreeItems.append(new QTreeWidgetItem(
          sensorsWidget, QStringList(QString("%1").arg(
                             QString::fromStdString(plugin->name())))));
  }
  ui->pluginsTreeWidget->header()->resizeSection(0, 250);
}

void ConnectionWindow::createPluginsTabs() {
  while (ui->tabWidget->count() > 1) {
    ui->tabWidget->removeTab(1);
  }
  for (std::string pluginId :
       instance->getPluginSettings()->getAllPluginIds()) {
    hypha::plugin::HyphaBasePlugin *plugin =
        instance->getPluginLoader()->getPluginInstance(pluginId);
    if (!plugin) {  // Add unknown plugin
      std::string pluginName = instance->getPluginSettings()->getName(pluginId);
      UnknownPluginWidget *widget = new UnknownPluginWidget(pluginId, this);
      this->pluginTabs.insert(QString::fromStdString(pluginId), widget);
      ui->tabWidget->addTab(
          widget, QString::fromStdString(pluginId + " (" + pluginName + ")"));
    } else if (plugin) {  // Add known auto plugin
      AutoPluginWidget *widget = new AutoPluginWidget(plugin, instance, this);
      this->pluginTabs.insert(QString::fromStdString(plugin->getId()), widget);
      ui->tabWidget->addTab(widget,
                            QString::fromStdString(plugin->getId() + " (" +
                                                   plugin->name() + ")"));
    }
  }
}

void ConnectionWindow::updatePluginItems() {
  instance->getPluginLoader()->reloadAllInstances();
  for (hypha::plugin::HyphaBasePlugin *plugin :
       instance->getPluginLoader()->getInstances()) {
    if (plugin) {
      PluginItem *item = pluginItems[QString::fromStdString(plugin->getId())];
      if (!item) {
        item = new PluginItem(plugin, this, instance);
        this->pluginItems.insert(QString::fromStdString(plugin->getId()), item);
        scene->addItem(item);
      }
    }
  }
}

void ConnectionWindow::loadPositions() {
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
  for (QString itemid : pluginItems.keys()) {
    PluginItem *item = pluginItems[itemid];
    if (item) savePosition(itemid.toStdString(), item->x(), item->y());
  }
}

void ConnectionWindow::saveConfig() {
  hypha::controller::Plugin pluginController(instance->getDatabase());

  for (hypha::plugin::HyphaBasePlugin *plugin :
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
    statement << "SELECT `id`, `sender_id`, `receiver_id` FROM `connection`;";

    statement.execute();
  } catch (Poco::Exception &e) {
    QMessageBox::critical(0, "error", QString::fromStdString(e.what()));
  }

  Poco::Data::RecordSet rs(statement);
  bool more = rs.moveFirst();
  while (more) {
    std::string id = rs[0].convert<std::string>();
    std::string senderId = rs[1].convert<std::string>();
    std::string receiverId = rs[2].convert<std::string>();
    ConnectionLine *line = new ConnectionLine(
        this->pluginItems[QString::fromStdString(senderId)],
        this->pluginItems[QString::fromStdString(receiverId)]);
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
  if (name == "Plugins" || name == "Handler" || name == "Actors" ||
      name == "Sensors") {
    ui->descriptionBox->setTitle("");
    ui->descriptionLineEdit->setText("");
  } else {
    ui->descriptionBox->setTitle(name);
    hypha::plugin::HyphaBasePlugin *plugin =
        instance->getPluginLoader()->getPlugin(name.toStdString());
    if (plugin) {
      ui->descriptionLineEdit->setText(
          QString::fromStdString(plugin->getDescription()));
    }
  }
}

void ConnectionWindow::on_connectionsButton_clicked() {
  saveConfig();
  ConnectionDialog dialog(instance->getPluginLoader(), instance->getDatabase(),
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
  createPluginsTabs();
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
