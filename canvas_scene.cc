#include "canvas_scene.h"

bool canvas_scene::init()
{
    setBackgroundBrush(QColor (230, 230, 230));
    return true;
}

void canvas_scene::drawBackground(QPainter *painter, const QRectF &rect)
{

}

void canvas_scene::drawForeground(QPainter *painter, const QRectF &rect)
{

}

canvas_scene::~canvas_scene()
{

}

