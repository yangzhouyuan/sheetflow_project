#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>
#include <memory>
#include <vector>
#include <QGraphicsItem>
#include "canvas_body.h"


using std::make_unique;
using std::unique_ptr;

class canvas_view : public canvas_body
{
    Q_OBJECT
public:
    enum class draw_type
    {
        NONE,
        STRAIGHTLINE,
        BROKENLINE
    };
signals:
    void type_changed (canvas_view::draw_type);
public:
    draw_type return_type ();
    void set_type_string (const QString & type);
    void set_type (draw_type t);
//    QPixmap pixmap ();
public:
    static unique_ptr<canvas_view> make (QWidget *parent = nullptr) { return make_helper (parent); }
    static unique_ptr<canvas_view> make (QGraphicsScene *scene, QWidget *parent = nullptr)
    { return make_helper (scene, parent); }
    ~canvas_view() override;

protected:
    bool init();

    canvas_view(QWidget *parent = Q_NULLPTR): canvas_body (parent) { }
    canvas_view(QGraphicsScene *scene, QWidget *parent) : canvas_body (scene, parent) { }

    void mousePressEvent (QMouseEvent* event) override;
    void mouseMoveEvent (QMouseEvent* event) override;
    void mouseReleaseEvent (QMouseEvent* event) override;

    void dragEnterEvent(QDragEnterEvent * event) override;
    void dragMoveEvent (QDragMoveEvent * event) override;
    void dropEvent (QDropEvent * event) override;
private:
    void straightline_press_event (QMouseEvent* event);
    void straightline_move_event (QMouseEvent* event);
    void straightline_release_event (QMouseEvent* event);

    void brokenline_press_event (QMouseEvent* event);
    void brokenline_move_event (QMouseEvent* event);
    void brokenline_release_event (QMouseEvent* event);
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


private:
    canvas_view::draw_type type_ = canvas_view::draw_type::BROKENLINE;
    QPointF begin_;

    unique_ptr<QGraphicsLineItem>  straight_line_item_ = nullptr;
    std::vector<unique_ptr<QGraphicsLineItem>> broken_lines_;

    std::vector<QGraphicsItem*> graphics_;




};


