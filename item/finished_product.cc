#include "finished_product.h"
#include <QInputDialog>
#include <QPainter>
//<<<<<<< HEAD
//产成品
//unique_ptr<finished_product> finished_product::make(QPointF pos, QColor color)
//{
//    Q_UNUSED(color);
//    unique_ptr <finished_product> ret(new finished_product);
//    ret->setPos(pos);
//    ret->type_ = "产成品";
//    ret->set_attribute("名称");
//    ret->set_attribute("数量");
//    ret->set_attribute("型号");
//    return ret;
//}

//finished_product::finished_product(item *parent)
//    :item(parent)
//=======
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


