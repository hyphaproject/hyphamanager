#ifndef CONNECTIONLINE_H
#define CONNECTIONLINE_H

#include <QtWidgets/QGraphicsLineItem>

class HandlerItem;
class PluginItem;

class ConnectionLine : public QGraphicsLineItem {
 public:
  explicit ConnectionLine(HandlerItem *handler, PluginItem *plugin, QGraphicsItem *parent = 0);
  void updatePosition();
 signals:

 public slots:

 protected:
  HandlerItem *handler;
  PluginItem *plugin;

};

#endif // CONNECTIONLINE_H
