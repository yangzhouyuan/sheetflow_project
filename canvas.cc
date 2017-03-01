#include "canvas.h"

canvas::~canvas()
{

}

bool canvas::init()
{
    return true;
}

canvas::canvas(QGraphicsView *parent)
    :QGraphicsView(parent)
{

}

canvas::canvas(QGraphicsScene *scene, QGraphicsView *parent)
    :QGraphicsView(scene,parent)
{
    setScene(scene);

}
