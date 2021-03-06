// Copyright (c) 2015-2017 Hypha

#include "hyphamanager/connection/pluginitem.h"
#include "hyphamanager/connection/connectionline.h"
#include "hyphamanager/connection/connectionwindow.h"

#include <hypha/controller/connection.h>
#include <hypha/controller/plugin.h>
#include <hypha/plugin/pluginutil.h>

#include <QDebug>
#include <QtGui/QPainter>
#include <QtWidgets/QAction>
#include <QtWidgets/QGraphicsSceneContextMenuEvent>
#include <QtWidgets/QMenu>

static const QPointF points[3] = {QPointF(-10.0, 0.0), QPointF(10.0, 0.0),
                                  QPointF(0.0, 10.0)};

PluginItem::PluginItem(HyphaBasePlugin *plugin, ConnectionWindow *window,
                       Instance *instance, QGraphicsItem *parent)
    : QGraphicsItem(parent) {
  this->plugin = plugin;
  this->wnd = window;
  this->instance = instance;
  setFlag(ItemIsMovable);
  setFlag(ItemIsSelectable);
}

QRectF PluginItem::boundingRect() const {
  qreal penWidth = 1;
  return QRectF(-10 - penWidth / 2, -10 - penWidth / 2, 20 + penWidth,
                20 + penWidth);
}

void PluginItem::paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget) {
  QPen pen = painter->pen();
  pen.setColor(QColor(0, 0, 255));
  pen.setWidth(2);
  painter->setPen(pen);
  if (hypha::plugin::PluginUtil::isHandler(this->plugin))
    painter->drawRoundedRect(-10, -10, 20, 20, 5, 5);
  if (hypha::plugin::PluginUtil::isActor(this->plugin))
    painter->drawConvexPolygon(points, 3);
  if (hypha::plugin::PluginUtil::isSensor(this->plugin))
    painter->drawEllipse(-10, -10, 20, 20);
  pen.setColor(QColor(0, 0, 0));
  pen.setWidth(1);
  painter->setPen(pen);
  painter->drawText(10, 10, QString::fromStdString(plugin->getId()));
}

void PluginItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event) {
  QString editAction("Edit");
  QString deleteAction("Delete");

  QMenu menu;
  menu.addAction(editAction);
  menu.addAction(deleteAction);
  QAction *a = menu.exec(event->screenPos());
  if (a) {
    if (a->text() == editAction) {
      wnd->moveTab(QString::fromStdString(plugin->getId()));
    } else if (a->text() == deleteAction) {
      hypha::controller::Connection con(instance->getDatabase());
      con.removeConnections(plugin->getId());
      hypha::controller::Plugin plug(instance->getDatabase());
      plug.remove(plugin->getId());
      wnd->reload();
    }
  }
}

void PluginItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
  QGraphicsItem::mouseReleaseEvent(event);
  update();
  for (ConnectionLine *line : connections) {
    line->updatePosition();
  }
  wnd->updateDesigner();
}

void PluginItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  QGraphicsItem::mousePressEvent(event);
  QString url = "http://" + QString::fromStdString(plugin->getHost()) +
                ":47965/statusmessage/" +
                QString::fromStdString(plugin->getId());
  wnd->setStatusMessageUrl(url);
}

void PluginItem::addConnection(ConnectionLine *connection) {
  connections.append(connection);
}
