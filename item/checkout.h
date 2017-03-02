#pragma once
#include "item/item.h"

class checkout : public item
{    
public:
    static unique_ptr<checkout> make (QPointF pos, QColor color = Qt::black);
protected:
    checkout(item* parent = nullptr);
    void paint (QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;
};



