#include "canvas_scene.h"
#include <QPainter>
#include <QMap>
#include <QDebug>
bool canvas_scene::init()
{
    connect (this, &canvas_scene::selectionChanged, [this] { report_seletion (); });
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

void canvas_scene::report_seletion()
{
    qDebug() << "scene有item被点击";
    if (selectedItems ().size () == 1)
    {
        emit selete_change(true);
        qDebug() <<"true1";
    }
    else
    {
        qDebug() <<"false";
        emit selete_change(false);
    }

}

canvas_scene::~canvas_scene()
{
}

QMap<QString, QString> canvas_scene::selete_item_attriute()
{

}

