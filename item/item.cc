#include "item/item.h"
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>

item::item(QGraphicsItem *parent) : QGraphicsObject (parent)
{
    setFlags (ItemIsSelectable | ItemIsMovable);
}

QMap<QString, QString> item::return_attriute()
{
    return attribute_map;
}

//void item::make_attribute()
//{
//   auto map = finish_->return_attribute_map();
//}
void item::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);
    painter->setPen(Qt::black);
}

void item::set_attribute(QString key, QString value)
{
    auto& attribute = attribute_map;
    attribute.insert(key,value);
}

QRectF item::boundingRect() const
{
    return {0, 0, item_width_, item_height_};
}


