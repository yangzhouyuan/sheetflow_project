#pragma once

#include <QWidget>
#include <memory>
#include <vector>


using std::unique_ptr;

struct impl_drag_widget;

class drag_widget : public QWidget
{
    Q_OBJECT
signals:
    void button_triggered (const QString&);
public:
    static unique_ptr<drag_widget> make (std::vector<QString>  labels = {},
                                         std::vector<QString> buttons = {},
                                         QWidget* parent = nullptr);
    void reset_status ();
    QString status ();
    virtual ~drag_widget () override;
protected:
    explicit drag_widget(std::vector<QString> labels, std::vector<QString> buttons,  QWidget *parent = 0);
    bool init ();
private:
    void mousePressEvent(QMouseEvent* event) override;
    void hideEvent (QHideEvent* event) override;
    void on_button_pressed ();
private:
    unique_ptr<impl_drag_widget> imp;
    QString status_;
};


