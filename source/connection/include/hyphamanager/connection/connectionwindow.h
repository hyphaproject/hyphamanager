// Copyright (c) 2015-2017 Hypha
#ifndef CONNECTIONWINDOW_H
#define CONNECTIONWINDOW_H

#include <hyphamanager/core/instance.h>
#include "pluginitem.h"

#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QTreeWidgetItem>
#include <QtWidgets/QWidget>

namespace Ui {
class ConnectionWindow;
}

class ConnectionWindow : public QWidget {
  Q_OBJECT

 public:
  explicit ConnectionWindow(Instance *instance, QWidget *parent = 0);
  ~ConnectionWindow();
  void reload();
  void moveTab(QString name);
  void savePositions();
  void saveConfig();
  void updateDesigner();
  void setStatusMessageUrl(QString url);

 private:
  Ui::ConnectionWindow *ui;

 protected:
  void createPluginsTree();
  void createPluginsTabs();
  void updatePluginItems();
  void loadPositions();
  void loadPosition(std::string id, QGraphicsItem *item);

  void savePosition(std::string id, int x, int y);

  void addLines();

  Instance *instance;
  QGraphicsScene *scene;
  QList<QTreeWidgetItem *> pluginsTreeItems;
  QMap<QString, QWidget *> pluginTabs;
  QMap<QString, PluginItem *> pluginItems;

 private slots:
  void on_pluginsTreeWidget_currentItemChanged(QTreeWidgetItem *current,
                                               QTreeWidgetItem *previous);
  void on_connectionsButton_clicked();
  void on_pluginButton_clicked();
  void on_printButton_clicked();
};

#endif  // CONNECTIONWINDOW_H
