#ifndef CONNECTIONWINDOW_H
#define CONNECTIONWINDOW_H

#include <QtWidgets/QWidget>
#include <QtCore/QList>
#include <QtWidgets/QTreeWidgetItem>
#include <QtCore/QMap>
#include <QtWidgets/QGraphicsScene>
#include "../main/instance.h"
#include "../database/database.h"
#include "handleritem.h"
#include "pluginitem.h"


namespace Ui {
class ConnectionWindow;
}

class ConnectionWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ConnectionWindow(Instance *instance, QWidget *parent = 0);
    ~ConnectionWindow();
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
    void createHandlerItems();
    void updatePluginItems();
    void loadPositions();
    void loadPosition(QString id, QGraphicsItem *item);

    void savePosition(QString id, int x, int y);
    void saveHandlerConfig(QString id, QString config);
    void savePluginConfig(QString id, QString config);

    void addLines();

    Instance *instance;
    QGraphicsScene *scene;
    QList<QTreeWidgetItem *> pluginsTreeItems;
    QMap<QString, QWidget*> pluginTabs;
    QMap<QString, HandlerItem*> handlerItems;
    QMap<QString, PluginItem*> pluginItems;

private slots:
    void on_pluginsTreeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
    void on_connectionsButton_clicked();
    void on_handlerButton_clicked();
    void on_pluginButton_clicked();
    void on_printButton_clicked();
};

#endif // CONNECTIONWINDOW_H
