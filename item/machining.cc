#include "machining.h"
#include <QPainter>
#include <QInputDialog>

unique_ptr<machining> machining::make(QPointF pos, QColor color)
{
    unique_ptr <machining> ret(new machining);
    ret->setPos(pos);
    ret->type_ = "加工";
    ret->set_attribute("序号");
    ret->set_attribute("名称");
    ret->set_attribute("设备");
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

    painter->setFont(font_);
    auto the_pen = painter->pen();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(0.02 * item_width_);

    painter->setPen(the_pen);
    painter->setBrush(Qt::white);

    const QFontMetricsF metrics (painter->font());
    const auto text_w = metrics.width(machining_info_);
    const auto text_h = metrics.height();

    const QRectF rect (0.3 * item_width_, item_height_ * 20 / 80, 0.5 * item_width_, item_height_ * 50 / 80);
    auto center = rect.center();

    QRectF text_rect (center.x() - text_w / 2, center.y() - text_h / 2, text_w, text_h);

    //painter->drawRect(rect);
    painter->drawEllipse(rect);
    painter->drawText(text_rect, machining_info_);

//    painter->drawEllipse();

}

void machining::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QInputDialog dlg;
    dlg.setInputMode (QInputDialog::IntInput);
    dlg.setLabelText("序号");
    dlg.setTextValue (machining_info_);

    auto action = dlg.exec();
    if (action == QInputDialog::Rejected)
    {
        return;
    }

    machining_info_ = dlg.textValue();

}
