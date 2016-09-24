#include "connection/pluginitem.h"
#include <QDebug>
#include <QtGui/QPainter>
#include <QtWidgets/QAction>
#include <QtWidgets/QGraphicsSceneContextMenuEvent>
#include <QtWidgets/QMenu>
#include "connection/connectionline.h"
#include "connection/connectionwindow.h"

PluginItem::PluginItem(HyphaPlugin *plugin, ConnectionWindow *window,
                       QGraphicsItem *parent)
    : QGraphicsItem(parent) {
  this->plugin = plugin;
  this->wnd = window;
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
  painter->drawRoundedRect(-10, -10, 20, 20, 5, 5);
  pen.setColor(QColor(0, 0, 0));
  pen.setWidth(1);
  painter->setPen(pen);
  painter->drawText(10, 10, QString::fromStdString(plugin->getId()));
}

void PluginItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event) {
  QMenu menu;
  menu.addAction("Edit");
  QAction *a = menu.exec(event->screenPos());
  if (a) {
    wnd->moveTab(QString::fromStdString(plugin->getId()));
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
