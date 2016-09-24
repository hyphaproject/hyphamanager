#include "connection/connectionline.h"
#include <QtGui/QPen>
#include <QtWidgets/QGraphicsLineItem>
#include "connection/handleritem.h"
#include "connection/pluginitem.h"

ConnectionLine::ConnectionLine(HandlerItem *handler, PluginItem *plugin,
                               QGraphicsItem *parent)
    : QGraphicsLineItem(parent) {
  if (!handler || !plugin) return;
  this->handler = handler;
  this->plugin = plugin;
  setPen(QPen(Qt::green, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
  handler->addConnection(this);
  plugin->addConnection(this);
  updatePosition();
}

void ConnectionLine::updatePosition() {
  QLineF line(mapFromItem(handler, 0, 0), mapFromItem(plugin, 0, 0));
  setLine(line);
}
