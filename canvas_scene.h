#pragma once
#include <QGraphicsScene>
#include <memory>
#include <item/item.h>
#include <QMap>

using std::unique_ptr;
using std::make_unique;


class canvas_scene : public QGraphicsScene
{
    Q_OBJECT
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

    template<typename ... ARGS>
    canvas_scene (ARGS && ... args) : QGraphicsScene (std::forward<ARGS> (args)...) {}
    QMap<QString, QString>attribute_map();
signals:
   void selete_change(bool);


protected:

    bool init ();

    void drawBackground(QPainter *painter, const QRectF &rect) override;
    void drawForeground(QPainter *painter, const QRectF &rect) override;
private:
    void item_seleted();



};


