#include "machining.h"
#include <QPainter>
#include <QInputDialog>

unique_ptr<machining> machining::make(QPointF pos, QColor color)
{
    unique_ptr <machining> ret(new machining);
    ret->setPos(pos);
    ret->type_ = "加工";
    return ret;
}

machining::machining(item *parent)
    :item(parent)
{
    item_width_ /= narrow_object_ratio_;
    item_height_ /= narrow_object_ratio_;
}

void machining::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    item::paint(painter, option, widget);

    auto the_pen = painter->pen();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(0.02 * item_width_);

    painter->setPen(the_pen);
    painter->setBrush(Qt::white);
    painter->drawEllipse(QRectF(0.3 * item_width_, item_height_ * 20 / 80, 0.5 * item_width_, item_height_ * 50 / 80));

}

void machining::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QInputDialog dlg;
    dlg.setInputMode (QInputDialog::IntInput);
    dlg.setLabelText("序号");

    dlg.exec();
}
