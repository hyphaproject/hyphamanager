// Copyright (c) 2015-2016 Hypha
#ifndef PLUGINITEM_H
#define PLUGINITEM_H

#include <QtCore/QList>
#include <QtWidgets/QGraphicsItem>
#include "hyphamanager/hmplugin/hyphapluginconfig.h"

using namespace hypha::plugin;

class ConnectionWindow;
class ConnectionLine;

class PluginItem : public QGraphicsItem {
 public:
  explicit PluginItem(HyphaPlugin *plugin, ConnectionWindow *window,
                      QGraphicsItem *parent = 0);

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
  HyphaPlugin *plugin;
  ConnectionWindow *wnd;
  QList<ConnectionLine *> connections;
};

#endif  // PLUGINITEM_H
