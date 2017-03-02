#include "finished_product.h"
#include <QInputDialog>
#include <QPainter>

unique_ptr<finished_product> finished_product::make(QPointF pos, QColor color)
{
    unique_ptr <finished_product> ret(new finished_product);
    ret->setPos(pos);
    ret->type_ = "产成品";
    return ret;
}

finished_product::finished_product(item *parent)
{
    item_width_ *= enlarge_object_ratio_;
    item_height_ *= enlarge_object_ratio_;
}

void finished_product::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    auto the_pen = painter->pen();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(0.01 * item_width_);
    painter->setPen(the_pen);
    painter->setBrush(Qt::white);
    painter->drawRect(QRectF(0.07 * item_width_, item_height_ * 25 / 80, 0.85 * item_width_, item_height_ * 30 / 80));
}

void finished_product::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QInputDialog dlg;
    dlg.setInputMode (QInputDialog::TextInput);
    dlg.setLabelText("产品信息");

    dlg.exec();
}
