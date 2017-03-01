#include "drag_widget.h"
#include <QLabel>
#include <QVBoxLayout>
#include "drag_pixmap.h"

struct impl_drag_widget
{
    std::vector<QString> names;
};

unique_ptr<drag_widget> drag_widget::make(std::vector<QString> names)
{
    unique_ptr<drag_widget> ret (new drag_widget (std::move (names)));
    if (ret == nullptr or ! ret->init())
    {
        return nullptr;
    }

    return ret;
}

drag_widget::~drag_widget()
{

}

drag_widget::drag_widget(std::vector<QString> names, QWidget *parent)
    :QWidget (parent)
    ,imp (std::make_unique<impl_drag_widget> ())
{
    imp->names = std::move (names);
}

bool drag_widget::init()
{
    auto v_layout = new QVBoxLayout(this);
    for (auto & name : imp->names)
    {
        auto map = drawer::make_pixmap (name, 100, 80);

        auto pic_label = new QLabel (this);
        pic_label->setObjectName(name);
        pic_label->setPixmap(map.scaled(100, 80));
        v_layout->addWidget (pic_label);

        auto info_label = new QLabel (name, this);
        v_layout->addWidget (info_label);
    }


    return true;
}
