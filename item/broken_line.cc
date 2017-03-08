﻿#include "broken_line.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
///连线2
std::unique_ptr<broken_line> broken_line::make(QVector<QPointF> points)
{
    auto ret = std::unique_ptr<broken_line> (new broken_line (points));
    if (ret == nullptr or !ret->init())
    {
        return nullptr;
    }

    return ret;
}

QRectF broken_line::boundingRect() const
{
    const auto x_min = std::min (points_.constFirst().x(), points_.constLast().x());
    const auto y_min = std::min (points_.constFirst().y(), points_.constLast().y());
    const auto x_max = std::max (points_.constFirst().x(), points_.constLast().x());
    const auto y_max = std::max (points_.constFirst().y(), points_.constLast().y());
    const QPointF left_top (x_min, y_min);
    const QPointF bottom_right (x_max, y_max);
    return QRectF(left_top, bottom_right);
}

void broken_line::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    item::paint(painter, option, widget);

    auto the_pen = painter->pen();
    the_pen.setWidthF(0.01 * item_width_);
    painter->setPen(the_pen);

    painter->drawPolyline(return_points());

    if (option->state & QStyle::State_Selected)
    {
        the_pen.setBrush(Qt::transparent);
        the_pen.setStyle(Qt::DashLine);
        painter->setPen(the_pen);
        painter->drawRect(boundingRect());
    }


}

QVector<QPointF> broken_line::return_points()
{
    return points_;
}


broken_line::broken_line(QVector<QPointF> points)
{
    points_ = points;
}

bool broken_line::init()
{
    set_attribute("123");
    return true;
}
