#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>
#include <memory>

using std::make_unique;
using std::unique_ptr;

class canvas : public QGraphicsView
{
    Q_OBJECT
public:

    static unique_ptr<canvas> make (QWidget *parent = nullptr) { return make_helper (parent); }
    static unique_ptr<canvas> make (QGraphicsScene *scene, QWidget *parent = nullptr)
    { return make_helper (scene, parent); }
    virtual ~canvas() ;

protected:
    bool init();

    canvas(QWidget *parent = Q_NULLPTR): QGraphicsView (parent) { }
    canvas(QGraphicsScene *scene, QWidget *parent) : QGraphicsView (scene, parent) { }
private:
    template<typename ... ARGS>
    static unique_ptr<canvas> make_helper (ARGS && ... args)
    {
        unique_ptr<canvas> ret (new canvas (std::forward<ARGS> (args)...));
        if (ret == nullptr or ret->init() == false)
        {
            return nullptr;
        }
        return ret;
    }
};


