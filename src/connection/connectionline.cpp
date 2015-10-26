#include <QtWidgets/QGraphicsLineItem>
#include <QtGui/QPen>
#include "handleritem.h"
#include "pluginitem.h"
#include "connectionline.h"

ConnectionLine::ConnectionLine(HandlerItem *handler, PluginItem *plugin, QGraphicsItem *parent) :
    QGraphicsLineItem(parent) {
    if (!handler || !plugin)
        return;
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
