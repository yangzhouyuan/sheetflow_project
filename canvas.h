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
    template<typename ... ARGS>
    static unique_ptr<canvas> make (ARGS && ... args)
    {
        unique_ptr<canvas> ret (new canvas (std::forward<ARGS> (args)...));
        if (ret == nullptr or ret->init() == false)
        {
            return nullptr;
        }
        return ret;
    }

    virtual ~canvas() override;

//protected:
    bool init();
    canvas(QGraphicsView* parent = nullptr);
    canvas(QGraphicsScene* scene, QGraphicsView* parent = nullptr);
};


