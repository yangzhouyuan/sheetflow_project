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

    painter->drawRect(QRectF (5, 5 , 595, 495));
}

void canvas_scene::drawForeground(QPainter *painter, const QRectF &rect)
{
    QGraphicsScene::drawForeground(painter, rect);
    painter->setBrush(Qt::transparent);
    painter->drawRect(QRectF (5, 5, 595, 495));
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
    QMap<QString, QString> map_;
    map_.insert("echo","echo");
    map_.insert("123","345");
    map_.insert("234","333");
    map_.insert("xixi","x");

    return map_;
}

canvas_scene::~canvas_scene()
{
}

