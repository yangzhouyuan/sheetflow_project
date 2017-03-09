#pragma once

#include <QMainWindow>
#include <memory>
#include <canvas_view.h>
#include <QMdiArea>
#include <QDockWidget>
#include "drag_widget.h"

using std::unique_ptr;

namespace Ui {
class sheetflow_main;
}

struct impl_sheetflow_main;

class sheetflow_main : public QMainWindow
{
    Q_OBJECT
public:
    ~sheetflow_main();
    static unique_ptr<sheetflow_main> make ();
    void file_new ();
protected:
    explicit sheetflow_main(QWidget *parent = 0);
    bool init ();
private:
    void create_toolbars ();
    void connections ();
    void create_actions ();
    void set_draw ();
    void set_mdiare ();
    void set_draw_widget_name ();
    canvas_view* create_canvas_body();
    void notify_attribute (bool ok);
    canvas_view* actvite_body ();
    void set_attribute ();
    void set_attribute_window ();
private:
    unique_ptr<impl_sheetflow_main> imp;


};

