#include "drag_widget.h"

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

drag_widget::drag_widget(std::vector<QString> names, QWidget *parent)
    :QWidget (parent)
    ,imp (std::make_unique<impl_drag_widget> ())
{
    imp->names = std::move (names);
}

bool drag_widget::init()
{
    for (auto & name : imp->names)
    {

    }

    return true;
}
