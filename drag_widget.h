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
    static unique_ptr<drag_widget> make (std::vector<QString>  labels = {},
                                         std::vector<QString> buttons = {},
                                         QWidget* parent = nullptr);
    ~drag_widget () override;
protected:
    explicit drag_widget(std::vector<QString> labels, std::vector<QString> buttons,  QWidget *parent = 0);
    bool init ();
signals:
private:
    void mousePressEvent(QMouseEvent* event) override;
private:
    unique_ptr<impl_drag_widget> imp;
};


