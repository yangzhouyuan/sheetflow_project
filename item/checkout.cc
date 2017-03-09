#include "checkout.h"
#include <QInputDialog>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

unique_ptr<checkout> checkout::make(QPointF pos, QColor color)
{
    Q_UNUSED(color);
    auto ret = unique_ptr <checkout> (new checkout);
    if (ret == nullptr or !ret->init())
    {
        return nullptr;
    }
    ret->setPos(pos);
    ret->type_ = "检验";
    ret->set_attribute("序号","345");
    ret->set_attribute("名称","567");
    ret->set_attribute("设备","789");
    return ret;
}

checkout::checkout(item *parent)
{
    Q_UNUSED(parent);
    item_width_ /= narrow_object_ratio_;
    item_height_ /= narrow_object_ratio_;
}

bool checkout::init()
{
    return true;
}

void checkout::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    item::paint(painter, option, widget);

    const QColor color = option->state bitand QStyle::State_Selected ? selected_color() : Qt::black;
    auto the_pen = painter->pen();
    the_pen.setColor(color);
    the_pen.setWidthF(0.02 * item_width_);
    painter->setPen(the_pen);
    painter->setBrush(Qt::white);

    const QFontMetricsF metrics (painter->font());
    const auto text_w = metrics.width(checkout_info_);
    const auto text_h = metrics.height();

    const QRectF rect (0.3 * item_width_, item_height_ * 20 / 80, 0.45 * item_width_, item_height_ * 45 / 80);
    auto center = rect.center();

    QRectF text_rect (center.x() - text_w / 2, center.y() - text_h / 2, text_w, text_h);

    painter->drawRect(rect);
    painter->drawText(text_rect, checkout_info_);

}

void checkout::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    item::mouseDoubleClickEvent(event);

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

QPainterPath checkout::shape() const
{
    QPainterPath path;

    const QRectF rect (0.3 * item_width_, item_height_ * 20 / 80, 0.45 * item_width_, item_height_ * 45 / 80);

    path.addRect(rect);

    return path;
}

