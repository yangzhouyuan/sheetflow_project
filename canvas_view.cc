#include "canvas_view.h"
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDropEvent>
#include "item/raw_material.h"
#include "item/maker.hpp"
#include <QStyleOptionGraphicsItem>
#include <QDebug>

canvas_view::draw_type canvas_view::return_type()
{
    return type_;
}

void canvas_view::set_type(canvas_view::draw_type t)
{
    if (t == type_)
    {
        return;
    }

    type_ = t;
    emit type_changed(t);
}

//QPixmap canvas_view::pixmap()
//{

//    QPixmap pix {200, 160};
//    pix.fill(Qt::transparent);
//    QPainter painter (&pix);
//    QStyleOptionGraphicsItem item;

//    for (auto & it : graphics_)
//    {
//        it->paint(&painter, &item, nullptr);
//    }
//    return pix;
//}

canvas_view::~canvas_view()
{

}

bool canvas_view::init()
{
    setViewportUpdateMode(FullViewportUpdate);
    setMouseTracking(true);
    setRenderHints (QPainter::Antialiasing);

    connect (this, &canvas_view::type_changed, [this] (auto && )
    {
        straight_line_item_ = nullptr;
        broken_lines_.clear();
    });

    return true;
}

void canvas_view::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent (event);
    switch (return_type())
    {
    case canvas_view::draw_type::STRAIGHTLINE:
        straightline_press_event(event);
        break;
    case canvas_view::draw_type::BROKENLINE:
        brokenline_press_event(event);
        break;
    default:
        break;
    }



}

void canvas_view::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent (event); 
    switch (return_type())
    {
    case canvas_view::draw_type::STRAIGHTLINE:
        straightline_move_event(event);
        break;
    case canvas_view::draw_type::BROKENLINE:
        brokenline_move_event(event);
        break;
    default:
        break;
    }
}

void canvas_view::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent (event);  
    switch (return_type())
    {
    case canvas_view::draw_type::STRAIGHTLINE:
        straightline_release_event(event);
        break;
    case canvas_view::draw_type::BROKENLINE:
        brokenline_release_event(event);
        break;
    default:
        break;
    }
}


void canvas_view::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("item") and event->source() != this)
    {
        event->accept();
    }
    else
    {
        QGraphicsView::dragEnterEvent(event);
    }
}

void canvas_view::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("item") and event->source() != this)
    {
        event->accept();
    }
    else
    {
        QGraphicsView::dragMoveEvent(event);
    }
}

void canvas_view::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("item") and event->source() != this)
    {
        drop_action (event);
        event->accept();
    }
    else
    {
        QGraphicsView::dropEvent(event);
    }

}

void canvas_view::straightline_press_event(QMouseEvent *event)
{
    begin_ = mapToScene (event->pos());
}

void canvas_view::straightline_move_event(QMouseEvent *event)
{
    if (event->buttons() != Qt::LeftButton)
    {
        return;
    }
    const auto pos = mapToScene(event->pos());

    if( straight_line_item_ == nullptr)
    {
        auto straight_item = scene()->addLine(QLineF(begin_, pos));
        straight_line_item_.reset(straight_item);
    }
    else
    {
        straight_line_item_->setLine(QLineF(begin_, pos));
    }
}

void canvas_view::straightline_release_event(QMouseEvent *event)
{
    Q_UNUSED(event);
    if(straight_line_item_ == nullptr)
    {
        return;
    }
    graphics_.emplace_back (straight_line_item_.release());
}

void canvas_view::brokenline_press_event(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        const auto scene_pos = mapToScene (event->pos());
        broken_lines_.emplace_back (
                    scene ()->addLine(QLineF (QPointF (scene_pos), QPointF (scene_pos))));
    }
    else if (event->buttons() == Qt::RightButton)
    {
        if (broken_lines_.size() <= 1)
        {
            return;
        }

        QVector<QPointF> points;
        QVector<QLineF> lines;

        const auto p1 = broken_lines_.front()->line().p1();
        points.push_back(p1);

        for (auto & it : broken_lines_)
        {
            points.push_back(it->line().p2());
        }

        graphics_.emplace_back (scene()->addPolygon({points}));

        broken_lines_.clear();
    }
}

void canvas_view::brokenline_move_event(QMouseEvent *event)
{
    if (broken_lines_.empty())
    {
        return;
    }
    const auto line = broken_lines_.back()->line();
    const auto p1 = line.p1();


    const auto new_p2 = mapToScene(event->pos());
    const auto new_line = QLineF (p1, new_p2);
    broken_lines_.back()->setLine(new_line);
}

void canvas_view::brokenline_release_event(QMouseEvent *event)
{
    Q_UNUSED(event);
}


void canvas_view::drop_action(QDropEvent *event)
{
    QString type = event->mimeData ()->data ("item");

    const auto pos = event->pos();
    const auto scene_pos = mapToScene(pos);

    auto item = make_item(type, scene_pos);

    const auto rect_center = item->boundingRect().center();
    auto center_pos = scene_pos - rect_center;
    item->setPos(center_pos);
    scene ()->addItem(item.release());

}

