#pragma once
#include <QGraphicsTextItem>
#include <QFont>
#include <memory>

using std::unique_ptr;
class finished_product : public QGraphicsTextItem
{
public:
    static unique_ptr<finished_product> make (QPointF point);
protected:
    finished_product(QPointF point);
    bool init();
    void paint (QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;
    void focusOutEvent (QFocusEvent* event) override;
    QString type_;

};


