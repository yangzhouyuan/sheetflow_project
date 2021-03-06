﻿#include "finished_product.h"
#include <QInputDialog>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QFocusEvent>

unique_ptr<finished_product> finished_product::make(QPointF point)
{

    auto ret = unique_ptr <finished_product> (new finished_product(point));
    if (ret == nullptr or !ret->init())
    {
        return nullptr;
    }

    return ret;
}

void finished_product::set_attribute()
{
  attribute_.insert("名称", "111");
  attribute_.insert("数量","111");
  attribute_.insert("型号","111");
}

QMap<QString, QString> finished_product::return_attribute_map()
{
    return attribute_;
}

finished_product::finished_product(QGraphicsTextItem *parent)
    :QGraphicsTextItem(parent)
{
    set_attribute();
}

finished_product::finished_product(QPointF point)
//>>>>>>> spong2
{
    setPos(point);
    this->setPlainText("双击输入产成品信息");
}

bool finished_product::init()
{

    setFlags(ItemIsMovable | ItemIsSelectable);
    return true;
}


void finished_product::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsTextItem::paint(painter, option, widget);

    painter->drawRect(boundingRect());
}

void finished_product::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsTextItem::mouseDoubleClickEvent(event);

    if (textInteractionFlags() == Qt::NoTextInteraction)
    {
        setTextInteractionFlags(Qt::TextEditorInteraction);
    }
}

void finished_product::focusOutEvent(QFocusEvent* event)
{
    QGraphicsTextItem::focusOutEvent(event);
    setTextInteractionFlags(Qt::NoTextInteraction);

    if (this->toPlainText().trimmed().isEmpty())
    {
        deleteLater();
    }
}


