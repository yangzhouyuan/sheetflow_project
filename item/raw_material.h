#pragma once
#include <QGraphicsTextItem>
#include <memory>

class raw_material : public QGraphicsTextItem
{
public:
    static std::unique_ptr<raw_material> make (QPointF point);
protected:
    raw_material (QPointF point);
    bool init ();

    void mouseDoubleClickEvent (QGraphicsSceneMouseEvent* event) override;
    void focusOutEvent (QFocusEvent* event) override;
};


