#include "drag_pixmap.h"
#include <QMap>
#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <QFontMetricsF>
#include <algorithm>
#include <QLineF>


namespace drawer
<%
using namespace std;
using pixmap_maker = void (*)  (QPainter*, qreal, qreal); //定义函数指针

static void raw_material_maker(QPainter* painter,qreal width, qreal height);
static void machining_maker(QPainter* painter,qreal width, qreal height);
static void checkout_maker(QPainter* painter,qreal width, qreal height);
static void finished_product_maker(QPainter* painter,qreal width, qreal height);
static void straight_line_maker(QPainter* painter,qreal width, qreal height);
static void broken_line_maker(QPainter* painter,qreal width, qreal height);


QPixmap make_pixmap(const QString &name, qreal width, qreal height)
{
    QPixmap pm (static_cast<int> (width), static_cast<int> (height));
    pm.fill(Qt::transparent);

    static std::map<QString, pixmap_maker> item_map
    {
        {"原材料", raw_material_maker},
        {"加工", machining_maker},
        {"检验", checkout_maker},
        {"产成品", finished_product_maker},
        {"连线1", straight_line_maker},
        {"连线2", broken_line_maker}

    };

    QPainter painter (&pm);

    auto found = item_map.find(name);

    if (found == item_map.end())
    {
        pm.fill(Qt::red);
    }
    else
    {
        (found->second) (&painter, width, height);
    }

    return pm;
}

static void raw_material_maker(QPainter* painter,qreal width, qreal height)
{
    auto font = painter->font();
    font.setPointSizeF(height);
    font.setBold(true);
    painter->setFont(font);

    QFontMetricsF metrics (font);

    auto w = metrics.width("A");
    auto h = metrics.height();
    QPointF center (width / 2, height / 2);

    painter->drawText(QRectF (center - QPointF (w / 2, h / 2), QSizeF (w, h)), "A");
}

static void machining_maker(QPainter* painter,qreal width, qreal height)
{
    auto the_pen = painter->pen();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(0.02 * width);
    painter->setPen(the_pen);
    painter->setBrush(Qt::white);
    painter->drawEllipse(QRectF(0.3 * width, height * 20 / 80, 0.5 * width, height * 50 / 80));
}

static void checkout_maker(QPainter* painter,qreal width, qreal height)
{
    auto the_pen = painter->pen();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(0.02 * width);
    painter->setPen(the_pen);
    painter->setBrush(Qt::white);
    painter->drawRect(QRectF(0.3 * width, height * 20 / 80, 0.45 * width, height * 45 / 80));

}

static void finished_product_maker(QPainter* painter,qreal width, qreal height)
{
    auto the_pen = painter->pen();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(0.02 * width);
    painter->setPen(the_pen);
    painter->setBrush(Qt::white);
    painter->drawRect(QRectF(0.07 * width, height * 25 / 80, 0.85 * width, height * 30 / 80));
}

static void straight_line_maker(QPainter* painter,qreal width, qreal height)
{
    auto x_scale = width / 100;
    auto y_scale = height / 80;
    QPointF p1 {x_scale * 20, y_scale * 50},
    p2 {x_scale * 80, y_scale * 50};

    auto the_pen = painter->pen();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(0.02 * width);
    painter->setPen(the_pen);
    painter->drawLine(p1, p2);
}

static void broken_line_maker(QPainter* painter,qreal width, qreal height)
{
    auto x_scale = width / 100;
    auto y_scale = height / 80;
    QPointF p1 {x_scale * 10, y_scale * 10},
    p2 {x_scale * 10, y_scale * 70},
    p3 {x_scale * 90, y_scale * 70};

    auto the_pen = painter->pen();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(0.02 * width);
    painter->setPen(the_pen);
    painter->drawLine(p1, p2);
    painter->drawLine(p2, p3);
}


%>
