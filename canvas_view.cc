#include "canvas_view.h"
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDropEvent>
#include "item/raw_material.h"
#include "item/maker.hpp"
#include <QStyleOptionGraphicsItem>
#include <QDebug>
#include "item/broken_line.h"
#include <QKeyEvent>

canvas_view::draw_type canvas_view::return_type()
{
    return type_;
}

void canvas_view::set_type_string(const QString &type)
{
    if (type == "原材料")
    {
        set_type(draw_type::RAWMATERIAL);
    }
    else if (type == "连线1")
    {
        set_type(draw_type::STRAIGHTLINE);
    }
    else if (type == "连线2")
    {
        set_type(draw_type::BROKENLINE);
    }
    else
    {
        set_type(draw_type::NONE);
    }
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
    if (canvas_body::init () == false)
    {
        return false;
    }

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

void canvas_view::keyPressEvent(QKeyEvent *event)
{
    QGraphicsView::keyPressEvent(event);

    if (event->modifiers() & Qt::CTRL and event->key() == Qt::Key_A)
    {
        select_allitems();
        event->accept();
    }

    if (event->key() == Qt::Key_Delete)
    {
        delete_selected();
        event->accept();
    }
}

void canvas_view::mousePressEvent(QMouseEvent *event)
{
    canvas_body::mousePressEvent (event);
    switch (return_type())
    {
    case canvas_view::draw_type::RAWMATERIAL:
        rawmaterial_press_event(event);
        break;
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
    canvas_body::mouseMoveEvent (event);
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
    canvas_body::mouseReleaseEvent (event);
    switch (return_type())
    {
    case canvas_view::draw_type::RAWMATERIAL:
        rawmaterial_release_event(event);
        break;
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
        canvas_body::dragEnterEvent(event);
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
        canvas_body::dragMoveEvent(event);
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
        canvas_body::dropEvent(event);
    }

}

void canvas_view::rawmaterial_press_event(QMouseEvent *event)
{
    begin_ = mapToScene (event->pos());
    auto rawmaterial = raw_material::make(begin_);
    scene()->addItem(rawmaterial.release());
}

void canvas_view::rawmaterial_release_event(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit draw_finished();
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
    scene()->addItem(straight_line_item_.release());
//    graphics_.emplace_back (straight_line_item_.release());

    emit draw_finished();
}

void canvas_view::brokenline_press_event(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        const auto scene_pos = mapToScene (event->pos());
        const auto begin_point = broken_lines_.empty() ? scene_pos : broken_lines_.back()->line().p2();

        auto new_line = scene()->addLine({begin_point, begin_point});
        broken_lines_.emplace_back (new_line);

    }
    else if (event->buttons() == Qt::RightButton)
    {
        if (broken_lines_.size() <= 1)
        {
            return;
        }

        QVector<QPointF> points;

        const auto p1 = broken_lines_.front()->line().p1();
        points.push_back(p1);

        for (auto & it : broken_lines_)
        {
            points.push_back(it->line().p2());
        }

        auto broke = broken_line::make (points);

        scene()->addItem(broke.get());
//        QPainter painter;
//        QStyleOptionGraphicsItem option;
//        broke.release()->paint(&painter, &option, this);

        broken_lines_.clear();

        emit draw_finished();
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

    const auto current_ptr = mapToScene(event->pos());
    const auto mouse_line = QLineF (p1, current_ptr);
    const auto angle = mouse_line.angle();

    QPointF _new_p2;
    if ((angle < 180 - 45 and angle > 45 + 0) or (angle > 180 + 45 and angle < 360 - 45))
    {
        _new_p2 = QPointF (p1.x(), current_ptr.y());
    }
    else
    {
        _new_p2 = QPointF (current_ptr.x(), p1.y());
    }

    const auto new_p2 = _new_p2;
    const auto new_line = QLineF (p1, new_p2);
    broken_lines_.back()->setLine(new_line);
}

void canvas_view::brokenline_release_event(QMouseEvent *event)
{
    Q_UNUSED(event);
}

void canvas_view::select_allitems()
{
    const auto list = items ();
    for (auto & item : list)
    {
        item->setSelected(true);
    }
}

void canvas_view::delete_selected()
{
    for (auto & it : scene()->selectedItems())
    {
        delete it;
    }
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

