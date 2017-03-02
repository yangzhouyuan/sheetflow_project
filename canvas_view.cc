#include "canvas_view.h"
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDropEvent>
#include "item/raw_material.h"
#include "item/maker.hpp"


canvas_view::~canvas_view()
{

}

bool canvas_view::init()
{
    return true;
}
#include <QDebug>
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


void canvas_view::drop_action(QDropEvent *event)
{
    QString type = event->mimeData ()->data ("item");

    const auto pos = event->pos();
    const auto scene_pos = mapToScene(pos);

    auto item = make_item( type, scene_pos);

    const auto rect_center = item->boundingRect().center();
    auto center_pos = scene_pos - rect_center;
    item->setPos(center_pos);
    scene ()->addItem(item.release());

}

