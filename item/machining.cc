#include "machining.h"

unique_ptr<machining> machining::make(QPointF pos, QColor color)
{
    unique_ptr <machining> ret(new machining);
    ret->setPos(pos);

    return ret;
}

machining::machining(item *parent)
    :item(parent)
{

}

void machining::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    item::paint(painter, option, widget);


}

void machining::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

}
