// Copyright (c) 2015-2017 Hypha
#ifndef PLUGINITEM_H
#define PLUGINITEM_H

#include <hyphamanager/core/instance.h>

#include <hypha/plugin/hyphabaseplugin.h>

#include <QAction>
#include <QtCore/QList>
#include <QtWidgets/QGraphicsItem>

using namespace hypha::plugin;

class ConnectionWindow;
class ConnectionLine;

class PluginItem : public QGraphicsItem {
 public:
  explicit PluginItem(HyphaBasePlugin *plugin, ConnectionWindow *window,
                      Instance *instance, QGraphicsItem *parent = 0);

  QRectF boundingRect() const;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget);
  void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
  void addConnection(ConnectionLine *connection);
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
  void mousePressEvent(QGraphicsSceneMouseEvent *event);
 signals:

 public slots:

 protected:
  HyphaBasePlugin *plugin;
  ConnectionWindow *wnd;
  Instance *instance;
  QList<ConnectionLine *> connections;
};

#endif  // PLUGINITEM_H
