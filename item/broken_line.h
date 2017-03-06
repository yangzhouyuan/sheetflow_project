#pragma once
#include <memory>
#include <QVector>
#include <QPointF>
#include <QGraphicsObject>

using std::unique_ptr;
class broken_line : public QGraphicsObject
{
    Q_OBJECT
public:
    static std::unique_ptr<broken_line> make (QVector<QPointF> points);
protected:
    broken_line (QVector<QPointF> points);
    bool init();
};





