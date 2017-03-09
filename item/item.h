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
    explicit item(QGraphicsItem *parent = nullptr);
protected:
    qreal item_width_ = 100;
    qreal item_height_ = 0.8 * item_width_;
    static constexpr qreal narrow_object_ratio_ = 1.2;
    static constexpr qreal enlarge_object_ratio_ = 2;
    QString type_;
    const QColor &  selected_color () { return  selected_color_ ; }
private:
    const QColor selected_color_ = Qt::red;
};
