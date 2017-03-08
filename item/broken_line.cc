#include "broken_line.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QDebug>

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

    const QColor color = option->state bitand QStyle::State_Selected ? selected_color() : Qt::black;
    auto the_pen = painter->pen();
    the_pen.setWidthF(0.01 * item_width_);
    the_pen.setColor(color);
    painter->setPen(the_pen);

    painter->drawPolyline(points_);

    if (option->state bitand QStyle::State_Selected)
    {
        the_pen.setBrush(Qt::transparent);
        the_pen.setStyle(Qt::DashLine);
        painter->setPen(the_pen);
        painter->drawRect(boundingRect());
    }


}

//QVector<QPointF> broken_line::return_points()
//{
//    return points_;
//}

QPainterPath broken_line::shape() const
{
    QPainterPath path;

    for (auto & it : points_)
    {
        path.lineTo(it);
    }

    return path;
}


broken_line::broken_line(QVector<QPointF> points)
{
    points_ = points;
}

bool broken_line::init()
{
    return true;
}
