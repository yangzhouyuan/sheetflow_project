#pragma once
#include "item/item.h"

using std::unique_ptr;
class straight_line : public item
{

public:
    static unique_ptr<straight_line> make (QPointF begin, QPointF end);
    void paint(QPainter* painter,const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    QRectF boundingRect () const override;
    QPainterPath shape () const override;
protected:
    straight_line(QPointF begin, QPointF end);
    bool init ();
private:
    QPointF begin_;
    QPointF end_;
};


