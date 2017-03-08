#include "finished_product.h"
#include <QInputDialog>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

unique_ptr<finished_product> finished_product::make(QPointF pos, QColor color)
{
    Q_UNUSED(color);
    unique_ptr <finished_product> ret (new finished_product);

    ret->setPos(pos);
    ret->type_ = "产成品";
    return ret;
}

finished_product::finished_product(item *parent)
{
    Q_UNUSED(parent);
}


void finished_product::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    item::paint(painter, option, widget);

    const QColor color = option->state bitand QStyle::State_Selected ? selected_color() : Qt::black;
    painter->setFont(font_);
    auto the_pen = painter->pen();
    the_pen.setColor(color);
    the_pen.setWidthF(2.0);
    painter->setPen(the_pen);
    painter->setBrush(Qt::white);
    const QFontMetricsF metrics (painter->font());
    auto text_size = metrics.size(Qt::TextWordWrap, product_info_);
    auto text_w = text_size.width();
    auto text_h = text_size.height();

    const auto rect_w = std::max (item_width_ - 10, text_w + 10);
    const auto rect_h = text_h + 10;

    const QRectF rect (0, 0, rect_w, rect_h);
    auto center = rect.center();

    QRectF text_rect (center.x() - text_w / 2, center.y() - text_h / 2, text_w, text_h);

    painter->drawRect(rect);
    painter->drawText(text_rect, Qt::TextWordWrap, product_info_);
}

void finished_product::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    QInputDialog dlg;
    dlg.setInputMode (QInputDialog::TextInput);
    dlg.setLabelText("产品信息");
    dlg.setTextValue (product_info_);

    auto action = dlg.exec();
    if (action == QInputDialog::Rejected)
    {
        return;
    }

    product_info_ = dlg.textValue();
}

QRectF finished_product::boundingRect() const
{
    const QFontMetricsF metrics (font_);
    auto text_size = metrics.size(Qt::TextWordWrap, product_info_);
    auto text_w = text_size.width();
    auto text_h = text_size.height();

    auto rect_w = std::max (item_width_ - 10, text_w + 10);
    auto rect_h = text_h + 10;

    return QRectF (0, 0, rect_w, rect_h);
}
