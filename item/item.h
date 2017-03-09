#pragma once
#include <QGraphicsObject>
#include <memory>
#include <QMap>
#include "finished_product.h"
#include "raw_material.h"

using std::unique_ptr;
using std::make_unique;

struct impl_item;

class item : public QGraphicsObject
{
    Q_OBJECT
public:
     QRectF boundingRect () const override;
     void paint (QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) override;
     void set_attribute (QString key, QString value = {});
     //explicit item(QGraphicsItem *parent = 0);
     QMap<QString, QString> return_attriute();
     const QColor &  selected_color () { return  selected_color_ ; }
     void make_attribute();
protected:

    explicit item(QGraphicsItem *parent = nullptr);

protected:
    qreal item_width_ = 100;
    qreal item_height_ = 0.8 * item_width_;
    static constexpr qreal narrow_object_ratio_ = 1.2;
    static constexpr qreal enlarge_object_ratio_ = 2;
    QString type_;

private:
    QMap<QString, QString> attribute_map;
    finished_product finish_;
    raw_material raw_;




private:
    const QColor selected_color_ = Qt::red;

};
