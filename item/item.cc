#include "item/item.h"
#include <QGraphicsItem>
#include <QPainter>

item::item(QGraphicsItem *parent) : QGraphicsObject (parent)
{
    setFlags (ItemIsSelectable | ItemIsMovable);
}

void item::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    painter->setPen(Qt::black);
}

QRectF item::boundingRect() const
{
    return {0, 0, item_width_, item_height_};
}


