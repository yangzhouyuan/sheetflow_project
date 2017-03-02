#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>
#include <memory>

using std::make_unique;
using std::unique_ptr;

class canvas_view : public QGraphicsView
{
    Q_OBJECT
public:

    static unique_ptr<canvas_view> make (QWidget *parent = nullptr) { return make_helper (parent); }
    static unique_ptr<canvas_view> make (QGraphicsScene *scene, QWidget *parent = nullptr)
    { return make_helper (scene, parent); }
    virtual ~canvas_view() ;

protected:
    bool init();

    canvas_view(QWidget *parent = Q_NULLPTR): QGraphicsView (parent) { }
    canvas_view(QGraphicsScene *scene, QWidget *parent) : QGraphicsView (scene, parent) { }
    void dragEnterEvent(QDragEnterEvent * event) override;
    void dragMoveEvent (QDragMoveEvent * event) override;
    void dropEvent (QDropEvent * event) override;
private:
    void drop_action (QDropEvent* event);
    template<typename ... ARGS>
    static unique_ptr<canvas_view> make_helper (ARGS && ... args)
    {
        unique_ptr<canvas_view> ret (new canvas_view (std::forward<ARGS> (args)...));
        if (ret == nullptr or ret->init() == false)
        {
            return nullptr;
        }
        return ret;
    }
};


