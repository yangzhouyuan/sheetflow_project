#include "raw_material.h"
#include <QGraphicsSceneMouseEvent>
///原材料
std::unique_ptr<raw_material> raw_material::make(QPointF point)
{
    auto ret = std::unique_ptr<raw_material> ( new raw_material (point));

    if (ret == nullptr or !ret->init())
    {
        return nullptr;
    }

    return ret;
}

QMap<QString, QString> raw_material::return_attribute()
{
    return attribute_;
}

raw_material::raw_material(QGraphicsTextItem *parent)
    :QGraphicsTextItem(parent)
{

}


void raw_material::setattribute()
{
    attribute_.insert("名称","222");
    attribute_.insert("规格","222");
}

raw_material::raw_material(QPointF point)
{
    setPos (point);
    setFlags (ItemIsSelectable | ItemIsMovable);
}



bool raw_material::init()
{
    this->setPlainText("双击输入原材料信息");
    return true;
}

void raw_material::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsTextItem::mouseDoubleClickEvent(event);
    if (textInteractionFlags() == Qt::NoTextInteraction)
    {
        setTextInteractionFlags(Qt::TextEditorInteraction);
    }
}

void raw_material::focusOutEvent(QFocusEvent *event)
{
    setTextInteractionFlags(Qt::NoTextInteraction);
    QGraphicsTextItem::focusOutEvent(event);
    if (this->toPlainText().trimmed().isEmpty())
    {
        deleteLater();
    }
}


