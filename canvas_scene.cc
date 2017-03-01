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

    painter->drawRect(QRectF (5, 5 , 595, 495));
}

void canvas_scene::drawForeground(QPainter *painter, const QRectF &rect)
{
    QGraphicsScene::drawForeground(painter, rect);
    painter->setBrush(Qt::transparent);
    painter->drawRect(QRectF (5, 5, 595, 495));
}

canvas_scene::~canvas_scene()
{

}

