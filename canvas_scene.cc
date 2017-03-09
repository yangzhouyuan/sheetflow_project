#include "canvas_scene.h"
#include <QPainter>
#include <QMap>
#include <QDebug>
bool canvas_scene::init()
{
    connect (this, &canvas_scene::selectionChanged, this, &canvas_scene::item_seleted);
    setBackgroundBrush(QColor (230, 230, 230));
    return true;
}

void canvas_scene::drawBackground(QPainter *painter, const QRectF &rect)
{
    QGraphicsScene::drawBackground(painter, rect);
    painter->setBrush(Qt::white);

    auto center_point = sceneRect().center();
    effective_rect_ = QRectF (center_point - QPointF (width_ / 2, height_ / 2), QSizeF (width_, height_));
    painter->drawRect(effective_rect_);
}

void canvas_scene::drawForeground(QPainter *painter, const QRectF &rect)
{
    QGraphicsScene::drawForeground(painter, rect);
    painter->setBrush(Qt::transparent);

    auto center_point = sceneRect().center();
    effective_rect_ = QRectF (center_point - QPointF (width_ / 2, height_ / 2), QSizeF (width_, height_));
    painter->drawRect(effective_rect_);
}

void canvas_scene::item_seleted()
{
    qDebug() << "scene有item被点击";
    if (selectedItems ().size () == 1)
    {
        qDebug() <<"true1";
        emit selete_change(true);

    }
    else
    {

        emit selete_change(false);
        qDebug() <<"false";
    }

}

QMap<QString, QString> canvas_scene::attribute_map()
{
    auto selected = selectedItems();
    if (selected.size() != 1)
    {
        return {};
    }

    auto item_selected = dynamic_cast<item*> (selected [0]);

    if (item_selected == nullptr)
    {
        return {};
    }

    return item_selected->return_attriute();

}

void canvas_scene::set_attribute(QString key, QString value)
{
    auto selected = selectedItems();
    if (selected.size () != 1)
    {
        return;
    }
    auto item_selected = dynamic_cast<item*> (selected [0]);
    if (item_selected == nullptr)
    {
        return;
    }
    item_selected->set_attribute (key, value);
    item_selected->update ();

}

canvas_scene::~canvas_scene()
{
}

