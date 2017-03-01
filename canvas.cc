#include "canvas.h"

canvas::canvas(QGraphicsView *parent)
    :QGraphicsView(parent)
{

}

canvas::canvas(QGraphicsScene *scene, QGraphicsView *parent)
    :QGraphicsView(scene,parent)
{
    setScene(scene);

}
