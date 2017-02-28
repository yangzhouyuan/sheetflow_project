#pragma once

#include <QWidget>
#include <memory>
#include <vector>

using std::unique_ptr;

struct impl_drag_widget;

class drag_widget : public QWidget
{
    Q_OBJECT
public:
    unique_ptr<drag_widget> make (std::vector<QString>  names);
    ~drag_widget();
protected:
    explicit drag_widget(std::vector<QString> names, QWidget *parent = 0);
    bool init ();
signals:

private:
    unique_ptr<impl_drag_widget> imp;
};


