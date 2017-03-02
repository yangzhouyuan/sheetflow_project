#pragma once
#include "item/item.h"

class machining : public item
{
public:
    static unique_ptr<machining> make (QPointF pos, QColor color = Qt::black);
protected:
    machining(item* parent = nullptr);
    void paint (QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;
};


