#pragma once
#include <QGraphicsTextItem>
#include <QFont>
#include <memory>

using std::unique_ptr;
class finished_product : public QGraphicsTextItem
{
public:
    static unique_ptr<finished_product> make (QPointF point);
    void set_attribute ();
    QMap<QString,QString>return_attribute_map ();
    QMap<QString, QString> attribute_;
    finished_product(QGraphicsTextItem* parent = nullptr);
protected:

    finished_product(QPointF point);
    bool init();
    void paint (QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;
    void focusOutEvent (QFocusEvent* event) override;
    QString type_;

};


