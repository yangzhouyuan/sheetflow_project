#pragma once
#include <QGraphicsScene>
#include <memory>

using std::unique_ptr;
using std::make_unique;


class canvas_scene : public QGraphicsScene
{
public:
    template<typename ... ARGS>
    static unique_ptr<canvas_scene> make (ARGS && ... args)
    {
        unique_ptr<canvas_scene> ret (new canvas_scene (std::forward<ARGS> (args)...));
        if (ret == nullptr or ret->init() == false)
        {
            return nullptr;
        }
        return ret;
    }

    virtual ~canvas_scene();
protected:
    template<typename ... ARGS>
    canvas_scene (ARGS && ... args) : QGraphicsScene (std::forward<ARGS> (args)...) {}
    bool init ();

    void drawBackground(QPainter *painter, const QRectF &rect) override;
    void drawForeground(QPainter *painter, const QRectF &rect) override;
private:
    qreal height_ = 1000;
    qreal width_ = 1000 * 1.4142135;
    QRectF effective_rect_;
};


