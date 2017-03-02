#include "item/item.h"
#include <QGraphicsItem>
#include <QPainter>

//struct impl_item
//{

//};

item::item(QGraphicsItem *parent) : QGraphicsObject (parent)
{
//    imp = make_unique<impl_item> ();

    setFlags (ItemIsSelectable | ItemIsMovable);
}

void item::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    painter->setPen(Qt::black);
}

QRectF item::boundingRect() const
{
    return {0, 0, item_width, item_height};
//    return {};
}

QPainterPath item::shape() const
{
    return {};
}
