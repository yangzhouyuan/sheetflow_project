#include "finished_product.h"
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

    ret->setPos(point);

    return ret;
}

finished_product::finished_product(QPointF point)
{
    this->setPlainText("产成品");
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


