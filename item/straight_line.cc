#include "straight_line.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>

unique_ptr<straight_line> straight_line::make(QPointF begin, QPointF end)
{
    auto ret = unique_ptr<straight_line>(new straight_line(begin, end));

    if (ret == nullptr or !ret->init())
    {
        return nullptr;
    }

    return ret;
}

void straight_line::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    item::paint(painter, option, widget);

    const QColor color = option->state bitand QStyle::State_Selected ? selected_color() : Qt::black;
    auto the_pen = painter->pen();
    the_pen.setColor(color);
    painter->setPen(the_pen);

    painter->drawLine(begin_, end_);

}

QRectF straight_line::boundingRect() const
{
    QPointF offset(0, 1);
    auto rect = QRectF(begin_ - offset, end_ + offset);
    return rect;
}

QPainterPath straight_line::shape() const
{
    QPainterPath path;
    QPointF offset(0, 1);
    path.addRect(QRectF(begin_ - offset, end_ + offset));
    QPainter painter;
    painter.drawRect(QRectF(begin_ - offset, end_ + offset));

    return path;
}

straight_line::straight_line(QPointF begin, QPointF end)
{
    begin_ = begin;
    end_ = end;
}

bool straight_line::init()
{
    return true;
}
