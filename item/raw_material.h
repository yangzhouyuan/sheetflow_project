#pragma once
#include <QGraphicsTextItem>
#include <memory>

class raw_material : public QGraphicsTextItem
{
public:
    static std::unique_ptr<raw_material> make (QPointF point);
    QMap<QString, QString> return_attribute ();
     raw_material (QGraphicsTextItem* parent = nullptr);
protected:
    raw_material (QPointF point);
    bool init ();

    void mouseDoubleClickEvent (QGraphicsSceneMouseEvent* event) override;
    void focusOutEvent (QFocusEvent* event) override;
    void setattribute ();
private:
    QMap<QString, QString> attribute_;

};


