#pragma once
#include "item/item.h"

class finished_product : public item
{
public:
    static unique_ptr<finished_product> make (QPointF pos, QColor color = Qt::black);
protected:
    finished_product(item* parent = nullptr);
    void paint (QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;
};


