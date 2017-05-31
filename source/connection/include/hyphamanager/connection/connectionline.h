// Copyright (c) 2015-2016 Hypha
#ifndef CONNECTIONLINE_H
#define CONNECTIONLINE_H

#include <QtWidgets/QGraphicsLineItem>

class PluginItem;

class ConnectionLine : public QGraphicsLineItem {
 public:
  explicit ConnectionLine(PluginItem *sender, PluginItem *receiver,
                          QGraphicsItem *parent = 0);
  void updatePosition();
 signals:

 public slots:

 protected:
  PluginItem *sender;
  PluginItem *receiver;
};

#endif  // CONNECTIONLINE_H
