// Copyright (c) 2015-2017 Hypha

#include "connection/connectionline.h"
#include "connection/pluginitem.h"

#include <QtGui/QPen>
#include <QtWidgets/QGraphicsLineItem>

ConnectionLine::ConnectionLine(PluginItem *sender, PluginItem *receiver,
                               QGraphicsItem *parent)
    : QGraphicsLineItem(parent) {
  if (!sender || !receiver) return;
  this->sender = sender;
  this->receiver = receiver;
  setPen(QPen(Qt::green, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
  sender->addConnection(this);
  receiver->addConnection(this);
  updatePosition();
}

void ConnectionLine::updatePosition() {
  QLineF line(mapFromItem(sender, 0, 0), mapFromItem(receiver, 0, 0));
  setLine(line);
}
