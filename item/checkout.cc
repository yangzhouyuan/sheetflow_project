#include "checkout.h"
#include <QInputDialog>
#include <QPainter>

unique_ptr<checkout> checkout::make(QPointF pos, QColor color)
{
    Q_UNUSED(color);
    unique_ptr <checkout> ret(new checkout);
    ret->setPos(pos);
    ret->type_ = "加工";
    ret->set_attribute("序号");
    ret->set_attribute("名称");
    ret->set_attribute("设备");
    return ret;
}

checkout::checkout(item *parent)
{
    Q_UNUSED(parent);
    item_width_ /= narrow_object_ratio_;
    item_height_ /= narrow_object_ratio_;
}

void checkout::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    item::paint(painter, option, widget);

    auto the_pen = painter->pen();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(0.02 * item_width_);
    painter->setPen(the_pen);
    painter->setBrush(Qt::white);

    const QFontMetricsF metrics (painter->font());
    const auto text_w = metrics.width(checkout_info_);
    const auto text_h = metrics.height();

//    const auto rect_w = std::max (item_width_ - 10, text_w + 10);
//    const auto rect_h = metrics.height() + 10;

    const QRectF rect (0.3 * item_width_, item_height_ * 20 / 80, 0.45 * item_width_, item_height_ * 45 / 80);
    auto center = rect.center();

    QRectF text_rect (center.x() - text_w / 2, center.y() - text_h / 2, text_w, text_h);

    //painter->drawRect(rect);
    painter->drawRect(rect);
    painter->drawText(text_rect, checkout_info_);


}

void checkout::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    QInputDialog dlg;
    dlg.setInputMode (QInputDialog::IntInput);
    dlg.setLabelText("序号");
    dlg.setTextValue (checkout_info_);

    auto action = dlg.exec();
    if (action == QInputDialog::Rejected)
    {
        return;
    }

    checkout_info_ = dlg.textValue();
}

//QRectF checkout::boundingRect() const
//{
//    return {};
//}
