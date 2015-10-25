#include <QtGui/QPainter>
#include <QtWidgets/QMenu>
#include <QtWidgets/QAction>
#include <QtWidgets/QGraphicsSceneContextMenuEvent>
#include "connectionwindow.h"
#include "connectionline.h"
#include "handleritem.h"

HandlerItem::HandlerItem(HyphaHandler *handler, ConnectionWindow *window, QGraphicsItem *parent) :
    QGraphicsItem(parent) {
    this->handler = handler;
    this->wnd = window;
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
}

QRectF HandlerItem::boundingRect() const {
    qreal penWidth = 1;
    return QRectF(-10 - penWidth / 2, -10 - penWidth / 2,
                  20 + penWidth, 20 + penWidth);
}

void HandlerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QPen pen = painter->pen();
    pen.setColor(QColor(255,0,0));
    pen.setWidth(2);
    painter->setPen(pen);
    painter->drawRoundedRect(-10, -10, 20, 20, 5, 5);
    pen.setColor(QColor(0,0,0));
    pen.setWidth(1);
    painter->setPen(pen);
    painter->drawText(10,10, QString::fromStdString(handler->getId()));
}

void HandlerItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event) {
    QMenu menu;
    menu.addAction("Edit");
    QAction *a = menu.exec(event->screenPos());
    if(a) {
        wnd->moveTab(QString::fromStdString(handler->getId()));
    }
}

void HandlerItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem::mouseReleaseEvent(event);
    update();
    for(ConnectionLine *line: connections) {
        line->updatePosition();
    }
    wnd->updateDesigner();
}

void HandlerItem::addConnection(ConnectionLine *connection) {
    connections.append(connection);
}
