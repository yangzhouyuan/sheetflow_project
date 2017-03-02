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
     QRectF boundingRect () const override;
     void paint (QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) override;
protected:
    explicit item(QGraphicsItem *parent = 0);
protected:
//    unique_ptr<impl_item> imp;
    qreal item_width_ = 100;
    qreal item_height_ = 0.8 * item_width_;
    static constexpr qreal narrow_object_ratio = 1.2;
    QString type_;
};
