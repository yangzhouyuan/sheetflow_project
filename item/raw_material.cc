#include "raw_material.h"
#include <QGraphicsSceneMouseEvent>

std::unique_ptr<raw_material> raw_material::make(QPointF point)
{
    auto ret = std::unique_ptr<raw_material> ( new raw_material (point));

    if (ret == nullptr or !ret->init())
    {
        return nullptr;
    }

    return ret;
}

raw_material::raw_material(QPointF point)
{
    setPos (point);
    setFlags (ItemIsSelectable | ItemIsMovable);
}



bool raw_material::init()
{
    this->setPlainText("双击输入文字或数字");
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
