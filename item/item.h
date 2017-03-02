#pragma once
#include <QGraphicsObject>
#include <memory>

using std::unique_ptr;
using std::make_unique;

struct impl_item;

class item : public QGraphicsObject
{
    Q_OBJECT
public:
protected:
    explicit item(QGraphicsItem *parent = 0);
    void paint (QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) override;
    QRectF boundingRect () const override;
    QPainterPath shape () const override;
protected:
//    unique_ptr<impl_item> imp;
    qreal item_width = 100;
    qreal item_height = 0.8 * item_width;
};
