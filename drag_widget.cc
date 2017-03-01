#include "drag_widget.h"
#include <QLabel>
#include <QVBoxLayout>
#include "drag_pixmap.h"
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <QPushButton>

struct impl_drag_widget
{
    std::vector<QString> label_names;
    std::vector<QString> button_names;
    std::vector<QPushButton*> buttons;

};

unique_ptr<drag_widget> drag_widget::make(std::vector<QString> labels,
                                          std::vector<QString> buttons,
                                          QWidget *parent)
{
    Q_UNUSED(parent);
    unique_ptr<drag_widget> ret (new drag_widget (std::move (labels), std::move (buttons)));
    if (ret == nullptr or ! ret->init())
    {
        return nullptr;
    }

    return ret;
}

drag_widget::~drag_widget()
{

}

drag_widget::drag_widget(std::vector<QString> labels, std::vector<QString> buttons, QWidget *parent)
    :QWidget (parent)
    ,imp (std::make_unique<impl_drag_widget> ())
{
    imp->label_names = std::move (labels);
    imp->button_names = std::move (buttons);
}

bool drag_widget::init()
{
    auto v_layout = new QVBoxLayout(this);
    for (auto & name : imp->label_names)
    {
        auto map = drawer::make_pixmap (name, 100, 80);

        auto pic_label = new QLabel (this);
        pic_label->setObjectName(name);
        pic_label->setPixmap(map.scaled(100, 80));
        pic_label->setAlignment(Qt::AlignCenter);
        pic_label->setFrameShape(QFrame::StyledPanel);
        v_layout->addWidget (pic_label);

        auto technics_label = new QLabel (name, this);
        technics_label->setAlignment(Qt::AlignCenter);
        v_layout->addWidget (technics_label);
    }
    return true;
}

void drag_widget::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    auto pos =  event->pos ();
    auto child = childAt(pos);

    if (child == nullptr)
    {
        return;
    }

    auto label = dynamic_cast<QLabel*>(child);
    if (label == nullptr)
    {
        return;
    }

    auto object_name = label->objectName();
    if (object_name.isEmpty())
    {
        return;
    }

    auto pm = drawer::make_pixmap(object_name, 100, 80);

    QDrag drag(this);
    auto data = std::make_unique<QMimeData> ();
    {
        auto str = label->objectName().toStdString();
        data->setData("item", QByteArray (str.data(), static_cast<int> (str.size())));
    }

    drag.setMimeData (data.release ());
    drag.setPixmap (pm);
    drag.setHotSpot ({pm.width () / 2, pm.height() / 2});

    drag.exec(Qt::CopyAction);
}
