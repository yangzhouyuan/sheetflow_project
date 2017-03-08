#pragma once
#include <memory>
#include <QVector>
#include <QPointF>
#include "item/item.h"

using std::unique_ptr;
class broken_line : public item
{
    Q_OBJECT
public:
    static std::unique_ptr<broken_line> make (QVector<QPointF> points);
    QRectF boundingRect () const override;
    void paint (QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) override;
    QVector<QPointF> return_points();
    QPainterPath shape () const override;
private:
    broken_line (QVector<QPointF> points);
    bool init();
    QVector<QPointF> points_;

};





