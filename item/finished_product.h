#pragma once
#include "item/item.h"
#include <QFont>

class finished_product : public item
{
public:
    static unique_ptr<finished_product> make (QPointF pos, QColor color = Qt::black);
protected:
    finished_product(item* parent = nullptr);
    bool init();
    void paint (QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;
    QRectF boundingRect () const override;
    QString type_;
private:
    QString product_info_ ;
    QFont font_;
};


