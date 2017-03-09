#pragma once
#include "item/item.h"
#include <QFont>

class machining : public item
{
public:
    static unique_ptr<machining> make (QPointF pos, QColor color = Qt::black);
protected:
    machining(item* parent = nullptr);
    bool init();
    void paint (QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;

    QPainterPath shape() const override;

private:
    QString machining_info_;
    QFont font_;
};


