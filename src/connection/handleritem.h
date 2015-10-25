#ifndef HANDLERITEM_H
#define HANDLERITEM_H

#include <QtWidgets/QGraphicsItem>
#include <QtCore/QList>
#include <hypha/handler/hyphahandler.h>

using namespace hypha::handler;

class ConnectionLine;
class ConnectionWindow;

class HandlerItem : public QGraphicsItem {
 public:
  explicit HandlerItem(HyphaHandler *handler, ConnectionWindow *window, QGraphicsItem *parent = 0);

  QRectF boundingRect() const;

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget);

  void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
  void addConnection(ConnectionLine *connection);

 signals:

 public slots:

 protected:
  HyphaHandler *handler;
  ConnectionWindow *wnd;
  QList<ConnectionLine *> connections;

};

#endif // HANDLERITEM_H
