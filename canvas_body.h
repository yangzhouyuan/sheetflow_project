#pragma once
#include "canvas_scene.h"
#include <QGraphicsView>

class canvas_body : public QGraphicsView
{
    Q_OBJECT
public:
    static unique_ptr<canvas_body> make (QWidget *parent = nullptr) { return make_helper (parent); }
    static unique_ptr<canvas_body> make (QGraphicsScene *scene, QWidget *parent = nullptr)
    { return make_helper (scene, parent); }


protected:
    bool init();

    canvas_body(QWidget *parent = Q_NULLPTR): QGraphicsView (parent) { }
    canvas_body(QGraphicsScene *scene, QWidget *parent) : QGraphicsView (scene, parent) { }
private:
    template<typename ... ARGS>
    static unique_ptr<canvas_body> make_helper (ARGS && ... args)
    {
        unique_ptr<canvas_body> ret (new canvas_body (std::forward<ARGS> (args)...));
        if (ret == nullptr or ret->init() == false)
        {
            return nullptr;
        }
        return ret;
    }
private:
    unique_ptr<canvas_scene> scene_ = canvas_scene::make (QRectF{0, 0, 600, 500});
    //canvas_scene canvas_scene_;

};


