#include "canvas_scene.h"
#include <QPainter>

bool canvas_scene::init()
{
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

canvas_scene::~canvas_scene()
{

}

