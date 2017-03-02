#include "checkout.h"
#include <QInputDialog>
#include <QPainter>

unique_ptr<checkout> checkout::make(QPointF pos, QColor color)
{
    unique_ptr <checkout> ret(new checkout);
    ret->setPos(pos);
    ret->type_ = "加工";
    return ret;
}

checkout::checkout(item *parent)
{
    item_width_ /= narrow_object_ratio_;
    item_height_ /= narrow_object_ratio_;
}

void checkout::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    auto the_pen = painter->pen();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(0.02 * item_width_);
    painter->setPen(the_pen);
    painter->setBrush(Qt::white);
    painter->drawRect(QRectF(0.3 * item_width_, item_height_ * 20 / 80, 0.45 * item_width_, item_height_ * 45 / 80));
}

void checkout::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QInputDialog dlg;
    dlg.setInputMode (QInputDialog::IntInput);
    dlg.setLabelText("序号");

    dlg.exec();
}
