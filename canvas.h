#ifndef CANVAS_H
#define CANVAS_H
#include <QGraphicsView>
#include <QGraphicsScene>

class canvas : public QGraphicsView
{
public:
    canvas(QGraphicsView* parent = nullptr);
    canvas(QGraphicsScene* scene, QGraphicsView* parent = nullptr);
};

#endif // CANVAS_H
