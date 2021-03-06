﻿#pragma once
#include "item/item.h"
#include <QFont>

class checkout : public item
{    
public:
    static unique_ptr<checkout> make (QPointF pos, QColor color = Qt::black);
protected:
    checkout(item* parent = nullptr);
    bool init();
    void paint (QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;
    QPainterPath shape () const override;
private:
    QString checkout_info_;
  //  item item_;
    QFont font_;
    //void attribute ();
};



